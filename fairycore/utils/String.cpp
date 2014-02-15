#include "stdafx.h"
#include <assert.h>
#include <string>

ObjectsPool* String::s_stringsPool = 0;

void String::setup()
{
	s_stringsPool = new ObjectsPool(MIN_STRING_LENGTH, MAX_STRING_LENGTH);
	s_stringsPool->autorelease();
	s_stringsPool->retain();
}

String* String::create(bool isAutoRelease)
{
	String* ptr = new(true) String();
	if (isAutoRelease)
	{
		ptr->autorelease();
	}
	return ptr;
}

String* String::create(const char* value, bool isAutoRelease)
{
	String* ptr = new(true) String(value);
	if (isAutoRelease)
	{
		ptr->autorelease();
	}
	return ptr;
}

String* String::create(const String& value, bool isAutoRelease)
{
	String* ptr = new(true) String(value);
	if (isAutoRelease)
	{
		ptr->autorelease();
	}
	return ptr;
}

void String::destroy()
{
	this->~String();
	POOL(String)->deallocate(this);
}

String::String()
{
	initString();
}

String::String(const char* value)
{
	initString();
	setString(value);
}

String::String(const String& value)
{
	initString();
	setString(value.m_data);
}

String::~String()
{
	s_stringsPool->get(m_dataCapacity)->deallocate(m_data);
}

unsigned short* String::getData() const
{
	return m_data;
}

unsigned int String::length() const
{
	return m_stringLength;
}

void String::initString() 
{
	m_stringLength = 0;
	m_dataCapacity = s_stringsPool->getMinimalCapacity(0);
	m_data = (unsigned short*)s_stringsPool->get(m_dataCapacity)->allocate();
}

void String::appendString(const char *str) 
{
	int len = str ? strlen(str) : 0;
	if (len) {
		if (m_stringLength) 
		{
			requestMoreData(m_stringLength + len + 1);

			unsigned short* ptr = m_data + m_stringLength;
			for (int i = 0; i < len; ++i)
			{
				ptr[i] = str[i];
			}
			m_stringLength += len;
			m_data[m_stringLength] = 0;
		}
		else 
		{
			setString(str);
		}
	}
}

void String::appendString(const unsigned short *str)
{
	int len = str ? wstrlen(str) : 0;
	if (len) {
		if (m_stringLength)
		{
			requestMoreData(m_stringLength + len + 1);

			memcpy(m_data + m_stringLength, str, len * sizeof(unsigned short));			
			m_stringLength += len;
			m_data[m_stringLength] = 0;
		}
		else
		{
			setString(str);
		}
	}
}

void String::setString(const char *str) 
{
	int len = str ? strlen(str) : 0;

	if (len)
	{
		requestNewData(len);

		for (int i = 0; i < len; ++i)
		{
			m_data[i] = str[i];
		}
		m_stringLength = len;
	}
	else
	{
		empty();
	}
}

void String::setString(const unsigned short *str)
{
	int len = str ? wstrlen(str) : 0;
	if (len)
	{		
		requestNewData(len);

		memcpy(m_data, str, len * sizeof(unsigned short));
		m_stringLength = len;
	}
	else
	{
		empty();
	}
}

void String::empty() 
{
	if (m_stringLength) 
	{
		s_stringsPool->get(m_dataCapacity)->deallocate(m_data);
		initString();
	}
}

void String::requestNewData(int len)
{
	empty();

	m_dataCapacity = s_stringsPool->getMinimalCapacity((len + 1) * sizeof(unsigned short));
	m_data = (unsigned short*)s_stringsPool->get(m_dataCapacity)->allocate();
	m_data[len] = 0;
}

void String::requestMoreData(int newLen)
{
	if (newLen*sizeof(unsigned short) > m_dataCapacity)
	{
		int newDataCapacity = s_stringsPool->getMinimalCapacity(newLen * sizeof(unsigned short));
		unsigned short* newData = (unsigned short*)s_stringsPool->get(newDataCapacity)->allocate();

		memcpy(newData, m_data, m_stringLength * sizeof(unsigned short));
		s_stringsPool->get(m_dataCapacity)->deallocate(m_data);

		m_data = newData;
		m_dataCapacity = newDataCapacity;
	}
}

int String::wstrlen(const unsigned short* str)
{
	int res = 0;
	while (*str++)
	{
		++res;
	}
	return res;
}

void String::append(const char* str, int index, int count)
{
	if (count) 
	{
		if (m_stringLength)
		{
			requestMoreData(m_stringLength + count + 1);
		}
		else
		{
			requestNewData(count);			
		}

		unsigned short* ptr = m_data + m_stringLength;
		for (int i = 0; i < count; ++i)
		{
			ptr[i] = str[index + i];
		}

		m_stringLength += count;
		m_data[m_stringLength] = 0;
	}
}

void String::trim()
{
	int i;
	int left = 0;
	for (i = 0; i < m_stringLength; ++i)
	{
		if (isSpace(m_data[i]))
		{
			left = i + 1;
			break;
		}
	}

	int right = m_stringLength;
	for (i = m_stringLength-1; i >= 0; --i)
	{
		if (isSpace(m_data[i]))
		{
			right = i;
			break;
		}
	}

	int len = right - left;
	if (len < m_stringLength)
	{
		subString(left, right - left);
	}
}

bool String::isSpace(unsigned short c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == 'v' || c == '\f');
}

void String::subString(int start)
{
	return subString(start, m_stringLength - start);
}

void String::subString(int start, int length)
{
	int i;
	for (i = 0; i < length; ++i)
	{
		m_data[i] = m_data[i + start];
	}

	m_stringLength = length;
}

bool String::startsWith(unsigned short c)
{
	return m_data[0] == c;
}

bool String::endsWith(unsigned short c)
{
	return m_data[m_stringLength - 1] == c;
}

void String::toUpper()
{
	for (int i = 0; i < m_stringLength; ++i)
	{
		unsigned short c = m_data[i];
		m_data[i] = (c < 'a' || c > 'z') ? c : (c - 'a') + 'A';
	}
}

void String::toLower()
{
	for (int i = 0; i < m_stringLength; ++i)
	{
		unsigned short c = m_data[i];
		m_data[i] = (c < 'A' || c > 'Z') ? c : (c - 'A') + 'a';
	}
}

bool String::equals(const char* value)
{
	int len = strlen(value);
	if (m_stringLength != len)
	{
		return false;
	}

	for (int i = 0; i < len; ++i)
	{
		if (m_data[i] != value[i])
		{
			return false;
		}
	}

	return true;
}


/*
public String [] Split (params char [] separator)
{
return Split (separator, int.MaxValue, 0);
}

public String[] Split (char[] separator, int count)
{
return Split (separator, count, 0);
}

[ComVisible (false)]
public String[] Split (char[] separator, StringSplitOptions options)
{
return Split (separator, Int32.MaxValue, options);
}

[ComVisible (false)]
public String[] Split (char[] separator, int count, StringSplitOptions options)
{
if (count < 0)
throw new ArgumentOutOfRangeException ("count", "Count cannot be less than zero.");
if ((options != StringSplitOptions.None) && (options != StringSplitOptions.RemoveEmptyEntries))
throw new ArgumentException ("Illegal enum value: " + options + ".");

if (Length == 0 && (options & StringSplitOptions.RemoveEmptyEntries) != 0)
return EmptyArray<string>.Value;

if (count <= 1) {
return count == 0 ?
EmptyArray<string>.Value :
new String[1] { this };
}

return SplitByCharacters (separator, count, options != 0);
}

[ComVisible (false)]
public String[] Split (string[] separator, StringSplitOptions options)
{
return Split (separator, Int32.MaxValue, options);
}

[ComVisible (false)]
public String[] Split (string[] separator, int count, StringSplitOptions options)
{
if (count < 0)
throw new ArgumentOutOfRangeException ("count", "Count cannot be less than zero.");
if ((options != StringSplitOptions.None) && (options != StringSplitOptions.RemoveEmptyEntries))
throw new ArgumentException ("Illegal enum value: " + options + ".");

if (count <= 1) {
return count == 0 ?
EmptyArray<string>.Value :
new String[1] { this };
}

bool removeEmpty = (options & StringSplitOptions.RemoveEmptyEntries) != 0;

if (separator == null || separator.Length == 0)
return SplitByCharacters (null, count, removeEmpty);

if (Length == 0 && removeEmpty)
return EmptyArray<string>.Value;

List<String> arr = new List<String> ();

int pos = 0;
int matchCount = 0;
while (pos < this.Length) {
int matchIndex = -1;
int matchPos = Int32.MaxValue;

// Find the first position where any of the separators matches
for (int i = 0; i < separator.Length; ++i) {
string sep = separator [i];
if (sep == null || sep.Length == 0)
continue;

int match = IndexOfOrdinalUnchecked (sep, pos, length - pos);
if (match >= 0 && match < matchPos) {
matchIndex = i;
matchPos = match;
}
}

if (matchIndex == -1)
break;

if (!(matchPos == pos && removeEmpty)) {
if (arr.Count == count - 1)
break;
arr.Add (this.Substring (pos, matchPos - pos));
}

pos = matchPos + separator [matchIndex].Length;

matchCount ++;
}

if (matchCount == 0)
return new String [] { this };

// string contained only separators
if (removeEmpty && matchCount != 0 && pos == this.Length && arr.Count == 0)
return EmptyArray<string>.Value;

if (!(removeEmpty && pos == this.Length))
arr.Add (this.Substring (pos));

return arr.ToArray ();
}

// .NET 2.0 compatibility only
#if !NET_4_0 && !MOBILE
static readonly char[] WhiteChars = {
(char) 0x9, (char) 0xA, (char) 0xB, (char) 0xC, (char) 0xD,
(char) 0x85, (char) 0x1680, (char) 0x2028, (char) 0x2029,
(char) 0x20, (char) 0xA0, (char) 0x2000, (char) 0x2001, (char) 0x2002, (char) 0x2003, (char) 0x2004,
(char) 0x2005, (char) 0x2006, (char) 0x2007, (char) 0x2008, (char) 0x2009, (char) 0x200A, (char) 0x200B,
(char) 0x3000, (char) 0xFEFF
};
#endif

unsafe string[] SplitByCharacters (char[] sep, int count, bool removeEmpty)
{
#if !NET_4_0 && !MOBILE
if (sep == null || sep.Length == 0)
sep = WhiteChars;
#endif

int[] split_points = null;
int total_points = 0;
--count;

if (sep == null || sep.Length == 0) {
fixed (char* src = this) {
char* src_ptr = src;
int len = Length;

while (len > 0) {
if (char.IsWhiteSpace (*src_ptr++)) {
if (split_points == null) {
split_points = new int[8];
} else if (split_points.Length == total_points) {
Array.Resize (ref split_points, split_points.Length * 2);
}

split_points[total_points++] = Length - len;
if (total_points == count && !removeEmpty)
break;
}
--len;
}
}
} else {
fixed (char* src = this) {
fixed (char* sep_src = sep) {
char* src_ptr = src;
char* sep_ptr_end = sep_src + sep.Length;
int len = Length;
while (len > 0) {
char* sep_ptr = sep_src;
do {
if (*sep_ptr++ == *src_ptr) {
if (split_points == null) {
split_points = new int[8];
} else if (split_points.Length == total_points) {
Array.Resize (ref split_points, split_points.Length * 2);
}

split_points[total_points++] = Length - len;
if (total_points == count && !removeEmpty)
len = 0;

break;
}
} while (sep_ptr != sep_ptr_end);

++src_ptr;
--len;
}
}
}
}

if (total_points == 0)
return new string[] { this };

var res = new string[Math.Min (total_points, count) + 1];
int prev_index = 0;
int i = 0;
if (!removeEmpty) {
for (; i < total_points; ++i) {
var start = split_points[i];
res[i] = SubstringUnchecked (prev_index, start - prev_index);
prev_index = start + 1;
}

res[i] = SubstringUnchecked (prev_index, Length - prev_index);
} else {
int used = 0;
int length;
for (; i < total_points; ++i) {
var start = split_points[i];
length = start - prev_index;
if (length != 0) {
if (used == count)
break;

res[used++] = SubstringUnchecked (prev_index, length);
}

prev_index = start + 1;
}

length = Length - prev_index;
if (length != 0)
res[used++] = SubstringUnchecked (prev_index, length);

if (used != res.Length)
Array.Resize (ref res, used);
}

return res;
}
*/
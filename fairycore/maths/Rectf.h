#ifndef __RECT_H__
#define __RECT_H__

#include "maths/Vector3f.h"

struct Rectf
{
public:	
	/*public Vector2 center
	{
		get
		{
		return new Vector2(this.x + this.m_Width / 2f, this.y + this.m_Height / 2f);
	}
		set
		{
			this.m_XMin = value.x - this.m_Width / 2f;
			this.m_YMin = value.y - this.m_Height / 2f;
		}
	}

	public float height
	{
		get
		{
		return this.m_Height;
	}
		set
		{
			this.m_Height = value;
		}
	}

	[Obsolete("use xMin")]
	public float left
	{
		get
		{
		return this.m_XMin;
	}
	}

	[Obsolete("use xMax")]
	public float right
	{
		get
		{
		return this.m_XMin + this.m_Width;
	}
	}

	[Obsolete("use yMin")]
	public float top
	{
		get
		{
		return this.m_YMin;
	}
	}

	public float width
	{
		get
		{
		return this.m_Width;
	}
		set
		{
			this.m_Width = value;
		}
	}

	public float x
	{
		get
		{
		return this.m_XMin;
	}
		set
		{
			this.m_XMin = value;
		}
	}

	public float xMax
	{
		get
		{
		return this.m_Width + this.m_XMin;
	}
		set
		{
			this.m_Width = value - this.m_XMin;
		}
	}

	public float xMin
	{
		get
		{
		return this.m_XMin;
	}
		set
		{
			float xMax = this.xMax;
			this.m_XMin = value;
			this.m_Width = xMax - this.m_XMin;
		}
	}

	public float y
	{
		get
		{
		return this.m_YMin;
	}
		set
		{
			this.m_YMin = value;
		}
	}

	public float yMax
	{
		get
		{
		return this.m_Height + this.m_YMin;
	}
		set
		{
			this.m_Height = value - this.m_YMin;
		}
	}

	public float yMin
	{
		get
		{
		return this.m_YMin;
	}
		set
		{
			float yMax = this.yMax;
			this.m_YMin = value;
			this.m_Height = yMax - this.m_YMin;
		}
	}

	//
	// Constructors
	//
	public Rect(Rect source)
	{
		this.m_XMin = source.m_XMin;
		this.m_YMin = source.m_YMin;
		this.m_Width = source.m_Width;
		this.m_Height = source.m_Height;
	}

	public Rect(float left, float top, float width, float height)
	{
		this.m_XMin = left;
		this.m_YMin = top;
		this.m_Width = width;
		this.m_Height = height;
	}

	//
	// Static Methods
	//
	public static Rect MinMaxRect(float left, float top, float right, float bottom)
	{
		return new Rect(left, top, right - left, bottom - top);
	}

	//
	// Methods
	//
	public bool Contains(Vector2 point)
	{
		return point.x >= this.xMin && point.x < this.xMax && point.y >= this.yMin && point.y < this.yMax;
	}

	public bool Contains(Vector3 point)
	{
		return point.x >= this.xMin && point.x < this.xMax && point.y >= this.yMin && point.y < this.yMax;
	}

	public bool Contains(Vector3 point, bool allowInverse)
	{
		if (!allowInverse)
		{
			return this.Contains(point);
		}
		bool flag = false;
		if ((this.width < 0f && point.x <= this.xMin && point.x > this.xMax) || (this.width >= 0f && point.x >= this.xMin && point.x < this.xMax))
		{
			flag = true;
		}
		return flag && ((this.height < 0f && point.y <= this.yMin && point.y > this.yMax) || (this.height >= 0f && point.y >= this.yMin && point.y < this.yMax));
	}

	public override bool Equals(object other)
	{
		if (!(other is Rect))
		{
			return false;
		}
		Rect rect = (Rect)other;
		return this.x.Equals(rect.x) && this.y.Equals(rect.y) && this.width.Equals(rect.width) && this.height.Equals(rect.height);
	}

	public override int GetHashCode()
	{
		return this.x.GetHashCode() ^ this.width.GetHashCode() << 2 ^ this.y.GetHashCode() >> 2 ^ this.height.GetHashCode() >> 1;
	}

	public bool Overlaps(Rect other)
	{
		return other.xMax > this.xMin && other.xMin < this.xMax && other.yMax > this.yMin && other.yMin < this.yMax;
	}

	public bool Overlaps(Rect other, bool allowInverse)
	{
		Rect rect = this;
		if (allowInverse)
		{
			rect = Rect.OrderMinMax(rect);
			other = Rect.OrderMinMax(other);
		}
		return rect.Overlaps(other);
	}

	public void Set(float left, float top, float width, float height)
	{
		this.m_XMin = left;
		this.m_YMin = top;
		this.m_Width = width;
		this.m_Height = height;
	}

	public override string ToString()
	{
		return UnityString.Format("(x:{0:F2}, y:{1:F2}, width:{2:F2}, height:{3:F2})", new object[]
		{
			this.x,
				this.y,
				this.width,
				this.height
		});
	}

	public string ToString(string format)
	{
		return UnityString.Format("(x:{0}, y:{1}, width:{2}, height:{3})", new object[]
		{
			this.x.ToString(format),
				this.y.ToString(format),
				this.width.ToString(format),
				this.height.ToString(format)
		});
	}

	//
	// Operators
	//
	public static bool operator ==(Rect lhs, Rect rhs)
	{
		return lhs.x == rhs.x && lhs.y == rhs.y && lhs.width == rhs.width && lhs.height == rhs.height;
	}

	public static bool operator !=(Rect lhs, Rect rhs)
	{
		return lhs.x != rhs.x || lhs.y != rhs.y || lhs.width != rhs.width || lhs.height != rhs.height;
	}*/
};

#endif // __RECT_H__

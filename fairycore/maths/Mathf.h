#ifndef __MATHF_H__
#define __MATHF_H__

#include <math.h>
#include "utils/Array.h"

struct Mathf
{
public:

	//
	// Static Fields
	//
	static const float Deg2Rad;
	static const float Rad2Deg;
	static const float Epsilon;
	static const float PI;
	static const float Infinity;
	static const float NegativeInfinity;

	//
	// Static Methods
	//
	inline static float Abs(float f)
	{
		return fabsf(f);
	}

	inline static int Abs(int value)
	{
		int mask = (value >> (sizeof(int)* CHAR_BIT - 1));
		return (value + mask) ^ mask;
	}

	inline static float Acos(float f)
	{
		return acosf(f);
	}

	inline static bool Approximately(float a, float b)
	{
		return Mathf::Abs(b - a) < Mathf::Max(1E-06f * Mathf::Max(Mathf::Abs(a), Mathf::Abs(b)), 1.121039E-44f);
	}

	inline static float Asin(float f)
	{
		return asinf(f);
	}

	inline static float Atan(float f)
	{
		return atanf(f);
	}

	inline static float Atan2(float y, float x)
	{
		return atan2f(y, x);
	}

	inline static float Ceil(float f)
	{
		return ceilf(f);
	}

	inline static int CeilToInt(float f)
	{
		return (int)ceilf(f);
	}

	inline static int Clamp(int value, int min, int max)
	{
		if (value < min)
		{
			value = min;
		}
		else
		{
			if (value > max)
			{
				value = max;
			}
		}
		return value;
	}

	inline static float Clamp(float value, float min, float max)
	{
		if (value < min)
		{
			value = min;
		}
		else
		{
			if (value > max)
			{
				value = max;
			}
		}
		return value;
	}

	inline static float Clamp01(float value)
	{
		if (value < 0.f)
		{
			return 0.f;
		}
		if (value > 1.f)
		{
			return 1.f;
		}
		return value;
	}

	static int ClosestPowerOfTwo(int value)
	{
		// TODO
		return value;
	}

	inline static float Cos(float f)
	{
		return cosf(f);
	}

	inline static float DeltaAngle(float current, float target)
	{
		float num = Mathf::Repeat(target - current, 360.f);
		if (num > 180.f)
		{
			num -= 360.f;
		}
		return num;
	}

	inline static float Exp(float power)
	{
		return expf(power);
	}

	inline static float Floor(float f)
	{
		return floorf(f);
	}

	inline static int FloorToInt(float f)
	{
		return (int)floorf(f);
	}

	inline static float Gamma(float value, float absmax, float gamma)
	{
		bool flag = false;
		if (value < 0.f)
		{
			flag = true;
		}
		float num = Mathf::Abs(value);
		if (num > absmax)
		{
			return (!flag) ? num : (-num);
		}
		float num2 = Mathf::Pow(num / absmax, gamma) * absmax;
		return (!flag) ? num2 : (-num2);
	}

	inline static float GammaToLinearSpace(float value)
	{
		// TODO
		return 0.f;
	}

	inline static float InverseLerp(float from, float to, float value)
	{
		if (from < to)
		{
			if (value < from)
			{
				return 0.f;
			}
			if (value > to)
			{
				return 1.f;
			}
			value -= from;
			value /= to - from;
			return value;
		}
		else
		{
			if (from <= to)
			{
				return 0.f;
			}
			if (value < to)
			{
				return 1.f;
			}
			if (value > from)
			{
				return 0.f;
			}
			return 1.f - (value - to) / (from - to);
		}
	}

	inline static bool IsPowerOfTwo(int value)
	{
		// TODO
		return false;
	}

	inline static float Lerp(float from, float to, float t)
	{
		return from + (to - from) * Mathf::Clamp01(t);
	}

	inline static float LerpAngle(float a, float b, float t)
	{
		float num = Mathf::Repeat(b - a, 360.f);
		if (num > 180.f)
		{
			num -= 360.f;
		}
		return a + num * Mathf::Clamp01(t);
	}

	inline static float LinearToGammaSpace(float value)
	{
		// TODO
		return 0.f;
	}

	inline static float Log(float f, float p)
	{
		// TODO
		return 0.f;
	}

	inline static float Log(float f)
	{
		return logf(f);
	}

	inline static float Log10(float f)
	{
		return log10f(f);
	}

	inline static float Max(float a, float b, float c)
	{
		return (a <= b) ? ( (b <= c) ? c : b ) : ( (a <= c) ? c : a );
	}

	inline static float Max(Array<float>& values)
	{
		int num = values.count();
		if (num == 0)
		{
			return 0.f;
		}
		float num2 = values[0];
		for (int i = 1; i < num; i++)
		{
			if (values[i] > num2)
			{
				num2 = values[i];
			}
		}
		return num2;
	}

	inline static int Max(int a, int b)
	{
		return (a <= b) ? b : a;
	}
	
	inline static int Max(Array<int>& values)
	{
		int num = values.count();
		if (num == 0)
		{
			return 0;
		}
		int num2 = values[0];
		for (int i = 1; i < num; i++)
		{
			if (values[i] > num2)
			{
				num2 = values[i];
			}
		}
		return num2;
	}

	inline static float Max(float a, float b)
	{
		return (a <= b) ? b : a;
	}

	inline static int Min(Array<int>& values)
	{
		int num = values.count();
		if (num == 0)
		{
			return 0;
		}
		int num2 = values[0];
		for (int i = 1; i < num; i++)
		{
			if (values[i] < num2)
			{
				num2 = values[i];
			}
		}
		return num2;
	}

	inline static int Min(int a, int b)
	{
		return (a >= b) ? b : a;
	}

	inline static float Min(Array<float>& values)
	{
		int num = values.count();
		if (num == 0)
		{
			return 0.f;
		}
		float num2 = values[0];
		for (int i = 1; i < num; i++)
		{
			if (values[i] < num2)
			{
				num2 = values[i];
			}
		}
		return num2;
	}

	inline static float Min(float a, float b)
	{
		return (a >= b) ? b : a;
	}

	inline static float Min(float a, float b, float c)
	{
		return (a >= b) ? ((b >= c) ? c : b) : ((a >= c) ? c : a);
	}

	inline static float MoveTowards(float current, float target, float maxDelta)
	{
		if (Mathf::Abs(target - current) <= maxDelta)
		{
			return target;
		}
		return current + Mathf::Sign(target - current) * maxDelta;
	}

	inline static float MoveTowardsAngle(float current, float target, float maxDelta)
	{
		target = current + Mathf::DeltaAngle(current, target);
		return Mathf::MoveTowards(current, target, maxDelta);
	}

	inline static int NextPowerOfTwo(int value)
	{
		value--;
		value |= value >> 1;
		value |= value >> 2;
		value |= value >> 4;
		value |= value >> 8;
		value |= value >> 16;
		value++;
	}

	inline static float PerlinNoise(float x, float y)
	{
		// TODO
		return 0.f;
	}

	inline static float PingPong(float t, float length)
	{
		t = Mathf::Repeat(t, length * 2.f);
		return length - Mathf::Abs(t - length);
	}

	inline static float Pow(float f, float p)
	{
		return powf(f, p);
	}

	inline static float Repeat(float t, float length)
	{
		return t - Mathf::Floor(t / length) * length;
	}

	inline static float Round(float f)
	{
		return (float)roundf(f);
	}

	inline static int RoundToInt(float f)
	{
		return (int)roundf(f);
	}

	inline static float Sign(float f)
	{
		return (f < 0.f) ? -1.f : 1.f;
	}

	inline static float Sin(float f)
	{
		return sinf(f);
	}

	// TODO
	/*
	[ExcludeFromDocs]
	inline static float SmoothDamp(float current, float target, ref float currentVelocity, float smoothTime, float maxSpeed)
	{
		float deltaTime = Time.deltaTime;
		return Mathf::SmoothDamp(current, target, ref currentVelocity, smoothTime, maxSpeed, deltaTime);
	}

	[ExcludeFromDocs]
	inline static float SmoothDamp(float current, float target, ref float currentVelocity, float smoothTime)
	{
		float deltaTime = Time.deltaTime;
		float maxSpeed = float.PositiveInfinity;
		return Mathf::SmoothDamp(current, target, ref currentVelocity, smoothTime, maxSpeed, deltaTime);
	}

	inline static float SmoothDamp(float current, float target, ref float currentVelocity, float smoothTime, [DefaultValue("Mathf::Infinity")] float maxSpeed, [DefaultValue("Time.deltaTime")] float deltaTime)
	{
		smoothTime = Mathf::Max(0.0001f, smoothTime);
		float num = 2.f / smoothTime;
		float num2 = num * deltaTime;
		float num3 = 1.f / (1.f + num2 + 0.48f * num2 * num2 + 0.235f * num2 * num2 * num2);
		float num4 = current - target;
		float num5 = target;
		float num6 = maxSpeed * smoothTime;
		num4 = Mathf::Clamp(num4, -num6, num6);
		target = current - num4;
		float num7 = (currentVelocity + num * num4) * deltaTime;
		currentVelocity = (currentVelocity - num * num7) * num3;
		float num8 = target + (num4 + num7) * num3;
		if (num5 - current > 0.f == num8 > num5)
		{
			num8 = num5;
			currentVelocity = (num8 - num5) / deltaTime;
		}
		return num8;
	}

	[ExcludeFromDocs]
	inline static float SmoothDampAngle(float current, float target, ref float currentVelocity, float smoothTime, float maxSpeed)
	{
		float deltaTime = Time.deltaTime;
		return Mathf::SmoothDampAngle(current, target, ref currentVelocity, smoothTime, maxSpeed, deltaTime);
	}

	inline static float SmoothDampAngle(float current, float target, ref float currentVelocity, float smoothTime, [DefaultValue("Mathf::Infinity")] float maxSpeed, [DefaultValue("Time.deltaTime")] float deltaTime)
	{
		target = current + Mathf::DeltaAngle(current, target);
		return Mathf::SmoothDamp(current, target, ref currentVelocity, smoothTime, maxSpeed, deltaTime);
	}

	[ExcludeFromDocs]
	inline static float SmoothDampAngle(float current, float target, ref float currentVelocity, float smoothTime)
	{
		float deltaTime = Time.deltaTime;
		float maxSpeed = float.PositiveInfinity;
		return Mathf::SmoothDampAngle(current, target, ref currentVelocity, smoothTime, maxSpeed, deltaTime);
	}*/

	inline static float SmoothStep(float from, float to, float t)
	{
		t = Mathf::Clamp01(t);
		t = -2.f * t * t * t + 3.f * t * t;
		return to * t + from * (1.f - t);
	}

	inline static float Sqrt(float f)
	{
		return sqrtf(f);
	}

	inline static float Tan(float f)
	{
		return tanf(f);
	}
};

#endif // __MATHF_H__

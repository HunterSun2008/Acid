#include "Maths.hpp"

#include <random>

namespace acid
{
	static std::random_device RANDOM_DEVICE;
	static std::mt19937 RANDOM_GENERATOR(RANDOM_DEVICE());

	float Maths::Random(const float &min, const float &max)
	{
		std::uniform_real_distribution<float> dist(min, max);
		return dist(RANDOM_GENERATOR);
	}

	float Maths::RandomNormal(const float &standardDeviation, const float &mean)
	{
		std::normal_distribution<float> dist(mean, standardDeviation);
		return dist(RANDOM_GENERATOR);
	}

	float Maths::RandomLog(const float &min, const float &max)
	{
		float logLower = std::log(min);
		float logUpper = std::log(max);
		float raw = Random(0.0f, 1.0f);

		float result = std::exp(raw * (logUpper - logLower) + logLower);

		if (result < min)
		{
			result = min;
		}
		else if (result > max)
		{
			result = max;
		}

		return result;
	}

	float Maths::WrapDegrees(const float &degrees)
	{
		float x = std::fmod(degrees, 360.0f);

		if (x < 0.0f)
		{
			x += 360.0f;
		}

		return x;
	}

	float Maths::WrapRadians(const float &radians)
	{
		float x = std::fmod(radians, 2.0f * Pi);

		if (x < 0.0f)
		{
			x += 2.0f * Pi;
		}

		return x;
	}

	float Maths::CosLerp(const float &a, const float &b, const float &factor)
	{
		float ft = factor * Pi;
		float f = 1.0f - std::cos(ft) * 0.5f;
		return (a * (1.0f - f)) + (b * f);
	}

	float Maths::SmoothlyStep(const float &edge0, const float &edge1, const float &x)
	{
		float s = std::clamp((x - edge0) / (edge1 - edge0), 0.0f, 1.0f);
		return s * s * (3.0f - 2.0f * s);
	}

	float Maths::CosFromSin(const float &sin, const float &angle)
	{
		// sin(x)^2 + cos(x)^2 = 1
		float cos = std::sqrt(1.0f - sin * sin);
		float a = angle + (Pi / 2.0f);
		float b = a - (int)(a / (2.0f * Pi)) * (2.0f * Pi);

		if (b < 0.0f)
		{
			b = (2.0f * Pi) + b;
		}

		if (b >= Pi)
		{
			return -cos;
		}

		return cos;
	}
}

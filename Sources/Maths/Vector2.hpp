#pragma once

#include <ostream>
#include <string>
#include <cassert>
#include "Serialized/Metadata.hpp"
#include "Maths.hpp"

namespace acid
{
	/// <summary>
	/// Holds a 2-tuple vector.
	/// </summary>
	template<typename T = float>
	class Vector2
	{
	public:
		/// <summary>
		/// Constructor for Vector2.
		/// </summary>
		/// <param name="x"> Start x. </param>
		/// <param name="y"> Start y. </param>
		Vector2(const T &x = 0, const T &y = 0) :
			m_x(x),
			m_y(y)
		{
		}

		/// <summary>
		/// Adds this vector to another vector.
		/// </summary>
		/// <param name="other"> The other vector. </param>
		/// <returns> The resultant vector. </returns>
		template<typename X>
		auto Add(const Vector2<X> &other) const
		{
			return Vector2(m_x + other.m_x, m_y + other.m_y);
		}

		/// <summary>
		/// Subtracts this vector to another vector.
		/// </summary>
		/// <param name="other"> The other vector. </param>
		/// <returns> The resultant vector. </returns>
		template<typename X>
		auto Subtract(const Vector2<X> &other) const
		{
			return Vector2(m_x - other.m_x, m_y - other.m_y);
		}

		/// <summary>
		/// Multiplies this vector with another vector.
		/// </summary>
		/// <param name="other"> The other vector. </param>
		/// <returns> The resultant vector. </returns>
		template<typename X>
		auto Multiply(const Vector2<X> &other) const
		{
			return Vector2(m_x * other.m_x, m_y * other.m_y);
		}

		/// <summary>
		/// Divides this vector by another vector.
		/// </summary>
		/// <param name="other"> The other vector. </param>
		/// <returns> The resultant vector. </returns>
		template<typename X>
		auto Divide(const Vector2<X> &other) const
		{
			return Vector2(m_x / other.m_x, m_y / other.m_y);
		}

		/// <summary>
		/// Calculates the angle between this vector and another vector.
		/// </summary>
		/// <param name="other"> The other vector. </param>
		/// <returns> The angle, in radians. </returns>
		template<typename X>
		float Angle(const Vector2<X> &other) const
		{
			float dls = Dot(other) / (Length() * other.Length());

			if (dls < -1.0f)
			{
				dls = -1.0f;
			}
			else if (dls > 1.0f)
			{
				dls = 1.0f;
			}

			return std::acos(dls);
		}

		/// <summary>
		/// Calculates the dot product of the this vector and another vector.
		/// </summary>
		/// <param name="other"> The other vector. </param>
		/// <returns> The dot product. </returns>
		template<typename X>
		float Dot(const Vector2<X> &other) const
		{
			return m_x * other.m_x + m_y * other.m_y;
		}

		/// <summary>
		/// Calculates the linear interpolation between this vector and another vector.
		/// </summary>
		/// <param name="other"> The other quaternion. </param>
		/// <param name="progression"> The progression. </param>
		/// <returns> Left lerp right. </returns>
		template<typename X, typename Y>
		auto Lerp(const Vector2<X> &other, const Y &progression) const
		{
			auto ta = *this * (static_cast<Y>(1) - progression);
			auto tb = other * progression;
			return ta + tb;
		}

		/// <summary>
		/// Scales this vector by a scalar.
		/// </summary>
		/// <param name="scalar"> The scalar value. </param>
		/// <returns> The scaled vector. </returns>
		template<typename X>
		Vector2 Scale(const X &scalar) const
		{
			return Vector2(m_x * scalar, m_y * scalar);
		}

		/// <summary>
		/// Rotates this vector by a angle around the origin.
		/// </summary>
		/// <param name="angle"> The angle to rotate by, in radians. </param>
		/// <returns> The rotated vector. </returns>
		template<typename X>
		Vector2 Rotate(const X &angle) const
		{
			return Vector2(m_x * std::cos(angle) - m_y * std::sin(angle), m_x * std::sin(angle) + m_y * std::cos(angle));
		}

		/// <summary>
		/// Rotates this vector by a angle around a rotation axis.
		/// </summary>
		/// <param name="angle"> The angle to rotate by, in radians. </param>
		/// <param name="rotationAxis"> The point to rotate the vector around. </param>
		/// <returns> The rotated vector. </returns>
		template<typename X, typename Y>
		auto Rotate(const X &angle, const Vector2<Y> &rotationAxis) const
		{
			return Vector2(((m_x - rotationAxis.m_x) * std::cos(angle)) - ((m_y - rotationAxis.m_y) * std::sin(angle) + rotationAxis.m_x),
				((m_x - rotationAxis.m_x) * std::sin(angle)) + ((m_y - rotationAxis.m_y) * std::cos(angle) + rotationAxis.m_y));
		}

		/// <summary>
		/// Negates this vector.
		/// </summary>
		/// <returns> The negated vector. </returns>
		Vector2 Negate() const
		{
			return Vector2(-m_x, -m_y);
		}

		/// <summary>
		/// Normalizes this vector.
		/// </summary>
		/// <returns> The normalized vector. </returns>
		Vector2 Normalize() const
		{
			auto l = Length();
			return Vector2(m_x / l, m_y / l);
		}

		/// <summary>
		/// Gets the length squared of this vector.
		/// </summary>
		/// <returns> The length squared. </returns>
		auto LengthSquared() const
		{
			return m_x * m_x + m_y * m_y;
		}

		/// <summary>
		/// Gets the length of this vector.
		/// </summary>
		/// <returns> The length. </returns>
		auto Length() const
		{
			return std::sqrt(LengthSquared());
		}

		/// <summary>
		/// Gets the maximum value in this vector.
		/// </summary>
		/// <returns> The largest components. </returns>
		auto MaxComponent() const
		{
			return std::max(m_x, m_y);
		}

		/// <summary>
		/// Gets the lowest value in this vector.
		/// </summary>
		/// <returns> The smallest components. </returns>
		auto MinComponent() const
		{
			return std::min(m_x, m_y);
		}

		/// <summary>
		/// Gets the distance between this vector and another vector.
		/// </summary>
		/// <param name="other"> The other vector. </param>
		/// <returns> The squared distance. </returns>
		template<typename X>
		auto DistanceSquared(const Vector2<X> &other) const
		{
			auto dx = m_x - other.m_x;
			auto dy = m_y - other.m_y;
			return dx * dx + dy * dy;
		}

		/// <summary>
		/// Gets the between this vector and another vector.
		/// </summary>
		/// <param name="other"> The other vector. </param>
		/// <returns> The distance. </returns>
		template<typename X>
		auto Distance(const Vector2<X> &other) const
		{
			return std::sqrt(DistanceSquared(other));
		}

		/// <summary>
		/// Gets the vector distance between this vector and another vector.
		/// </summary>
		/// <param name="other"> The other vector. </param>
		/// <returns> The vector distance. </returns>
		template<typename X>
		auto DistanceVector(const Vector2<X> &other) const
		{
			auto dx = m_x - other.m_x;
			auto dy = m_y - other.m_y;
			return Vector2(dx * dx, dy * dy);
		}

		/// <summary>
		/// Gets if this vector is in a triangle.
		/// </summary>
		/// <param name="v1"> The first triangle vertex. </param>
		/// <param name="v2"> The second triangle vertex. </param>
		/// <param name="v3"> The third triangle vertex. </param>
		/// <returns> If this vector is in a triangle. </returns>
		template<typename X, typename Y, typename Z>
		bool InTriangle(const Vector2<X> &v1, const Vector2<Y> &v2, const Vector2<Z> &v3) const
		{
			bool b1 = ((m_x - v2.m_x) * (v1.m_y - v2.m_y) - (v1.m_x - v2.m_x) * (m_y - v2.m_y)) < 0.0f;
			bool b2 = ((m_x - v3.m_x) * (v2.m_y - v3.m_y) - (v2.m_x - v3.m_x) * (m_y - v3.m_y)) < 0.0f;
			bool b3 = ((m_x - v1.m_x) * (v3.m_y - v1.m_y) - (v3.m_x - v1.m_x) * (m_y - v1.m_y)) < 0.0f;
			return ((b1 == b2) & (b2 == b3));
		}

		/// <summary>
		/// Gradually changes this vector to a target.
		/// </summary>
		/// <param name="target"> The target vector. </param>
		/// <param name="rate"> The rate to go from current to the target. </param>
		/// <returns> The changed vector. </returns>
		template<typename X, typename Y>
		auto SmoothDamp(const Vector2<X> &target, const Vector2<Y> &rate) const
		{
			return Vector2(Maths::SmoothDamp(m_x, target.m_x, rate.m_x), Maths::SmoothDamp(m_y, target.m_y, rate.m_y));
		}

		/// <summary>
		/// Converts from rectangular to spherical coordinates, this vector is in cartesian (x, y).
		/// </summary>
		/// <returns> The polar coordinates (radius, theta). </returns>
		Vector2 CartesianToPolar() const
		{
			float radius = std::sqrt(m_x * m_x + m_y * m_y);
			float theta = std::atan2(m_y, m_x);
			return Vector2(radius, theta);
		}

		/// <summary>
		/// Converts from spherical to rectangular coordinates, this vector is in polar (radius, theta).
		/// </summary>
		/// <returns> The cartesian coordinates (x, y). </returns>
		Vector2 PolarToCartesian() const
		{
			float x = m_x * std::cos(m_y);
			float y = m_x * std::sin(m_y);
			return Vector2(x, y);
		}

		/// <summary>
		/// Gets the lowest vector size.
		/// </summary>
		/// <param name="a"> The first vector to get values from. </param>
		/// <param name="b"> The second vector to get values from. </param>
		/// <returns> The lowest vector. </returns>
		template<typename X, typename Y>
		static auto MinVector(const Vector2<X> &a, const Vector2<Y> &b)
		{
			return Vector2(std::min(a.m_x, b.m_x), std::min(a.m_y, b.m_y));
		}

		/// <summary>
		/// Gets the maximum vector size.
		/// </summary>
		/// <param name="a"> The first vector to get values from. </param>
		/// <param name="b"> The second vector to get values from. </param>
		/// <returns> The maximum vector. </returns>
		template<typename X, typename Y>
		static auto MaxVector(const Vector2<X> &a, const Vector2<Y> &b)
		{
			return Vector2(std::max(a.m_x, b.m_x), std::max(a.m_y, b.m_y));
		}

		void Decode(const Metadata &metadata)
		{
			metadata.GetChild("x", m_x);
			metadata.GetChild("y", m_y);
		}

		void Encode(Metadata &metadata) const
		{
			metadata.SetChild("x", m_x);
			metadata.SetChild("y", m_y);
		}

		template<typename X>
		bool operator==(const Vector2<X> &other) const
		{
			return m_x == other.m_x && m_y == other.m_x;
		}

		template<typename X>
		bool operator!=(const Vector2<X> &other) const
		{
			return !(*this == other);
		}

		template<typename X>
		bool operator<(const Vector2<X> &other) const
		{
			return m_x < other.m_x && m_y < other.m_y;
		}

		template<typename X>
		bool operator<=(const Vector2<X> &other) const
		{
			return m_x <= other.m_x && m_y <= other.m_y;
		}

		template<typename X>
		bool operator>(const Vector2<X> &other) const
		{
			return m_x > other.m_x && m_y > other.m_y;
		}

		template<typename X>
		bool operator>=(const Vector2<X> &other) const
		{
			return m_x >= other.m_x && m_y >= other.m_y;
		}

		template<typename X>
		bool operator==(const X &value) const
		{
			return m_x == value && m_y == value;
		}

		template<typename X>
		bool operator!=(const X &value) const
		{
			return !(*this == value);
		}

		Vector2 operator-() const
		{
			return Negate();
		}

		const T &operator[](const uint32_t &index) const
		{
			assert(index < 2);
			return m_elements[index];
		}

		T &operator[](const uint32_t &index)
		{
			assert(index < 2);
			return m_elements[index];
		}

		template<typename X>
		Vector2 &operator+=(const Vector2<X> &other)
		{
			return *this = Add(other);
		}

		template<typename X>
		Vector2 &operator-=(const Vector2<X> &other)
		{
			return *this = Subtract(other);
		}

		template<typename X>
		Vector2 &operator*=(const Vector2<X> &other)
		{
			return *this = Multiply(other);
		}

		template<typename X>
		Vector2 &operator/=(const Vector2<X> &other)
		{
			return *this = Divide(other);
		}

		template<typename X>
		Vector2 &operator+=(const X &other)
		{
			return *this = Add(Vector2(other, other));
		}

		template<typename X>
		Vector2 &operator-=(const X &other)
		{
			return *this = Subtract(Vector2(other, other));
		}

		Vector2 &operator*=(const T &other)
		{
			return *this = Multiply(Vector2(other, other));
		}

		Vector2 &operator/=(const T &other)
		{
			return *this = Divide(Vector2(other, other));
		}

		friend std::ostream &operator<<(std::ostream &stream, const Vector2 &vector)
		{
			stream << vector.ToString();
			return stream;
		}

		std::string ToString() const
		{
			std::stringstream result;
			result << "Vector2(" << m_x << ", " << m_y << ")";
			return result.str();
		}

		union
		{
			struct
			{
				T m_elements[2];
			};

			struct
			{
				T m_x, m_y;
			};
		};
	};

	template<typename X, typename Y>
	auto operator+(const Vector2<X> &left, const Vector2<Y> &right)
	{
		return left.Add(right);
	}

	template<typename X, typename Y>
	auto operator-(const Vector2<X> &left, const Vector2<Y> &right)
	{
		return left.Subtract(right);
	}

	template<typename X, typename Y>
	auto operator*(const Vector2<X> &left, const Vector2<Y> &right)
	{
		return left.Multiply(right);
	}

	template<typename X, typename Y>
	auto operator/(const Vector2<X> &left, const Vector2<Y> &right)
	{
		return left.Divide(right);
	}

	template<typename X, typename Y>
	auto operator+(const X &left, const Vector2<Y> &right)
	{
		return Vector2(left, left).Add(right);
	}

	template<typename X, typename Y>
	auto operator-(const X &left, const Vector2<Y> &right)
	{
		return Vector2(left, left).Subtract(right);
	}

	template<typename X, typename Y>
	auto operator*(const X &left, const Vector2<Y> &right)
	{
		return Vector2(left, left).Multiply(right);
	}

	template<typename X, typename Y>
	auto operator/(const X &left, const Vector2<Y> &right)
	{
		return Vector2(left, left).Divide(right);
	}

	template<typename X, typename Y>
	auto operator+(const Vector2<X> &left, const Y &right)
	{
		return left.Add(Vector2(right, right));
	}

	template<typename X, typename Y>
	auto operator-(const Vector2<X> &left, const Y &right)
	{
		return left.Subtract(Vector2(right, right));
	}

	template<typename X, typename Y>
	auto operator*(const Vector2<X> &left, const Y &right)
	{
		return left.Multiply(Vector2(right, right));
	}

	template<typename X, typename Y>
	auto operator/(const Vector2<X> &left, const Y &right)
	{
		return left.Divide(Vector2(right, right));
	}

	using Vector2f = Vector2<float>;
	using Vector2d = Vector2<double>;
	using Vector2i = Vector2<int32_t>;
}

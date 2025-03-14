#pragma once

namespace engine
{
	template<typename T>
	class Vector2
	{
	public:
		T x, y;

		Vector2(T x, T y);
		Vector2(T v);
		Vector2();

		Vector2& operator +(const Vector2& v)
		{
			x += v.x;
			y += v.y;
			return *this;
		}
		Vector2& operator -(const Vector2& v)
		{
			x -= v.x;
			y -= v.y;
			return *this;
		}
		Vector2& operator *(const Vector2& v)
		{
			x *= v.x;
			y *= v.y;
			return *this;
		}

		Vector2& operator +(const T v)
		{
			x += v;
			y += v;
			return *this;
		}
		Vector2& operator -(const T v)
		{
			x -= v;
			y -= v;
			return *this;
		}
		Vector2& operator *(const T v)
		{
			x *= v;
			y *= v;
			return *this;
		}
	};

	template<typename T>
	class Vector3
	{
	public:
		T x, y, z;

		Vector3(T x, T y, T z);
		Vector3(T v);
		Vector3();

		Vector3& operator +(const Vector3& v)
		{
			x += v.x;
			y += v.y;
			z += v.z;
			return *this;
		}
		Vector3& operator -(const Vector3& v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
			return *this;
		}
		Vector3& operator *(const Vector3& v)
		{
			x *= v.x;
			y *= v.y;
			z *= v.z;
			return *this;
		}

		Vector3& operator +(const T v)
		{
			x += v;
			y += v;
			z += v;
			return *this;
		}
		Vector3& operator -(const T v)
		{
			x -= v;
			y -= v;
			z -= v;
			return *this;
		}
		Vector3& operator *(const T v)
		{
			x *= v;
			y *= v;
			z *= v;
			return *this;
		}
	};
}

#define Vec2f Vector2<float>
#define Vec3f Vector2<float>
#define Vec2i Vector2<int>
#define Vec3i Vector2<int>

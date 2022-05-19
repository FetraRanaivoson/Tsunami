#pragma once
#include <math.h>

namespace tsunami {
	/**
	Hold a 3 dimensional vector
	*/
	class Vector3 {
	public:
		float x;
		float y;
		float z;

		Vector3() : x(0), y(0), z(0) {}
		Vector3(const float x, const float y, const float z)
			: x(x), y(y), z(z) {}
		~Vector3(){};

	private:
		float pad = 0;
		void invert() {
			x = -x;
			y = -y;
			z = -z;
		}

		/*Get the magnitude of this vector*/
		float magnitude() const {
			return sqrtf(x * x + y * y + z * z);
		}

		/*Get the squared magnitude of this vector*/
		float sqrMagnitude() const {
			return x * x + y * y + z * z;
		}

		/*Turns a non-zero vector into a vector of unit length*/
		void normalize() {
			float m = magnitude();
			if (m > 0) {
				x /= m;
				y /= m;
				z /= m;
			}
		}

		/*Get a copy of the normalized version of a non-zero vector*/
		Vector3 normalized() const{
			float m = magnitude();
			float xx = x / m;
			float yy = y / m;
			float zz = y / m;
			return Vector3(xx,yy,zz);
		}

		/*Multiplies this vector by a given scalar k*/
		void operator *= (const float k) {
			x *= k;
			y *= k;
			z *= k;
		}

		/*Get a copy of this vector scaled to the given value*/
		Vector3 operator*(const float k) const {
			return Vector3(x * k, y * k, z * k);
		}

		/*Add the given vector to this*/
		void operator += (const Vector3& v) {
			x += v.x;
			y += v.y;
			z += v.z;
		}

		/*Get the value of the given vector added to this*/
		Vector3 operator+(const Vector3& v) const {
			return Vector3(x + v.x, y + v.x, z + v.z);
		}

		/*Substract the given vector to this*/
		void operator -= (const Vector3& v) {
			x -= v.x;
			y -= v.y;
			z -= v.z;
		}

		/*Get the value of the given vector substracted to this*/
		Vector3 operator+(const Vector3& v) const {
			return Vector3(x - v.x, y - v.x, z - v.z);
		}

		/*Add the given vector to this,scaled by the given k amount*/
		void addScaledVector(const Vector3& v, float k) {
			x += v.x * k;
			y += v.y * k;
			z += v.z * k;
		}
	};
} 

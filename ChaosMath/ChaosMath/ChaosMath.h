#pragma once

#include <assert.h>

// supported types:
// vec2f, vec3f, vec4f
// vec2i, vec3i, vec4i

// static functions
// lerp, pow, dot, cross
// static members
// one, zero, up, down, left, right, forward, back, ana, kata

// convert from each type to each other type

namespace cm {
	template <typename T>
	struct vec3 {
		T x, y, z;

		vec3() : vec3(0, 0, 0) {}
		vec3(T all) : vec3(all, all, all) {}
		vec3(T _x, T _y, T _z) : x(_x), y(_y), z(_z) { }
		vec3(const vec3& v) { x = v.x; y = v.y; z = v.z; }
		~vec3() {}
	};

	template<typename T>
	inline std::ostream& operator<<(std::ostream &os, vec3<T> vec) { 
		os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")"; 
		return os; 
	}

	template <typename T>
	struct vec4 {
		T x, y, z, w;

		vec4() : vec4<T>(0, 0, 0, 0) {}
		vec4(T all) : vec4<T>(all, all, all, all) {}
		vec4(T _x, T _y, T _z, T _w) : x(_x), y(_y), z(_z), w(_w) { }
		vec4(const vec4<T>& v) { x = v.x; y = v.y; z = v.z; w = v.w; }
		~vec4() {}

		#pragma region MEMBER OVERLOADS
		void swap(vec4<T>& other) {
			std::swap(x, other.x);
			std::swap(y, other.y);
			std::swap(z, other.z);
			std::swap(w, other.w);
		}

		vec4<T>& operator=(vec4<T> rhs) {
			swap(rhs);
			return *this;
		}

		inline bool operator==(const vec4<T>& rhs) { return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w; }
		inline bool operator!=(const vec4<T>& rhs) { return !operator==(rhs); }

		vec4<T> operator-() const { 
			return vec4<T>(-x, -y, -z, -w);
		}

		vec4<T>& operator+=(const vec4<T>& rhs) {
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
			w += rhs.w;
			return *this;
		}

		vec4<T>& operator-=(const vec4<T>& rhs) {
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;
			w -= rhs.w;
			return *this;
		}

		vec4<T>& operator*=(const T& rhs) {
			x *= rhs;
			y *= rhs;
			z *= rhs;
			w *= rhs;
			return *this;
		}

		vec4<T>& operator/=(const T& rhs) {
			x /= rhs;
			y /= rhs;
			z /= rhs;
			w /= rhs;
			return *this;
		}
		#pragma endregion

		#pragma region MEMBER FUNCTIONS
		inline float magnitude() const {
			return std::sqrt(x*x + y*y + z*z + w*w);
		}

		inline float sqrMagnitude() const {
			return x*x + y*y + z*z + w*w;
		}

		inline vec4<T> normalized() const {
			float magnitude = this->magnitude();
			assert(magnitude != 0.0f);
			return vec4<T>(x, y, z, w) / magnitude;
		}

		inline float dot(const vec4<T>& v) const {
			return x * v.x + y * v.y + z * v.z + w * v.w;
		}

		inline vec3<T> cross(const vec4<T>& v) const {
			return vec3<T>(
				y * v.z - z * v.y,
				-(x * v.z - z * v.x),
				x * v.y - y * v.x
			);
		}
		#pragma endregion
	};

	#pragma region NON-MEMBER OVERLOADS
	template <typename T>
	inline vec4<T> operator+(vec4<T> lhs, const vec4<T>& rhs) {
		lhs += rhs;
		return lhs;
	}

	template <typename T>
	inline vec4<T> operator-(vec4<T> lhs, const vec4<T>& rhs) {
		lhs -= rhs;
		return lhs;
	}

	template <typename T>
	inline vec4<T> operator*(vec4<T> lhs, const T& rhs) {
		lhs *= rhs;
		return lhs;
	}

	template <typename T>
	inline vec4<T> operator*(const T& lhs, vec4<T> rhs) {
		rhs *= lhs;
		return rhs;
	}

	template <typename T> // both ways
	inline vec4<T> operator/(vec4<T> lhs, const T& rhs) {
		lhs /= rhs;
		return lhs;
	}

	template<typename T>
	inline std::ostream& operator<<(std::ostream &os, vec4<T> vec) { 
		os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")"; 
		return os; 
	}
	#pragma endregion

	typedef vec4<float> vec4f;
}

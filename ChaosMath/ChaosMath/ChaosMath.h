#pragma once

#include <assert.h>

// supported types:
// vec2f, vec3f, vec4f
// vec2i, vec3i, vec4i

// static functions
// lerp, pow, dot, cross

// make debug define to cull asserts

// convert from each type to each other type
// vec2 to vec3(vec2, 0)
// vec2 to vec4(vec2, 0, 0)
// vec3 to vec4(vec3, 0)

// vec3 to vec2(vec3.xy)
// vec4 to vec2(vec4.xy)
// vec4 to vec3(vec4.xyz)

namespace cm {
	template<typename T>
	T Max(T left, T right) {
		return right > left ? right : left;
	}

	template<typename T>
	T Min(T left, T right) {
		return right < left ? right : left;
	}

	float Clamp01(float t) {
		return Max(Min(1.0f, t), 0.0f);
	}

	namespace { // hide helper functions
		template<typename T> // we have a hidden inner version to disambiguate the Max functions named the same
		T InnerMax(T left, T right) {
			return Max(left, right);
		}
		template<typename T>
		T InnerMin(T left, T right) {
			return Min(left, right);
		}
	}

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

		inline bool operator==(const vec4<T>& rhs) const { return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w; }
		inline bool operator!=(const vec4<T>& rhs) const { return !operator==(rhs); }

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

		#pragma region STATIC FUNCTIONS
		static vec4<T> one()     { return vec4<T>(1, 1, 1, 1); }
		static vec4<T> zero()    { return vec4<T>(0, 0, 0, 0); }
		static vec4<T> right()   { return vec4<T>(1, 0, 0, 0); }
		static vec4<T> up()	     { return vec4<T>(0, 1, 0, 0); }
		static vec4<T> forward() { return vec4<T>(0, 0, 1, 0); }
		static vec4<T> ana()     { return vec4<T>(0, 0, 0, 1); }
		static vec4<T> left()    { return vec4<T>(-1, 0, 0, 0); }
		static vec4<T> down()    { return vec4<T>(0, -1, 0, 0); }
		static vec4<T> back()    { return vec4<T>(0, 0, -1, 0); }
		static vec4<T> kata()    { return vec4<T>(0, 0, 0, -1); }

		static float Angle(const vec4<T>& from, const vec4<T>& to) {
			float magFrom = from.magnitude();
			float magTo = to.magnitude();
			assert(magFrom != 0 && magTo != 0);
			float rhs = from.dot(to) / (magFrom * magTo);
			return std::acos(rhs);
		}

		static vec4<T> ClampMagnitude(const vec4<T>& vec, float magnitude) {
			assert(vec.magnitude() != 0);
			return vec.normalized() * magnitude;
		}

		static vec3<T> Cross(const vec4<T>& left, const vec4<T>& right) {
			return left.cross(right);
		}

		static float Distance(const vec4<T>& left, const vec4<T>& right) {
			float dx = left.x - right.x;
			float dy = left.y - right.y;
			float dz = left.z - right.z;
			float dw = left.w - right.w;

			return std::sqrt(dx * dx + dy * dy + dz * dz + dw * dw);
		}

		static float Dot(const vec4<T>& left, const vec4<T>& right) {
			return left.dot(right);
		}

		static vec4<T> Lerp(const vec4<T>& left, const vec4<T>& right, float t) {
			return left + Clamp01(t) * (right - left);
		}

		static vec4<T> LerpUnclamped(const vec4<T>& left, const vec4<T>& right, float t) {
			return left + t * (right - left);
		}

		static vec4<float> Max(const vec4<float>& left, const vec4<float>& right) {
			return vec4<T>(
				InnerMax(left.x, right.x),
				InnerMax(left.y, right.y),
				InnerMax(left.z, right.z),
				InnerMax(left.w, right.w)
			);
		}

		static vec4<T> Min(const vec4<T>& left, const vec4<T>& right) {
			return vec4<T>(
				InnerMin(left.x, right.x),
				InnerMin(left.y, right.y),
				InnerMin(left.z, right.z),
				InnerMin(left.w, right.w)
			);
		}

		static vec4<T> Normalize(const vec4<T>& vec) {
			assert(vec.magnitude() != 0);
			return vec.normalized();
		}

		static vec4<T> Scale(const vec4<T>& left, const vec4<T>& right) {
			return vec4<T>(
				left.x * right.x,
				left.y * right.y,
				left.z * right.z,
				left.w * right.w
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
	inline std::ostream& operator<<(std::ostream &os, const vec4<T> vec) { 
		os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")"; 
		return os; 
	}
	#pragma endregion

	typedef vec4<float> vec4f;
}

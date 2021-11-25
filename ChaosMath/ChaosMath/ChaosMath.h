#pragma once

// supported types:
// vec2f, vec3f, vec4f
// vec2i, vec3i, vec4i

// magnitude, magnitudeSquared, normalized
// dot, cross, 
// one, zero, up, down, left, right, forward, back, ana, kata

namespace cm {
	template <typename T>
	struct vec4 {
		T x, y, z, w;

		vec4() : vec4(0, 0, 0, 0) {}
		vec4(T all) : vec4(all, all, all, all) {}
		vec4(T _x, T _y, T _z, T _w) : x(_x), y(_y), z(_z), w(_w) { }
		vec4(const vec4& v) { x = v.x; y = v.y; z = v.z; w = v.w; }
		~vec4() {}

		void swap(vec4& other) {
			std::swap(x, other.x);
			std::swap(y, other.y);
			std::swap(z, other.z);
			std::swap(w, other.w);
		}

		vec4& operator=(vec4 rhs) {
			swap(rhs);
			return *this;
		}

		inline bool operator==(const vec4<T>& rhs) { return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w; }
		inline bool operator!=(const vec4<T>& rhs) { return !operator==(rhs); }

		vec4 operator-() const { 
			return vec4(-x, -y, -z, -w);
		}

		vec4& operator+=(const vec4& rhs) {
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
			w += rhs.w;
			return *this;
		}

		vec4& operator-=(const vec4& rhs) {
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;
			w -= rhs.w;
			return *this;
		}

		vec4& operator*=(const T& rhs) {
			x *= rhs;
			y *= rhs;
			z *= rhs;
			w *= rhs;
			return *this;
		}

		vec4& operator/=(const T& rhs) {
			x /= rhs;
			y /= rhs;
			z /= rhs;
			w /= rhs;
			return *this;
		}
	};

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

	typedef vec4<float> vec4f;
}

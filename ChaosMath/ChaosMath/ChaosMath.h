#pragma once

#define CHM_ENABLE_ASSERTS // use this define to manage asserts

#ifdef _MSC_VER
	#define DEBUG_BREAK __debugbreak()
#else
	#define DEBUG_BREAK 
#endif

#ifdef CHM_ENABLE_ASSERTS
	#define CHM_ASSERT(x) { if (!(x)) { DEBUG_BREAK; } }
#else
	#define CHM_ASSERT(x) 
#endif

namespace cm {
	#pragma region MATH FUNCS
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

	float Pow(float base, int exp) {
		if (exp == 0) {
			return 1;
		} else if (exp == 1) {
			return base;
		} else if ((exp & 1) != 0) {
			return base * Pow(base * base, exp / 2);
		} else {
			return Pow(base * base, exp / 2);
		}
	}

	#pragma region HELPER FUNCS
	namespace { // hide helper functions
		template<typename T> // we have a hidden inner version to disambiguate the Max functions named the same
		T InnerMax(T left, T right) {
			return Max(left, right);
		}
		template<typename T>
		T InnerMin(T left, T right) {
			return Min(left, right);
		}
		float InnerPow(float base, int exp) {
			return Pow(base, exp);
		}
	}
	#pragma endregion

	#pragma endregion

	// forward declarations of each vec size
	template <typename T>
	struct vec2;
	template <typename T>
	struct vec3;
	template <typename T>
	struct vec4;

	#pragma region VEC2
	template <typename T>
	struct vec2 {
		T x, y;

		vec2() : vec2<T>(0, 0) {}
		vec2(T all) : vec2<T>(all, all) {}
		vec2(T _x, T _y) : x(_x), y(_y) { }
		vec2(const vec2<T>& v) { x = v.x; y = v.y; }
		vec2(const vec3<T>& v) { x = v.x; y = v.y; }
		vec2(const vec4<T>& v) { x = v.x; y = v.y; }
		~vec2() {}

		#pragma region MEMBER OVERLOADS
		void swap(vec2<T>& other) {
			std::swap(x, other.x);
			std::swap(y, other.y);
		}

		vec2<T>& operator=(vec2<T> rhs) {
			swap(rhs);
			return *this;
		}

		inline bool operator==(const vec2<T>& rhs) const { return x == rhs.x && y == rhs.y; }
		inline bool operator!=(const vec2<T>& rhs) const { return !operator==(rhs); }

		vec2<T> operator-() const { 
			return vec2<T>(-x, -y);
		}

		vec2<T>& operator+=(const vec2<T>& rhs) {
			x += rhs.x;
			y += rhs.y;
			return *this;
		}

		vec2<T>& operator-=(const vec2<T>& rhs) {
			x -= rhs.x;
			y -= rhs.y;
			return *this;
		}

		vec2<T>& operator*=(const T& rhs) {
			x *= rhs;
			y *= rhs;
			return *this;
		}

		vec2<T>& operator/=(const T& rhs) {
			x /= rhs;
			y /= rhs;
			return *this;
		}
		#pragma endregion

		#pragma region MEMBER FUNCTIONS
		inline float magnitude() const {
			return std::sqrt(x*x + y*y);
		}

		inline float sqrMagnitude() const {
			return x*x + y*y;
		}

		inline vec2<T> normalized() const {
			float magnitude = this->magnitude();
			CHM_ASSERT(magnitude != 0.0f);
			return vec2<T>(x, y) / magnitude;
		}

		inline float dot(const vec2<T>& v) const {
			return x * v.x + y * v.y;
		}

		inline vec2<T> perpendicular() const {
			return vec2<T>(1, -x / y); // we choose 1 as x2, and then solve for y2 = -x1 / y1
		}

		#pragma endregion

		#pragma region STATIC FUNCTIONS
		static vec2<T> one()     { return vec2<T>(1, 1); }
		static vec2<T> zero()    { return vec2<T>(0, 0); }
		static vec2<T> right()   { return vec2<T>(1, 0); }
		static vec2<T> up()	     { return vec2<T>(0, 1); }
		static vec2<T> left()    { return vec2<T>(-1, 0); }
		static vec2<T> down()    { return vec2<T>(0, -1); }

		static float Angle(const vec2<T>& from, const vec2<T>& to) {
			float magFrom = from.magnitude();
			float magTo = to.magnitude();
			CHM_ASSERT(magFrom != 0 && magTo != 0);
			float rhs = from.dot(to) / (magFrom * magTo);
			return std::acos(rhs);
		}

		static vec2<T> ClampMagnitude(const vec2<T>& vec, float magnitude) {
			CHM_ASSERT(vec.magnitude() != 0);
			return vec.normalized() * magnitude;
		}

		static float Distance(const vec2<T>& left, const vec2<T>& right) {
			float dx = left.x - right.x;
			float dy = left.y - right.y;

			return std::sqrt(dx * dx + dy * dy);
		}

		static float Dot(const vec2<T>& left, const vec2<T>& right) {
			return left.dot(right);
		}

		static vec2<T> Lerp(const vec2<T>& left, const vec2<T>& right, float t) {
			return left + Clamp01(t) * (right - left);
		}

		static vec2<T> LerpUnclamped(const vec2<T>& left, const vec2<T>& right, float t) {
			return left + t * (right - left);
		}

		static vec2<float> Max(const vec2<float>& left, const vec2<float>& right) {
			return vec2<T>(
				InnerMax(left.x, right.x),
				InnerMax(left.y, right.y)
			);
		}

		static vec2<T> Min(const vec2<T>& left, const vec2<T>& right) {
			return vec2<T>(
				InnerMin(left.x, right.x),
				InnerMin(left.y, right.y)
			);
		}

		static vec2<T> Normalize(const vec2<T>& vec) {
			CHM_ASSERT(vec.magnitude() != 0);
			return vec.normalized();
		}

		static vec2<T> Perpendicular(const vec2<T>& vec) {
			return vec.perpendicular();
		}

		static vec2<T> Pow(const vec2<T>& vec, int e) {
			return vec2<T>(
				InnerPow(vec.x, e),
				InnerPow(vec.y, e)
			);
		}

		static vec2<T> Scale(const vec2<T>& left, const vec2<T>& right) {
			return vec2<T>(
				left.x * right.x,
				left.y * right.y
			);
		}
		#pragma endregion
	};

	#pragma region NON-MEMBER OVERLOADS
	template <typename T>
	inline vec2<T> operator+(vec2<T> lhs, const vec2<T>& rhs) {
		lhs += rhs;
		return lhs;
	}

	template <typename T>
	inline vec2<T> operator-(vec2<T> lhs, const vec2<T>& rhs) {
		lhs -= rhs;
		return lhs;
	}

	template <typename T>
	inline vec2<T> operator*(vec2<T> lhs, const T& rhs) {
		lhs *= rhs;
		return lhs;
	}

	template <typename T>
	inline vec2<T> operator*(const T& lhs, vec2<T> rhs) {
		rhs *= lhs;
		return rhs;
	}

	template <typename T> // both ways
	inline vec2<T> operator/(vec2<T> lhs, const T& rhs) {
		lhs /= rhs;
		return lhs;
	}

	template<typename T>
	inline std::ostream& operator<<(std::ostream &os, const vec2<T> vec) { 
		os << "(" << vec.x << ", " << vec.y << ")"; 
		return os; 
	}
	#pragma endregion

	#pragma endregion

	#pragma region VEC3
	template <typename T>
	struct vec3 {
		T x, y, z;

		vec3() : vec3<T>(0, 0, 0) {}
		vec3(T all) : vec3<T>(all, all, all) {}
		vec3(T _x, T _y, T _z) : x(_x), y(_y), z(_z) { }
		vec3(const vec2<T>& v) { x = v.x; y = v.y; z = 0; }
		vec3(const vec3<T>& v) { x = v.x; y = v.y; z = v.z; }
		vec3(const vec4<T>& v) { x = v.x; y = v.y; z = v.z; }
		~vec3() {}

		#pragma region MEMBER OVERLOADS
		void swap(vec3<T>& other) {
			std::swap(x, other.x);
			std::swap(y, other.y);
			std::swap(z, other.z);
		}

		vec3<T>& operator=(vec3<T> rhs) {
			swap(rhs);
			return *this;
		}

		inline bool operator==(const vec3<T>& rhs) const { return x == rhs.x && y == rhs.y && z == rhs.z; }
		inline bool operator!=(const vec3<T>& rhs) const { return !operator==(rhs); }

		vec3<T> operator-() const { 
			return vec3<T>(-x, -y, -z);
		}

		vec3<T>& operator+=(const vec3<T>& rhs) {
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
			return *this;
		}

		vec3<T>& operator-=(const vec3<T>& rhs) {
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;
			return *this;
		}

		vec3<T>& operator*=(const T& rhs) {
			x *= rhs;
			y *= rhs;
			z *= rhs;
			return *this;
		}

		vec3<T>& operator/=(const T& rhs) {
			x /= rhs;
			y /= rhs;
			z /= rhs;
			return *this;
		}
		#pragma endregion

		#pragma region MEMBER FUNCTIONS
		inline float magnitude() const {
			return std::sqrt(x*x + y*y + z*z);
		}

		inline float sqrMagnitude() const {
			return x*x + y*y + z*z;
		}

		inline vec3<T> normalized() const {
			float magnitude = this->magnitude();
			CHM_ASSERT(magnitude != 0.0f);
			return vec3<T>(x, y, z) / magnitude;
		}

		inline float dot(const vec3<T>& v) const {
			return x * v.x + y * v.y + z * v.z;
		}

		inline vec3<T> cross(const vec3<T>& v) const {
			return vec3<T>(
				y * v.z - z * v.y,
				-(x * v.z - z * v.x),
				x * v.y - y * v.x
			);
		}
		#pragma endregion

		#pragma region STATIC FUNCTIONS
		static vec3<T> one()     { return vec3<T>(1, 1, 1); }
		static vec3<T> zero()    { return vec3<T>(0, 0, 0); }
		static vec3<T> right()   { return vec3<T>(1, 0, 0); }
		static vec3<T> up()	     { return vec3<T>(0, 1, 0); }
		static vec3<T> forward() { return vec3<T>(0, 0, 1); }
		static vec3<T> left()    { return vec3<T>(-1, 0, 0); }
		static vec3<T> down()    { return vec3<T>(0, -1, 0); }
		static vec3<T> back()    { return vec3<T>(0, 0, -1); }

		static float Angle(const vec3<T>& from, const vec3<T>& to) {
			float magFrom = from.magnitude();
			float magTo = to.magnitude();
			CHM_ASSERT(magFrom != 0 && magTo != 0);
			float rhs = from.dot(to) / (magFrom * magTo);
			return std::acos(rhs);
		}

		static vec3<T> ClampMagnitude(const vec3<T>& vec, float magnitude) {
			CHM_ASSERT(vec.magnitude() != 0);
			return vec.normalized() * magnitude;
		}

		static vec3<T> Cross(const vec3<T>& left, const vec3<T>& right) {
			return left.cross(right);
		}

		static float Distance(const vec3<T>& left, const vec3<T>& right) {
			float dx = left.x - right.x;
			float dy = left.y - right.y;
			float dz = left.z - right.z;

			return std::sqrt(dx * dx + dy * dy + dz * dz);
		}

		static float Dot(const vec3<T>& left, const vec3<T>& right) {
			return left.dot(right);
		}

		static vec3<T> Lerp(const vec3<T>& left, const vec3<T>& right, float t) {
			return left + Clamp01(t) * (right - left);
		}

		static vec3<T> LerpUnclamped(const vec3<T>& left, const vec3<T>& right, float t) {
			return left + t * (right - left);
		}

		static vec3<float> Max(const vec3<float>& left, const vec3<float>& right) {
			return vec3<T>(
				InnerMax(left.x, right.x),
				InnerMax(left.y, right.y),
				InnerMax(left.z, right.z)
			);
		}

		static vec3<T> Min(const vec3<T>& left, const vec3<T>& right) {
			return vec3<T>(
				InnerMin(left.x, right.x),
				InnerMin(left.y, right.y),
				InnerMin(left.z, right.z)
			);
		}

		static vec3<T> Normalize(const vec3<T>& vec) {
			CHM_ASSERT(vec.magnitude() != 0);
			return vec.normalized();
		}

		static vec3<T> Pow(const vec3<T>& vec, int e) {
			return vec3<T>(
				InnerPow(vec.x, e),
				InnerPow(vec.y, e),
				InnerPow(vec.z, e)
			);
		}

		static vec3<T> Scale(const vec3<T>& left, const vec3<T>& right) {
			return vec3<T>(
				left.x * right.x,
				left.y * right.y,
				left.z * right.z
			);
		}
		#pragma endregion
	};

	#pragma region NON-MEMBER OVERLOADS
	template <typename T>
	inline vec3<T> operator+(vec3<T> lhs, const vec3<T>& rhs) {
		lhs += rhs;
		return lhs;
	}

	template <typename T>
	inline vec3<T> operator-(vec3<T> lhs, const vec3<T>& rhs) {
		lhs -= rhs;
		return lhs;
	}

	template <typename T>
	inline vec3<T> operator*(vec3<T> lhs, const T& rhs) {
		lhs *= rhs;
		return lhs;
	}

	template <typename T>
	inline vec3<T> operator*(const T& lhs, vec3<T> rhs) {
		rhs *= lhs;
		return rhs;
	}

	template <typename T> // both ways
	inline vec3<T> operator/(vec3<T> lhs, const T& rhs) {
		lhs /= rhs;
		return lhs;
	}

	template<typename T>
	inline std::ostream& operator<<(std::ostream &os, const vec3<T> vec) { 
		os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")"; 
		return os; 
	}
	#pragma endregion

	#pragma endregion

	#pragma region VEC4
	template <typename T>
	struct vec4 {
		T x, y, z, w;

		vec4() : vec4<T>(0, 0, 0, 0) {}
		vec4(T all) : vec4<T>(all, all, all, all) {}
		vec4(T _x, T _y, T _z, T _w) : x(_x), y(_y), z(_z), w(_w) { }
		vec4(const vec2<T>& v) { x = v.x; y = v.y; z = 0;   w = 0; }
		vec4(const vec3<T>& v) { x = v.x; y = v.y; z = v.z; w = 0; }
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
			CHM_ASSERT(magnitude != 0.0f);
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
			CHM_ASSERT(magFrom != 0 && magTo != 0);
			float rhs = from.dot(to) / (magFrom * magTo);
			return std::acos(rhs);
		}
		static vec4<T> ClampMagnitude(const vec4<T>& vec, float magnitude) {
			CHM_ASSERT(vec.magnitude() != 0);
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
			CHM_ASSERT(vec.magnitude() != 0);
			return vec.normalized();
		}
		static vec4<T> Pow(const vec4<T>& vec, int e) {
			return vec4<T>(
				InnerPow(vec.x, e),
				InnerPow(vec.y, e),
				InnerPow(vec.z, e),
				InnerPow(vec.w, e)
			);
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

	#pragma endregion

	// vec typedefs
	typedef vec2<float> vec2f;
	typedef vec3<float> vec3f;
	typedef vec4<float> vec4f;
	typedef vec2<int32_t> vec2i;
	typedef vec3<int32_t> vec3i;
	typedef vec4<int32_t> vec4i;
}


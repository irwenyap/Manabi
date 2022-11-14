#pragma once

//template<typename T>
//struct Vector2 {
//	union {
//		struct {
//			T x, y, z;
//		};
//	};
//
//	Vector2(Vector2<T>&&) = default;
//	Vector2(const Vector2<T>&) = default;
//
//	Vector2(const T& x, const T& y, const T& z) : x(x), y(y), z(z) {}
//};
//
//template<typename T>
//struct Vector3 {
//	union {
//		struct {
//			T x, y, z;
//		};
//	};
//
//	Vector3(Vector3<T>&&) = default;
//	Vector3(const Vector3<T>&) = default;
//
//	Vector3(const T& x, const T& y, const T& z) : x(x), y(y), z(z) {}
//};
//
//template<typename T>
//struct Vector4 {
//	union {
//		struct {
//			int x, y, z, w;
//		};
//	};
//
//	Vector4(int a, int b, int c, int d) : x(a), y(b), z(c), w(d) {}
//};
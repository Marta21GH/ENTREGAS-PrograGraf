#pragma once
#define M_PI 3.14159265358979323846
#include <iostream>
#include <cmath>

namespace libPRGR {

	typedef struct {
		union {
			struct { float x, y, z, w; };
		};
	} Vector4f;

	typedef struct {
		union {
			float matrix[4][4];
		};
	} Matrix4x4f;

	// Constructor de Vector4f
	inline Vector4f make_Vector4f(float x, float y, float z, float w) {
		return { x, y, z, w };
	}

	// Normalizar vector
	inline Vector4f normalize(Vector4f v) {
		float magnitude = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
		if (magnitude == 0) return { 0, 0, 0, v.w };
		return { v.x / magnitude, v.y / magnitude, v.z / magnitude, 0 };
	}

	// Producto escalar
	inline float operator*(Vector4f v1, Vector4f v2) {
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
	}

	// Producto cruzado
	inline Vector4f cross_product(Vector4f v1, Vector4f v2) {
		return {
			v1.y * v2.z - v1.z * v2.y,
			v1.z * v2.x - v1.x * v2.z,
			v1.x * v2.y - v1.y * v2.x,
			0.0f
		};
	}

	// Suma
	inline Vector4f operator+(Vector4f v1, Vector4f v2) {
		return { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w };
	}

	// Resta
	inline Vector4f operator-(Vector4f v1, Vector4f v2) {
		return { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w };
	}

	// Multiplicación Vector * escalar
	inline Vector4f operator*(const Vector4f& v, float scalar) {
		return { v.x * scalar, v.y * scalar, v.z * scalar, v.w * scalar };
	}

	// Multiplicación escalar * Vector
	inline Vector4f operator*(float scalar, const Vector4f& v) {
		return v * scalar;
	}

	// Matriz identidad
	inline Matrix4x4f make_identityf() {
		Matrix4x4f mat = { 0 };
		for (int i = 0; i < 4; i++) mat.matrix[i][i] = 1.0f;
		return mat;
	}

	// Matriz de translación
	inline Matrix4x4f make_translate(float x, float y, float z) {
		Matrix4x4f mat = make_identityf();
		mat.matrix[0][3] = x;
		mat.matrix[1][3] = y;
		mat.matrix[2][3] = z;
		return mat;
	}

	// Matriz de escala
	inline Matrix4x4f make_scale(float x, float y, float z) {
		Matrix4x4f mat = { 0 };
		mat.matrix[0][0] = x;
		mat.matrix[1][1] = y;
		mat.matrix[2][2] = z;
		mat.matrix[3][3] = 1.0f;
		return mat;
	}

	// Matriz de rotación (XYZ)
	inline Matrix4x4f make_rotation_xyz(float angleX, float angleY, float angleZ) {
		float cosX = std::cos(angleX), sinX = std::sin(angleX);
		float cosY = std::cos(angleY), sinY = std::sin(angleY);
		float cosZ = std::cos(angleZ), sinZ = std::sin(angleZ);

		Matrix4x4f mat = {
			.matrix {
				{ cosZ * cosY, cosZ * sinY * sinX - sinZ * cosX, cosZ * sinY * cosX + sinZ * sinX, 0 },
				{ sinZ * cosY, sinZ * sinY * sinX + cosZ * cosX, sinZ * sinY * cosX - cosZ * sinX, 0 },
				{ -sinY,       cosY * sinX,                      cosY * cosX,                      0 },
				{ 0, 0, 0, 1 }
			}
		};

		return mat;
	}

	// Multiplicación de matrices
	inline Matrix4x4f operator*(Matrix4x4f m1, Matrix4x4f m2) {
		Matrix4x4f res = { 0 };
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				for (int k = 0; k < 4; k++) {
					res.matrix[i][j] += m1.matrix[i][k] * m2.matrix[k][j];
				}
			}
		}
		return res;
	}

	// Multiplicación Matriz * Vector
	inline Vector4f operator*(Matrix4x4f m, Vector4f v) {
		Vector4f res;
		res.x = m.matrix[0][0] * v.x + m.matrix[0][1] * v.y + m.matrix[0][2] * v.z + m.matrix[0][3] * v.w;
		res.y = m.matrix[1][0] * v.x + m.matrix[1][1] * v.y + m.matrix[1][2] * v.z + m.matrix[1][3] * v.w;
		res.z = m.matrix[2][0] * v.x + m.matrix[2][1] * v.y + m.matrix[2][2] * v.z + m.matrix[2][3] * v.w;
		res.w = m.matrix[3][0] * v.x + m.matrix[3][1] * v.y + m.matrix[3][2] * v.z + m.matrix[3][3] * v.w;
		return res;
	}

	// Grados a radianes
	inline float toRadians(float angle) {
		return angle * M_PI / 180.0f;
	}

	// Distancia entre dos vectores
	inline float distance(Vector4f v1, Vector4f v2) {
		Vector4f d = v1 - v2;
		return std::sqrt(d.x * d.x + d.y * d.y + d.z * d.z);
	}

}

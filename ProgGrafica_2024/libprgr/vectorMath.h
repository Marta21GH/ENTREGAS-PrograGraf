#pragma once
#include <iostream>

namespace libPRGR {


	typedef struct {
		union {
			struct {
				float x, y, z, w;
			};
			struct {
				float r, g, b, a;
			};
			
			float data[4];
		};
		
	} vector4f;

	typedef struct {
		union {
			float mat2D[4][4];
			float mat1[16];
			vector4f rows[4];
		};

	} matrix4x4f;

	inline float operator* (vector4f v1, vector4f v2) {
		
		float res = 0;
		
		res = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
	
		return res;
	}

	inline vector4f operator* (matrix4x4f m1, vector4f v1) {

		vector4f res = { 0, 0, 0, 0 };


		for (int j = 0; j < 4; j++) {
			res.data[j] = m1.rows[j] * v1;
		}

		return res;
	}

	inline float toRadians(float angle) {
		return angle * 3.1416/(180.0f);
	}

	inline matrix4x4f makeTranslate(float x, float y, float z) {
		matrix4x4f m = { .rows = {{1,0,0,x},{0,1,0,y}, {0,0,1,z}, {0,0,0,1}} };
		return m;
	}

	inline std::ostream& operator<<(std::ostream& os, vector4f v1) {
		os << "{" << v1.data[0] << ", " << v1.data[1] << ", " << v1.data[2] << ", " << v1.data[3] << "}\n";

		return os;
	}

};
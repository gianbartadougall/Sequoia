#ifndef MATRIX_4F
#define MATRIX_4F

#include "vector4f.h"
using namespace vector4f;

namespace matrix4f {

	class Matrix4f {

		// Private variables go here
		public:
		float m[16];

		// Public variables and functions go here
		Matrix4f();
		Matrix4f(Vector4f p, Vector4f s, Vector4f r);
		Matrix4f(float a0, float a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8, float a9,
				 float a10, float a11, float a12, float a13, float a14, float a15);
		~Matrix4f();

		void print();
		// void scale(float scalar);

		// void add(Matrix4f* m1);
		// void subtract(Matrix4f* m1);
		void multiply(Matrix4f* m1);
		void transform(Vector4f p, Vector4f s, Vector4f r);

		protected:
	};
} // namespace matrix4f

#endif // MATRIX_4F
#ifndef MATRIX_4F
#define MATRIX_4F

#include "vector4f.h"
using namespace vector4f;

namespace matrix4f {

	class Matrix4f {

		// Private variables go here
		public:
		float m[4][4];

		// Public variables and functions go here
		Matrix4f();
		Matrix4f(Vector4f p, Vector4f s, Vector4f r);
		~Matrix4f();

		void scale(float scalar);
		void print();

		void add(Matrix4f* m1);
		void subtract(Matrix4f* m1);
		void multiply(Matrix4f* m1);

		protected:
	};
} // namespace matrix4f

#endif // MATRIX_4F
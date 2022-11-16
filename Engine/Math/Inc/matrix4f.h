#ifndef MATRIX_4F
#define MATRIX_4F

namespace matrix4f {

	class Matrix4f {

		// Private variables go here
		public:            
		float m[4][4];

		// Public variables and functions go here
		
		Matrix4f();
		~Matrix4f();

		void scale(float scalar);
		void print();

		void add(Matrix4f* m1);
		void subtract(Matrix4f* m1);
		void multiply(Matrix4f* m1);


		protected:

	};
}

#endif // MATRIX_4F
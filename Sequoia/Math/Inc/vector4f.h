#ifndef VECTOR4F
#define VECTOR4F

namespace vector4f {

	class Vector4f {

		public:
		float x;
		float y;
		float z;

		Vector4f();
		Vector4f(float x, float y, float z);
		~Vector4f();

		void set(float xi, float yi, float zi);
		void add(float xi, float yi, float zi);
		void subtract(Vector4f v);
		float dot(Vector4f v);
	};
} // namespace vector4f

#endif // VECTOR4F
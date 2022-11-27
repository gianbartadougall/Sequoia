#ifndef VECTOR4F_H
#define VECTOR4F_H

namespace vector4f {

	class Vector4f {

		public:
		float v[4];

		Vector4f();
		Vector4f(float x, float y, float z, float wi);
		~Vector4f();

		void add(Vector4f v1);
		void add(float xi, float yi, float zi, float wi);

		void subtract(Vector4f v1);
		void subtract(float xi, float yi, float zi, float wi);
		void set_x(float x);
		void set_y(float y);
		void set_z(float z);
		void set_w(float w);
	};
} // namespace vector4f

#endif // VECTOR4F_H
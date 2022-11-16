#ifndef VECTOR4F
#define VECTOR4F

using namespace vector4f {

    class Vector4f {

        public:

            float v[3];

            Vector4f();
            ~Vector4f();

            void add();
            void subtract();
            float dot();

            void print();
    } ;
}

#endif // VECTOR4F
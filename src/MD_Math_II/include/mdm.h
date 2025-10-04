#ifndef MDM_H
#define MDM_H

namespace mdm{
   namespace Common
   {
      //First Part
        float Pow(float x, float n);
        float Pow(float x, int n);

        int Factorial(int x);
        float Abs(float x);
        float Mod(float x, float y);

        float Ceil(float x);
        float Floor(float x);

        float Sqrt(float x);
        float Rsqrt(float x);

        float Exp(float x);
        float Ln(float x);
        double Ln(double x);
        float Log2(float x);
        float Log10(float x);
        float Ldexp(float x, int exponent);

        float Decompose(float x, int* integer);
        float Rexp(float x, int* exponent);
        
        float Sin(float x);
        float Cos(float x);
        float ArcSin(float x);
        float ArcCos(float x);
        float ArcTan(float x);
        float ArcTan2(float y, float x);
        float Sinh(float x);
        float Cosh(float x);
        float Tanh(float x);
      
      //Second Part
        float Max(float a, float b);
        float Min(float a, float b);
        float Hypot(float x, float y);

        float Cbrt(float x);
        float Expml(float x);
        float Lnlp(float x);

        float ArSinh(float x);
        float ArCosh(float x);
        float ArTanh(float x);

        int Trunc(float x);
        int Round(float x);

        float PosInf();
        float NegInf();

        bool Isfinite(float x);
        bool IsInf(float x);
        bool IsNaN(float x);
        bool IsNormal(float x);
        bool Signbit(float x);

        bool Equal(float a, float b);
        float ToRadian(float angle);
        float ToAngle(float radian);
   }

   namespace Vector
   {
    typedef struct Vec2
    {
      union
      {
          float coords[2];
          struct
          {
              float x, y;
          };
      };
        
        Vec2() : x(0.0f), y(0.0f){}
        Vec2(float x, float y) : x(x), y(y){};

        Vec2 operator + (const Vec2& v2);
        void operator += (const Vec2& v2);

        Vec2 operator - (const Vec2& v2);
        void operator -= (const Vec2& v2);

        float operator * (const Vec2& v2);
        Vec2 operator * (const float& f);
        void operator *= (const float& f);

        bool operator == (const Vec2& v2);
        bool operator != (const Vec2& v2);

        Vec2 operator - ();

    } Vec2;

    typedef struct Vec3
    {
      union
      {
          float coords[3];
          struct
          {
              float x, y, z;
          };
      };

        Vec3() : x(0.0f), y(0.0f), z(0.0f){}
        Vec3(float x, float y, float z) : x(x), y(y), z(z){};

        Vec3 operator + (const Vec3& v2);
        void operator += (const Vec3& v2);

        Vec3 operator - (const Vec3& v2);
        void operator -= (const Vec3& v2);

        float operator * (const Vec3& v2);
        Vec3 operator * (const float& f);
        void operator *= (const float& f);

        bool operator == (const Vec3& v2);
        bool operator != (const Vec3& v2);

        Vec3 operator - ();

    } Vec3;

    typedef struct Vec4
    {
      union
      {
          float coords[4];
          struct
          {
              float x, y, z, w;
          };
      };

        Vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f){}
        Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w){};

        Vec4 operator + (const Vec4& v2);
        void operator += (const Vec4& v2);

        Vec4 operator - (const Vec4& v2);
        void operator -= (const Vec4& v2);

        float operator * (const Vec4& v2);
        Vec4 operator * (const float& f);
        void operator *= (const float& f);

        bool operator == (const Vec4& v2);
        bool operator != (const Vec4& v2);

        Vec4 operator - ();
    }Vec4;

    typedef struct IVECTOR4 { // Just For Assimp
    int x, y, z, w;
    IVECTOR4() : x(0), y(0), z(0), w(0) {}
    IVECTOR4(int a, int b, int c, int d) : x(a), y(b), z(c), w(d) {}
    } IVECTOR4;

    typedef struct IVECTOR2 { // Just For FreeType
    int x, y;
    IVECTOR2() : x(0), y(0){}
    IVECTOR2(int a, int b) : x(a), y(b){}
    } IVECTOR2;

    Vec3 Cross(Vec3 v1, Vec3 v2);
   }

  namespace Matrix
  {
   typedef struct MATRIX
    {
      union
      {
          float coords[16];
          struct
          {
              float _11, _12, _13, _14,
                    _21, _22, _23, _24,
                    _31, _32, _33, _34,
                    _41, _42, _43, _44;
          };
      };

        MATRIX() : 
                  _11(0.0f), _12(0.0f), _13(0.0f), _14(0.0f), 
                  _21(0.0f), _22(0.0f), _23(0.0f), _24(0.0f), 
                  _31(0.0f), _32(0.0f), _33(0.0f), _34(0.0f), 
                  _41(0.0f), _42(0.0f), _43(0.0f), _44(0.0f){}

        MATRIX(
          float _11, float _12, float _13, float _14, 
          float _21, float _22, float _23, float _24,
          float _31, float _32, float _33, float _34,
          float _41, float _42, float _43, float _44) : 
                  _11(_11), _12(_12), _13(_13), _14(_14), 
                  _21(_21), _22(_22), _23(_23), _24(_24), 
                  _31(_31), _32(_32), _33(_33), _34(_34), 
                  _41(_41), _42(_42), _43(_43), _44(_44){};

        MATRIX operator + (const MATRIX& m2);      
        void operator += (const MATRIX& m2);    

        MATRIX operator - (const MATRIX& m2);      
        void operator -= (const MATRIX& m2);

        MATRIX operator * (const MATRIX& m2);
        void operator *= (const MATRIX& m2);

        MATRIX operator * (const float& f);
        void operator *= (const float& f);

        bool operator == (const MATRIX& m);
        bool operator != (const MATRIX& m);

        MATRIX operator - ();

    } MATRIX;

    float Det(MATRIX m);
    MATRIX Identity();
    MATRIX Transpose(MATRIX m);    
    MATRIX Adjoint(MATRIX m);
    MATRIX Inverse(MATRIX m);
    Vector::Vec4 MulVector(Vector::Vec4 v, MATRIX m);
  }

  namespace Quaternion
  {
    typedef struct QUATERNION
    {
        QUATERNION(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f, float _w = 1.0f);
        float x, y, z, w;

        QUATERNION operator + (const QUATERNION& q) const;
        void operator += (const QUATERNION& q);
        
        QUATERNION operator - (const QUATERNION& q) const;
        void operator -= (const QUATERNION& q);
        
        QUATERNION operator * (const QUATERNION& q) const;
        void operator *= (const QUATERNION& q);
        
        QUATERNION operator * (float scalar) const;
        void operator *= (float scalar);
        
        QUATERNION operator / (float scalar) const;
        void operator /= (float scalar);
        
        bool operator == (const QUATERNION& q) const;
        bool operator != (const QUATERNION& q) const;
        
        QUATERNION operator - () const;

    } QUATERNION;

    QUATERNION Conjugate(const QUATERNION& q);
    QUATERNION Inverse(const QUATERNION& q);
    float Dot(const QUATERNION& q1, const QUATERNION& q2);

    QUATERNION FromAxisAngle(Vector::Vec3 axis, float angle);
    QUATERNION FromEulerAngles(float pitch, float yaw, float roll);
    QUATERNION FromMatrix(const Matrix::MATRIX& m);

    Matrix::MATRIX MatrixFromQuaternion(const QUATERNION& q);
    Vector::Vec3 EulerAnglesFromQuaternion(const QUATERNION& q);

    Vector::Vec3 RotateVector(const QUATERNION& q, const Vector::Vec3& v);
    QUATERNION Slerp(const QUATERNION& q1, const QUATERNION& q2, float t);
    QUATERNION Lerp(const QUATERNION& q1, const QUATERNION& q2, float t);
  }

  namespace Plane
  {
    typedef struct PLANE  
    {
        float a,b,c,d;
    } PLANE;

    PLANE PlaneFromPointAndNormal(Vector::Vec3 Point,Vector::Vec3 Normal);

    PLANE PlaneFromPoints(Vector::Vec3 p0,
                          Vector::Vec3 p1,
                          Vector::Vec3 p2);
									  
    float PlaneDot(PLANE p, Vector::Vec3 v);
    PLANE PlaneTransform(PLANE p, Matrix::MATRIX m);
  }

  namespace Ray
  {
    typedef struct RAY
    {
        Vector::Vec3 p0,u;
    } RAY;

    Vector::Vec3 CreateRay(RAY ray,float t);
    Vector::Vec3 Intersection(RAY ray, Plane::PLANE p);
  }

  namespace General
  {
    float Mix(float x, float y, float a);
    Vector::Vec2 Mix(const Vector::Vec2& x, const Vector::Vec2& y, float a);
    Vector::Vec3 Mix(const Vector::Vec3& x, const Vector::Vec3& y, float a);
    Vector::Vec4 Mix(const Vector::Vec4& x, const Vector::Vec4& y, float a);
    Quaternion::QUATERNION Mix(const Quaternion::QUATERNION& q1, const Quaternion::QUATERNION& q2, float a);

    float Length(Vector::Vec2 v);
    float Length(Vector::Vec3 v);
    float Length(Vector::Vec4 v);
    float Length(const Quaternion::QUATERNION& q);

    Vector::Vec2 Normalize(Vector::Vec2 v);
    Vector::Vec3 Normalize(Vector::Vec3 v);
    Vector::Vec4 Normalize(Vector::Vec4 v);
    Quaternion::QUATERNION Normalize(const Quaternion::QUATERNION& q);
    Plane::PLANE Normalize(Plane::PLANE p);

    float ProjectionOfVector(Vector::Vec2 v1, Vector::Vec2 v2);
    float ProjectionOfVector(Vector::Vec3 v1, Vector::Vec3 v2);
    float ProjectionOfVector(Vector::Vec4 v1, Vector::Vec4 v2);

    Vector::Vec2 ProjectionVector(Vector::Vec2 v1, Vector::Vec2 v2);
    Vector::Vec3 ProjectionVector(Vector::Vec3 v1, Vector::Vec3 v2);
    Vector::Vec4 ProjectionVector(Vector::Vec4 v1, Vector::Vec4 v2);
  }

  namespace Transform
  {
    Matrix::MATRIX ScaleMatrix(float x, float y, float z);
    Matrix::MATRIX TranslationMatrix(float x, float y, float z);
    Matrix::MATRIX RotationMatrix(Vector::Vec3 Axis ,float Angle);
	
    Matrix::MATRIX PerspectiveMatrixRH(float fovy, float aspect, float zNear, float zFar);	
    Matrix::MATRIX OrthoMatrixRH(float l, float r, float b, float t, float n, float f);	
    Matrix::MATRIX ViewMatrixRH(Vector::Vec3 eye, Vector::Vec3 target, Vector::Vec3 up);	
	
    Matrix::MATRIX PerspectiveMatrixLH(float fovy, float aspect, float zNear, float zFar);
    Matrix::MATRIX OrthoMatrixLH(float l, float r, float b, float t, float n, float f);
    Matrix::MATRIX ViewMatrixLH(Vector::Vec3 eye, Vector::Vec3 target, Vector::Vec3 up);

    Matrix::MATRIX ReflectMatrix(Plane::PLANE p);	
    Matrix::MATRIX ShadowMatrix(Vector::Vec4 Light, Plane::PLANE p);	

    Matrix::MATRIX NormalMatrix(Matrix::MATRIX model);
    Matrix::MATRIX BillboardMatrix(const Vector::Vec3& position, const Matrix::MATRIX& view);
  }
}

#endif
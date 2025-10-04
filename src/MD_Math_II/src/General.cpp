#include <mdm.h>
#include <constants.h>

namespace mdm{
    namespace General
    {
        float Length(Vector::Vec2 v)
        {
            return Common::Hypot(v.x,v.y);
        }

        float Length(Vector::Vec3 v)
        {
            return Common::Sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
        }

        float Length(Vector::Vec4 v)
        {
            return Common::Sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
        }

        float Length(const Quaternion::QUATERNION& q)
        {
            return Common::Sqrt(q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w);
        }

        Vector::Vec2 Normalize(Vector::Vec2 v)
        {
            Vector::Vec2 r;
            r.x = v.x * Common::Rsqrt(v.x*v.x + v.y * v.y); 
            r.y = v.y * Common::Rsqrt(v.x*v.x + v.y * v.y); 
            return r;
        }

        Vector::Vec3 Normalize(Vector::Vec3 v)
        {
            Vector::Vec3 r;
            r.x = v.x * Common::Rsqrt(v.x*v.x + v.y * v.y + v.z * v.z); 
            r.y = v.y * Common::Rsqrt(v.x*v.x + v.y * v.y + v.z * v.z); 
            r.z = v.z * Common::Rsqrt(v.x*v.x + v.y * v.y + v.z * v.z); 
            return r;
        }

        Vector::Vec4 Normalize(Vector::Vec4 v)
        {
            Vector::Vec4 r;
            r.x = v.x * Common::Rsqrt(v.x*v.x + v.y * v.y + v.z * v.z + v.w * v.w); 
            r.y = v.y * Common::Rsqrt(v.x*v.x + v.y * v.y + v.z * v.z + v.w * v.w);
            r.z = v.z * Common::Rsqrt(v.x*v.x + v.y * v.y + v.z * v.z + v.w * v.w); 
            r.w = v.w * Common::Rsqrt(v.x*v.x + v.y * v.y + v.z * v.z + v.w * v.w);  
            return r;
        }

        Quaternion::QUATERNION Normalize(const Quaternion::QUATERNION& q)
        {
            float len = Length(q);
            if (len < MDM_EPSILON) {
                return Quaternion::QUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
            }
            return q / len;
        }

        Plane::PLANE Normalize(Plane::PLANE p)
        {
            Plane::PLANE r;
            float nn;

            nn = Common::Rsqrt(p.a * p.a + p.b * p.b + p.c * p.c);

            r.a = nn * p.a;
            r.b = nn * p.b;
            r.c = nn * p.c;
            r.d = nn * p.d;

            return r;
        }

        float Mix(float x, float y, float a)
        {
            return x * (1.0f - a) + y * a;
        }

        Vector::Vec2 Mix(const Vector::Vec2& x, const Vector::Vec2& y, float a)
        {
            return Vector::Vec2(
                Mix(x.x, y.x, a),
                Mix(x.y, y.y, a)
            );
        }

        Vector::Vec3 Mix(const Vector::Vec3& x, const Vector::Vec3& y, float a)
        {
            return Vector::Vec3(
                Mix(x.x, y.x, a),
                Mix(x.y, y.y, a),
                Mix(x.z, y.z, a)
            );
        }

        Vector::Vec4 Mix(const Vector::Vec4& x, const Vector::Vec4& y, float a)
        {
            return Vector::Vec4(
                Mix(x.x, y.x, a),
                Mix(x.y, y.y, a),
                Mix(x.z, y.z, a),
                Mix(x.w, y.w, a)
            );
        }

        Quaternion::QUATERNION Mix(const Quaternion::QUATERNION& q1, const Quaternion::QUATERNION& q2, float a)
        {
            Quaternion::QUATERNION result(
                Mix(q1.x, q2.x, a),
                Mix(q1.y, q2.y, a),
                Mix(q1.z, q2.z, a),
                Mix(q1.w, q2.w, a)
            );
        
            return Normalize(result);
        }

        float ProjectionOfVector(Vector::Vec2 v1, Vector::Vec2 v2)
        {
            return 
            Length(v1) * 
            Common::Cos(Common::ArcCos((v1*v2) * Common::Rsqrt(v1.x * v1.x + v1.y * v1.y)*
            Common::Rsqrt(v2.x* v2.x + v2.y*v2.y )))
            ;
        }

        float ProjectionOfVector(Vector::Vec3 v1, Vector::Vec3 v2)
        {
            return 
            Length(v1) * 
            Common::Cos(Common::ArcCos((v1*v2) * Common::Rsqrt(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z)*
                Common::Rsqrt(v2.x* v2.x + v2.y*v2.y + v2.z * v2.z)))
            ;
        }

        float ProjectionOfVector(Vector::Vec4 v1, Vector::Vec4 v2)
        {
            return 
            Length(v1) * 
            Common::Cos(Common::ArcCos((v1*v2) * Common::Rsqrt(v1.x * v1.x + v1.y * v1.y+ v1.z * v1.z+ v1.w * v1.w)*
                Common::Rsqrt(v2.x* v2.x + v2.y*v2.y + v1.z * v1.z+ v1.w * v1.w)))
            ;
        }

        Vector::Vec2 ProjectionVector(Vector::Vec2 v1, Vector::Vec2 v2)
        {
            Vector::Vec2 r = Normalize(v2);
            return r * ProjectionOfVector(v1,v2);
        }

        Vector::Vec3 ProjectionVector(Vector::Vec3 v1, Vector::Vec3 v2)
        {
            Vector::Vec3 r = Normalize(v2);
            return r * ProjectionOfVector(v1,v2);
        }

        Vector::Vec4 ProjectionVector(Vector::Vec4 v1, Vector::Vec4 v2)
        {
            Vector::Vec4 r = Normalize(v2);
            return r * ProjectionOfVector(v1,v2);
        }
    }
}
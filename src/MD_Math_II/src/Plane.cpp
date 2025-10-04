#include <mdm.h>

namespace mdm
{
    namespace Plane
    {
        PLANE PlaneFromPointAndNormal(Vector::Vec3 Point,Vector::Vec3 Normal)
        {
            PLANE plane;
            plane.a = Point.x;
            plane.b = Point.y;
            plane.c = Point.z;
            plane.d = (-1.0f) * (Normal * Point);

            return plane;
        }
									  
    float PlaneDot(PLANE p, Vector::Vec3 v)
    {
        Vector::Vec3 n;
        float r;
        n.x = p.a;
        n.y = p.b;
        n.y = p.c;

        r = (n * v) + p.d;
        return r;
    }

    PLANE PlaneFromPoints(Vector::Vec3 p0,
                          Vector::Vec3 p1,
                          Vector::Vec3 p2)
    {
        Plane::PLANE plane;
        Vector::Vec3 u = p1 - p0;
        Vector::Vec3 v = p2 - p0;
        Vector::Vec3 n = Vector::Cross(u,v);

        plane.a = n.x;
        plane.b = n.y;
        plane.c = n.z;
        plane.d = (-1.0f) * (n * p0);

        return plane;
    }  

    PLANE PlaneTransform(PLANE p, Matrix::MATRIX m)
    {
        Plane::PLANE r;
        Vector::Vec4 pp;
        p = General::Normalize(p);

        pp.x = p.a;
        pp.y = p.b;
        pp.z = p.c;
        pp.w = p.d;

        m = Matrix::Inverse(m);
        m = Matrix::Transpose(m);

        pp = Matrix::MulVector(pp, m);

        r.a = pp.x;
        r.b = pp.y;
        r.c = pp.z;
        r.d = pp.w;

        return r;
    }                    

    }
}
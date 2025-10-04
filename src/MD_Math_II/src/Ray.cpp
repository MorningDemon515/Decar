#include <mdm.h>

namespace mdm
{
    namespace Ray{
        Vector::Vec3 CreateRay(RAY ray,float t)
        {
            Vector::Vec3 r(0.0f, 0.0f, 0.0f);

        if(t < 0.0f)
        {
            r.x = 0.0f;
            r.y = 0.0f;
            r.z = 0.0f;
            return r;
        }

        r = ray.p0 + ray.u * t;

        return r;
        }

        Vector::Vec3 Intersection(RAY ray, Plane::PLANE p)
        {
            Vector::Vec3 r, n;
        n.x = p.a;
        n.y = p.b;
        n.z = p.c;
        float t;

        t = ((-1) * p.d - (n * ray.p0))/(n * ray.u);

        r = ray.p0 + ray.u * t;

        return r;
        }
    }
}
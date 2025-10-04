#include <mdm.h>

namespace mdm{
   namespace Vector
   {

//Vector 2---------------------------------
    Vec2 Vec2::operator + (const Vec2& v2)
    {
		Vec2 temp(x + v2.x, y + v2.y);
        return temp;
    }

    void Vec2::operator += (const Vec2& v2)
    {
        x = x + v2.x;
        y = y + v2.y;
    }

    Vec2 Vec2::operator - (const Vec2& v2)
    {
		Vec2 temp(x - v2.x, y - v2.y);
        return temp;
    }

    void Vec2::operator -= (const Vec2& v2)
    {
        x = x - v2.x;
        y = y - v2.y;
    }

    float Vec2::operator * (const Vec2& v2)
    {
        return 
           x * v2.x +
           y * v2.y
        ;
    }

    Vec2 Vec2::operator * (const float& f)
    {
		Vec2 temp(f * x,
            f * y);
        return temp;
    }

    void Vec2::operator *= (const float& f)
    {
        x = f * x;
        y = f * y;
    }

    bool Vec2::operator == (const Vec2& v2)
    {
        if(
            Common::Equal(x,v2.x) &&
            Common::Equal(y,v2.y)
        )
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool Vec2::operator != (const Vec2& v2)
    {
        if(!(
            Common::Equal(x,v2.x) &&
            Common::Equal(y,v2.y)
            )
        )
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    Vec2 Vec2::operator - ()
    {
		Vec2 temp(
			-1.0f * x,
            -1.0f * y
			);
        return temp;
    }
//Vec3 ---------------------------------------

    Vec3 Vec3::operator + (const Vec3& v2)
    {
		Vec3 temp(x + v2.x,
            y + v2.y,
            z + v2.z);
        return temp;
    }

    void Vec3::operator += (const Vec3& v2)
    {
        x = x + v2.x;
        y = y + v2.y;
        z = z + v2.z;
    }

    Vec3 Vec3::operator - (const Vec3& v2)
    {
		Vec3 temp(
            x - v2.x,
            y - v2.y,
            z - v2.z
			);
        return temp;
    }

    void Vec3::operator -= (const Vec3& v2)
    {
        x = x - v2.x;
        y = y - v2.y;
        z = z - v2.z;
    }

    float Vec3::operator * (const Vec3& v2)
    {
        return 
            x * v2.x + y * v2.y + z * v2.z 
        ;
    }

    Vec3 Vec3::operator * (const float& f)
    {
		Vec3 temp(
			f * x,
            f * y,
            f * z
			);
        return temp;
    }

    void Vec3::operator *= (const float& f)
    {
        x = f * x;
        y = f * y;
        z = f * z;
    }

    bool Vec3::operator == (const Vec3& v2)
    {
        if(
            Common::Equal(x,v2.x) &&
            Common::Equal(y,v2.y) &&
            Common::Equal(z,v2.z) 
        )
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool Vec3::operator != (const Vec3& v2)
    {
        if(!(
            Common::Equal(x,v2.x) &&
            Common::Equal(y,v2.y) &&
            Common::Equal(z,v2.z) 
        )
        )
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    Vec3 Vec3::operator - ()
    {
		Vec3 temp(
			-1.0f * x,
            -1.0f * y,
            -1.0f * z
			);
        return temp;
    }
//Vec4----------------------------------------------------
    Vec4 Vec4::operator + (const Vec4& v2)
    {
		Vec4 temp(
			x + v2.x,
            y + v2.y,
            z + v2.z,
            w + v2.w
			);
        return temp;
    }

    void Vec4::operator += (const Vec4& v2)
    {
        x = x + v2.x;
        y = y + v2.y;
        z = z + v2.z;
        w = w + v2.w;
    }

    Vec4 Vec4::operator - (const Vec4& v2)
    {
		Vec4 temp(
			x - v2.x,
            y - v2.y,
            z - v2.z,
            w - v2.w
			);
        return temp;
    }
 
    void Vec4::operator -= (const Vec4& v2)
    {
        x = x - v2.x;
       y = y - v2.y;
        z = z - v2.z;
        w = w - v2.w;
    }

    float Vec4::operator * (const Vec4& v2)
    {
        return x * v2.x + y * v2.y + z * v2.z + w * v2.w;
    }

    Vec4 Vec4::operator * (const float& f)
    {
		Vec4 temp(
			f * x,
            f * y,
            f * z,
            f * w
			);
        return temp;
    }

    void Vec4::operator *= (const float& f)
    {
        x = f * x;
        y = f * y;
        z = f * z;
        w = f * w;
    }

    bool Vec4::operator == (const Vec4& v2)
    {
        if(
            Common::Equal(x,v2.x) &&
            Common::Equal(y,v2.y) &&
            Common::Equal(z,v2.z) &&
            Common::Equal(w,v2.w)
        )
        {
            return true;
        }
        else
        {
            return false;
        }    
    }

    bool Vec4::operator != (const Vec4& v2)
    {
        if(!(
            Common::Equal(x,v2.x) &&
            Common::Equal(y,v2.y) &&
            Common::Equal(z,v2.z) &&
            Common::Equal(w,v2.w)
        )
        )
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    Vec4 Vec4::operator - ()
    {
		Vec4 temp(
			-1.0f * x,
            -1.0f * y,
            -1.0f * z,
            -1.0f * w
			);
        return temp;
    }

    Vec3 Cross(Vec3 v1, Vec3 v2)
    {
        Vec3 r;
        r.x = v1.y * v2.z - v2.y * v1.z;
        r.y = v1.z * v2.x - v2.z * v1.x;
        r.z = v1.x * v2.y - v2.x * v1.y;
        return r;
    }
   }
}
#include <mdm.h>
#include <constants.h>

namespace mdm{
    namespace Matrix
    {
        typedef struct MATRIX2x2
        {
            float _11, _12, 
                  _21, _22;
        } MATRIX2x2;

        typedef struct MATRIX3x3
        {
            float _11, _12, _13,
                  _21, _22, _23,
                  _31, _32, _33;
        } MATRIX3x3;

        //Tool Function
    float DetMatrix2x2(MATRIX2x2 m)
    {
        return m._11 * m._22 - m._12 * m._21;
    }

    float DetMatrix3x3(MATRIX3x3 m)
    {
        MATRIX2x2 m1 = {m._22,m._23,
                        m._32,m._33};

        MATRIX2x2 m2 = {m._21,m._23,
                        m._31,m._33};

        MATRIX2x2 m3 = {m._21,m._22,
                        m._31,m._32};

        return m._11 * DetMatrix2x2(m1) - m._12 * DetMatrix2x2(m2) + m._13 * DetMatrix2x2(m3);  
    }

    float DetMatrix4x4(MATRIX m)
    {
        MATRIX3x3 m1 = {m._22,m._23,m._24,
                        m._32,m._33,m._34,
                        m._42,m._43,m._44};       

        MATRIX3x3 m2 = {m._21,m._23,m._24,
                        m._31,m._33,m._34,
                        m._41,m._43,m._44};

        MATRIX3x3 m3 = {m._21,m._22,m._24,
                        m._31,m._32,m._34,
                        m._41,m._42,m._44};      

        MATRIX3x3 m4 = {m._21,m._22,m._23,
                        m._31,m._32,m._33,
                        m._41,m._42,m._43};

        return m._11 * DetMatrix3x3(m1) - m._12 * DetMatrix3x3(m2) + m._13 * DetMatrix3x3(m3) - m._14 *DetMatrix3x3(m4);                                                                                                                                                
    }

        MATRIX MATRIX::operator + (const MATRIX& m2)
        {
            return MATRIX(
		    	_11 + m2._11, _12 + m2._12, _13 + m2._13, _14 + m2._14,
                _21 + m2._21, _22 + m2._22, _23 + m2._23, _24 + m2._24,
                _31 + m2._31, _32 + m2._32, _33 + m2._33, _34 + m2._34,
                _41 + m2._41, _42 + m2._42, _43 + m2._43, _44 + m2._44
		    );

        }  

    void MATRIX::operator += (const MATRIX& m2)
    {
        _11 = _11 + m2._11;
        _21 = _21 + m2._21;
        _31 = _31 + m2._31;
        _41 = _41 + m2._41;

        _12 = _12 + m2._12;
        _22 = _22 + m2._22;
        _32 = _32 + m2._32;
        _42 = _42 + m2._42;
    
       _13 = _13 + m2._13;
       _23 = _23 + m2._23;
       _33 = _33 + m2._33;
       _43 = _43 + m2._43;

       _14 = _14 + m2._14;
       _24 = _24 + m2._24;
       _34 = _34 + m2._34;
       _44 = _44 + m2._44;
    }  

    MATRIX MATRIX::operator - (const MATRIX& m2)
    {
		return MATRIX(
			_11 - m2._11, _12 - m2._12, _13 - m2._13, _14 - m2._14,
            _21 - m2._21, _22 - m2._22, _23 - m2._23, _24 - m2._24,
            _31 - m2._31, _32 - m2._32, _33 - m2._33, _34 - m2._34,
            _41 - m2._41, _42 - m2._42, _43 - m2._43, _44 - m2._44

		);
    }   

    void MATRIX::operator -= (const MATRIX& m2)
    {
        _11 = _11 - m2._11;
        _21 = _21 - m2._21;
        _31 = _31 - m2._31;
        _41 = _41 - m2._41;

        _12 = _12 - m2._12;
        _22 = _22 - m2._22;
        _32 = _32 - m2._32;
        _42 = _42 - m2._42;
    
        _13 = _13 - m2._13;
        _23 = _23 - m2._23;
        _33 = _33 - m2._33;
        _43 = _43 - m2._43;

        _14 = _14 - m2._14;
        _24 = _24 - m2._24;
        _34 = _34 - m2._34;
        _44 = _44 - m2._44;
    } 

    MATRIX MATRIX::operator * (const MATRIX& m2)
    {
		MATRIX temp;

    temp._11 = _11*m2._11 + _12*m2._21 + _13*m2._31 + _14*m2._41;
    temp._12 = _11*m2._12 + _12*m2._22 + _13*m2._32 + _14*m2._42;
    temp._13 = _11*m2._13 + _12*m2._23 + _13*m2._33 + _14*m2._43;
    temp._14 = _11*m2._14 + _12*m2._24 + _13*m2._34 + _14*m2._44;
    

    temp._21 = _21*m2._11 + _22*m2._21 + _23*m2._31 + _24*m2._41;
    temp._22 = _21*m2._12 + _22*m2._22 + _23*m2._32 + _24*m2._42;
    temp._23 = _21*m2._13 + _22*m2._23 + _23*m2._33 + _24*m2._43;
    temp._24 = _21*m2._14 + _22*m2._24 + _23*m2._34 + _24*m2._44;
    
    temp._31 = _31*m2._11 + _32*m2._21 + _33*m2._31 + _34*m2._41;
    temp._32 = _31*m2._12 + _32*m2._22 + _33*m2._32 + _34*m2._42;
    temp._33 = _31*m2._13 + _32*m2._23 + _33*m2._33 + _34*m2._43;
    temp._34 = _31*m2._14 + _32*m2._24 + _33*m2._34 + _34*m2._44;
    
    temp._41 = _41*m2._11 + _42*m2._21 + _43*m2._31 + _44*m2._41;
    temp._42 = _41*m2._12 + _42*m2._22 + _43*m2._32 + _44*m2._42;
    temp._43 = _41*m2._13 + _42*m2._23 + _43*m2._33 + _44*m2._43;
    temp._44 = _41*m2._14 + _42*m2._24 + _43*m2._34 + _44*m2._44;
    
    return temp;
    }

    void MATRIX::operator *= (const MATRIX& m2)
    {
        MATRIX temp = *this * m2;
        *this = temp;
    }

    MATRIX MATRIX::operator * (const float& f)
    {
		return MATRIX(
			f * _11, f * _12, f * _13, f * _14,
            f * _21, f * _22, f * _23, f * _24,
            f * _31, f * _32, f * _33, f * _34,
            f * _41, f * _42, f * _43, f * _44     
		);
    }

    void MATRIX::operator *= (const float& f)
    {
        _11 = f * _11; 
        _21 = f * _21; 
        _31 = f * _31; 
        _41 = f * _41; 

        _12 = f * _12; 
        _22 = f * _22; 
        _32 = f * _32; 
        _42 = f * _42; 

        _13 = f * _13; 
        _23 = f * _23; 
        _33 = f * _33; 
        _43 = f * _43; 

        _14 = f * _14; 
        _24 = f * _24; 
        _34 = f * _34; 
        _44 = f * _44; 
    }

    bool MATRIX::operator == (const MATRIX& m)
    {
        if(
            Common::Equal(_11,m._11) &&
            Common::Equal(_21,m._21) &&
            Common::Equal(_31,m._31) &&
            Common::Equal(_41,m._41) &&

            Common::Equal(_12,m._12) &&
            Common::Equal(_22,m._22) &&
            Common::Equal(_32,m._32) &&
            Common::Equal(_42,m._42) &&

            Common::Equal(_13,m._13) &&
            Common::Equal(_23,m._23) &&
            Common::Equal(_33,m._33) &&
            Common::Equal(_43,m._43) &&

            Common::Equal(_14,m._14) &&
            Common::Equal(_24,m._24) &&
            Common::Equal(_34,m._34) &&
            Common::Equal(_44,m._44) 
        )
        {
            return true;
        }
        else{
            return false;
        }
    }

    bool MATRIX::operator != (const MATRIX& m)
    {
        if(!(
            Common::Equal(_11,m._11) &&
            Common::Equal(_21,m._21) &&
            Common::Equal(_31,m._31) &&
            Common::Equal(_41,m._41) &&

            Common::Equal(_12,m._12) &&
            Common::Equal(_22,m._22) &&
            Common::Equal(_32,m._32) &&
            Common::Equal(_42,m._42) &&

            Common::Equal(_13,m._13) &&
            Common::Equal(_23,m._23) &&
            Common::Equal(_33,m._33) &&
            Common::Equal(_43,m._43) &&

            Common::Equal(_14,m._14) &&
            Common::Equal(_24,m._24) &&
            Common::Equal(_34,m._34) &&
            Common::Equal(_44,m._44) 
        )
        )
        {
            return true;
        }
        else{
            return false;
        }
    }

    MATRIX MATRIX::operator - ()
    {
		return MATRIX(
			-1.0f * _11, -1.0f * _12, -1.0f * _13, -1.0f * _14,
            -1.0f * _21, -1.0f * _22, -1.0f * _23, -1.0f * _24,
            -1.0f * _31, -1.0f * _32, -1.0f * _33, -1.0f * _34,
            -1.0f * _41, -1.0f * _42, -1.0f * _43, -1.0f * _44
		);
    }

    MATRIX Identity()
    {
        return MATRIX(
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        );
    }

    MATRIX Transpose(MATRIX m)
    {
        MATRIX r;

        r._11 = m._11;
        r._21 = m._12;
        r._31 = m._13;
        r._41 = m._14;

        r._12 = m._21;
        r._22 = m._22;
        r._32 = m._23;
        r._42 = m._24;

        r._13 = m._31;
        r._23 = m._32;
        r._33 = m._33;
        r._43 = m._34;

        r._14 = m._41;
        r._24 = m._42;
        r._34 = m._43;
        r._44 = m._44;
    
        return r;
    }   

    MATRIX Adjoint(MATRIX m)
    {
        MATRIX rm;
        MATRIX adj;      
 
        MATRIX3x3 m1 = {m._22, m._23,m._24,
                        m._32,m._33,m._34,
                        m._42,m._43,m._44};
        MATRIX3x3 m2 = {m._21,m._23,m._24,
                        m._31,m._33,m._34,
                        m._41,m._43,m._44};
        MATRIX3x3 m3 = {m._21,m._22,m._24,
                        m._31,m._32,m._34,
                        m._41,m._42,m._44};
        MATRIX3x3 m4 = {m._21,m._22,m._23,
                        m._31,m._32,m._33,
                        m._41,m._42,m._43};

        MATRIX3x3 m5 = {m._12,m._13,m._14,
                        m._32,m._33,m._34,
                        m._42,m._43,m._44};
        MATRIX3x3 m6 = {m._11,m._13,m._14,
                        m._31,m._33,m._34,
                        m._41,m._43,m._44};
        MATRIX3x3 m7 = {m._11,m._12,m._14,
                        m._31,m._32,m._34,
                        m._41,m._42,m._44};
        MATRIX3x3 m8 = {m._11,m._12,m._13,
                        m._31,m._32,m._33,
                        m._41,m._42,m._43};

        MATRIX3x3 m9 = {m._12,m._13,m._14,
                        m._22,m._23,m._24,
                        m._42,m._43,m._44};
        MATRIX3x3 m10 = {m._12,m._13,m._14,
                        m._21,m._23,m._24,
                        m._41,m._43,m._44};
        MATRIX3x3 m11 = {m._11,m._12,m._14,
                        m._21,m._22,m._24,
                        m._41,m._42,m._44};
        MATRIX3x3 m12 = {m._11,m._12,m._13,
                        m._21,m._22,m._23,
                        m._41,m._42,m._43};

        MATRIX3x3 m13 = {m._12,m._13,m._14,
                        m._22,m._23,m._24,
                        m._32,m._33,m._34};
        MATRIX3x3 m14 = {m._11,m._13,m._14,
                        m._21,m._23,m._24,
                        m._31,m._33,m._34};
        MATRIX3x3 m15 = {m._11,m._12,m._14,
                        m._21,m._22,m._24,
                        m._31,m._32,m._34};
        MATRIX3x3 m16 = {m._11,m._12,m._13,
                        m._21,m._22,m._23,
                        m._31,m._32,m._33};

        rm._11 = DetMatrix3x3(m1);
        rm._12 = (-1) * DetMatrix3x3(m2);
        rm._13 = DetMatrix3x3(m3);
        rm._14 = (-1) * DetMatrix3x3(m4);

        rm._21 = (-1) * DetMatrix3x3(m5);
        rm._22 = DetMatrix3x3(m6);
        rm._23 = (-1) * DetMatrix3x3(m7);
        rm._24 = DetMatrix3x3(m8);

        rm._31 = DetMatrix3x3(m9);
        rm._32 = (-1) * DetMatrix3x3(m10);
        rm._33 = DetMatrix3x3(m11);
        rm._34 = (-1) * DetMatrix3x3(m12);

        rm._41 = (-1) * DetMatrix3x3(m13);
        rm._42 = DetMatrix3x3(m14);
        rm._43 = (-1) * DetMatrix3x3(m15);
        rm._44 = DetMatrix3x3(m16);

        adj._11 = rm._11;
        adj._12 = rm._21;
        adj._13 = rm._31;
        adj._14 = rm._41;

        adj._21 = rm._12;
        adj._22 = rm._22;
        adj._23 = rm._32;
        adj._24 = rm._42;

        adj._31 = rm._13;
        adj._32 = rm._23;
        adj._33 = rm._33;
        adj._34 = rm._43;

        adj._41 = rm._14;
        adj._42 = rm._24;
        adj._43 = rm._34;
        adj._44 = rm._44;

        return adj;
    }

    MATRIX Inverse(MATRIX m)
    {
        MATRIX Inv,adj;
   
       float det = DetMatrix4x4(m);

       if(Common::Abs(det) < MDM_EPSILON)
       {
        return Identity();
       }

       float _1det = 1.0f / det;
       adj = Adjoint(m);

       Inv = adj * _1det;
    
        return Inv;
    }

    float Det(MATRIX m)
    {
        return DetMatrix4x4(m);
    }

    Vector::Vec4 MulVector(Vector::Vec4 v, MATRIX m)
    {
        Vector::Vec4 temp(
			v.x * m._11 + v.y * m._12 + v.z * m._13 + v.w * m._14,
            v.x * m._21 + v.y * m._22 + v.z * m._23 + v.w * m._24,
            v.x * m._31 + v.y * m._32 + v.z * m._33 + v.w * m._34,
            v.x * m._41 + v.y * m._42 + v.z * m._43 + v.w * m._44
			);
        return temp;
    }

    }
}
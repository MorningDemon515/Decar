#include <mdm.h>
#include <constants.h>

namespace mdm{
    namespace Quaternion
    {
        QUATERNION::QUATERNION(float _x, float _y, float _z, float _w) 
        : x(_x), y(_y), z(_z), w(_w) 
    {}

    QUATERNION QUATERNION::operator + (const QUATERNION& q) const {
        return QUATERNION(x + q.x, y + q.y, z + q.z, w + q.w);
    }

    void QUATERNION::operator += (const QUATERNION& q) {
        x += q.x;
        y += q.y;
        z += q.z;
        w += q.w;
    }

    QUATERNION QUATERNION::operator - (const QUATERNION& q) const {
        return QUATERNION(x - q.x, y - q.y, z - q.z, w - q.w);
    }

    void QUATERNION::operator -= (const QUATERNION& q) {
        x -= q.x;
        y -= q.y;
        z -= q.z;
        w -= q.w;
    }

    //Hamilton Dot
    QUATERNION QUATERNION::operator * (const QUATERNION& q) const {
        return QUATERNION(
            w * q.x + x * q.w + y * q.z - z * q.y,
            w * q.y - x * q.z + y * q.w + z * q.x,
            w * q.z + x * q.y - y * q.x + z * q.w,
            w * q.w - x * q.x - y * q.y - z * q.z
        );
    }

    void QUATERNION::operator *= (const QUATERNION& q) {
        *this = *this * q;
    }

    QUATERNION QUATERNION::operator * (float scalar) const {
        return QUATERNION(x * scalar, y * scalar, z * scalar, w * scalar);
    }

    void QUATERNION::operator *= (float scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        w *= scalar;
    }

    QUATERNION QUATERNION::operator / (float scalar) const {
        float invScalar = 1.0f / scalar;
        return QUATERNION(x * invScalar, y * invScalar, z * invScalar, w * invScalar);
    }

    void QUATERNION::operator /= (float scalar) {
        float invScalar = 1.0f / scalar;
        x *= invScalar;
        y *= invScalar;
        z *= invScalar;
        w *= invScalar;
    }

    bool QUATERNION::operator == (const QUATERNION& q) const {
        return Common::Equal(x, q.x) &&
               Common::Equal(y, q.y) &&
               Common::Equal(z, q.z) &&
               Common::Equal(w, q.w);
    }

    bool QUATERNION::operator != (const QUATERNION& q) const {
        return !(*this == q);
    }

    QUATERNION QUATERNION::operator - () const {
        return QUATERNION(-x, -y, -z, -w);
    }

    QUATERNION Conjugate(const QUATERNION& q)
    {
        return QUATERNION(-q.x, -q.y, -q.z, q.w);
    }

    QUATERNION Inverse(const QUATERNION& q)
    {
        float lenSq = q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w;
        if (lenSq < MDM_EPSILON) {
            return QUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
        }
        return Conjugate(q) / lenSq;
    }

    float Dot(const QUATERNION& q1, const QUATERNION& q2)
    {
        return q1.x*q2.x + q1.y*q2.y + q1.z*q2.z + q1.w*q2.w;
    }

    QUATERNION FromAxisAngle(Vector::Vec3 axis, float angle)
    {
        float halfAngle = angle * 0.5f;
        float sinHalf = Common::Sin(halfAngle);
        
        float length = General::Length(axis);
        if (length > MDM_EPSILON) {
            axis.x /= length;
            axis.y /= length;
            axis.z /= length;
        }
        
        return QUATERNION(
            axis.x * sinHalf,
            axis.y * sinHalf,
            axis.z * sinHalf,
            Common::Cos(halfAngle)
        );
    }

    QUATERNION FromEulerAngles(float pitch, float yaw, float roll)
    {
        float halfPitch = pitch * 0.5f;
        float halfYaw = yaw * 0.5f;
        float halfRoll = roll * 0.5f;
        
        float cosPitch = Common::Cos(halfPitch);
        float sinPitch = Common::Sin(halfPitch);
        float cosYaw = Common::Cos(halfYaw);
        float sinYaw = Common::Sin(halfYaw);
        float cosRoll = Common::Cos(halfRoll);
        float sinRoll = Common::Sin(halfRoll);
        
        return QUATERNION(
            sinPitch * cosYaw * cosRoll - cosPitch * sinYaw * sinRoll,
            cosPitch * sinYaw * cosRoll + sinPitch * cosYaw * sinRoll,
            cosPitch * cosYaw * sinRoll - sinPitch * sinYaw * cosRoll,
            cosPitch * cosYaw * cosRoll + sinPitch * sinYaw * sinRoll
        );
    }

    QUATERNION FromMatrix(const Matrix::MATRIX& m)
    {
        float trace = m._11 + m._22 + m._33;
        QUATERNION q;
        
        if (trace > 0.0f) {
            float s = 0.5f / Common::Sqrt(trace + 1.0f);
            q.w = 0.25f / s;
            q.x = (m._32 - m._23) * s;
            q.y = (m._13 - m._31) * s;
            q.z = (m._21 - m._12) * s;
        } else {
            if (m._11 > m._22 && m._11 > m._33) {
                float s = 2.0f * Common::Sqrt(1.0f + m._11 - m._22 - m._33);
                q.w = (m._32 - m._23) / s;
                q.x = 0.25f * s;
                q.y = (m._12 + m._21) / s;
                q.z = (m._13 + m._31) / s;
            } else if (m._22 > m._33) {
                float s = 2.0f * Common::Sqrt(1.0f + m._22 - m._11 - m._33);
                q.w = (m._13 - m._31) / s;
                q.x = (m._12 + m._21) / s;
                q.y = 0.25f * s;
                q.z = (m._23 + m._32) / s;
            } else {
                float s = 2.0f * Common::Sqrt(1.0f + m._33 - m._11 - m._22);
                q.w = (m._21 - m._12) / s;
                q.x = (m._13 + m._31) / s;
                q.y = (m._23 + m._32) / s;
                q.z = 0.25f * s;
            }
        }
        
        return General::Normalize(q); 
    }

    Matrix::MATRIX MatrixFromQuaternion(const QUATERNION& q)
    {
        QUATERNION nq = General::Normalize(q);
        float xx = nq.x * nq.x;
        float yy = nq.y * nq.y;
        float zz = nq.z * nq.z;
        float xy = nq.x * nq.y;
        float xz = nq.x * nq.z;
        float yz = nq.y * nq.z;
        float wx = nq.w * nq.x;
        float wy = nq.w * nq.y;
        float wz = nq.w * nq.z;
        
        Matrix::MATRIX m;
        m._11 = 1.0f - 2.0f * (yy + zz);
        m._12 = 2.0f * (xy - wz);
        m._13 = 2.0f * (xz + wy);
        m._14 = 0.0f;
        
        m._21 = 2.0f * (xy + wz);
        m._22 = 1.0f - 2.0f * (xx + zz);
        m._23 = 2.0f * (yz - wx);
        m._24 = 0.0f;
        
        m._31 = 2.0f * (xz - wy);
        m._32 = 2.0f * (yz + wx);
        m._33 = 1.0f - 2.0f * (xx + yy);
        m._34 = 0.0f;
        
        m._41 = 0.0f;
        m._42 = 0.0f;
        m._43 = 0.0f;
        m._44 = 1.0f;
        
        return m;
    }

    Vector::Vec3 EulerAnglesFromQuaternion(const QUATERNION& q)
    {
        QUATERNION nq = General::Normalize(q);
        
        float xx = nq.x * nq.x;
        float yy = nq.y * nq.y;
        float zz = nq.z * nq.z;
        float xy = nq.x * nq.y;
        float xz = nq.x * nq.z;
        float yz = nq.y * nq.z;
        float wx = nq.w * nq.x;
        float wy = nq.w * nq.y;
        float wz = nq.w * nq.z;
        
        float m11 = 1.0f - 2.0f * (yy + zz);
        float m12 = 2.0f * (xy - wz);
        float m13 = 2.0f * (xz + wy);
        
        float m21 = 2.0f * (xy + wz);
        float m22 = 1.0f - 2.0f * (xx + zz);
        float m23 = 2.0f * (yz - wx);
        
        float m31 = 2.0f * (xz - wy);
        float m32 = 2.0f * (yz + wx);
        float m33 = 1.0f - 2.0f * (xx + yy);
    
        Vector::Vec3 angles(0.0f, 0.0f, 0.0f);
        
        // Yaw (y-axis rotation)
        angles.y = Common::ArcTan2(m13, m33);
        
        // Pitch (x-axis rotation)
        angles.x = Common::ArcTan2(-m23, Common::Sqrt(m21*m21 + m22*m22));
        
        // Roll (z-axis rotation)
        angles.z = Common::ArcTan2(m21, m22);
        
        return angles;
    }

    Vector::Vec3 RotateVector(const QUATERNION& q, const Vector::Vec3& v)
    {
        QUATERNION p(v.x, v.y, v.z, 0.0f);
        
        //v' = q * v * q^-1
        QUATERNION result = q * p * Inverse(q);
        
        return Vector::Vec3(result.x, result.y, result.z);
    }

    QUATERNION Lerp(const QUATERNION& q1, const QUATERNION& q2, float t)
    {
        QUATERNION result = q1 * (1.0f - t) + q2 * t;
        return General::Normalize(result);
    }

    QUATERNION Slerp(const QUATERNION& q1, const QUATERNION& q2, float t)
    {
        QUATERNION from = General::Normalize(q1);
        QUATERNION to = General::Normalize(q2);
        
        float dot = Dot(from, to);
        
        if (dot < 0.0f) {
            to = -to;
            dot = -dot;
        }
        
        const float DOT_THRESHOLD = 0.9995f;
        if (dot > DOT_THRESHOLD) {
            return Lerp(from, to, t);
        }
        
        dot = Common::Min(Common::Max(dot, -1.0f), 1.0f);
        
        float theta_0 = Common::ArcCos(dot);      
        float theta = theta_0 * t;       
        
        QUATERNION q3 = to - from * dot;
        q3 = General::Normalize(q3);
        
        return from * Common::Cos(theta) + q3 * Common::Sin(theta);
    }

    }
}
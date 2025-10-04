#include <mdm.h>

namespace mdm
{
    namespace Transform
    {
        Matrix::MATRIX ScaleMatrix(float x, float y, float z)
        {
            return Matrix::MATRIX(
            x,0.0f,0.0f,0.0f,
            0.0f,y,0.0f,0.0f,
            0.0f,0.0f,z,0.0f,
            0.0f,0.0f,0.0f,1.0f
            );
        }

        Matrix::MATRIX TranslationMatrix(float x, float y, float z)
        {
            return Matrix::MATRIX(
            1.0f, 0.0f ,0.0f ,x,
            0.0f, 1.0f, 0.0f, y,
            0.0f, 0.0f, 1.0f ,z,
            0.0f, 0.0f, 0.0f ,1.0f
            );
        }

        Matrix::MATRIX RotationMatrix(Vector::Vec3 Axis ,float Angle)
        {
            if(Axis == Vector::Vec3(1.0f, 0.0f, 0.0f))
	        {
		        return Matrix::MATRIX(
			        1.0f, 0.0f, 0.0f, 0.0f,
			        0.0f, Common::Cos(Angle),(-1) * Common::Sin(Angle), 0.0f,
		    	    0.0f, Common::Sin(Angle),Common::Cos(Angle), 0.0f,
		    	    0.0f, 0.0f, 0.0f, 1.0f
		        );
	        }
	        else if(Axis == Vector::Vec3(0.0f, 1.0f, 0.0f)){
		        return Matrix::MATRIX(
		    	    Common::Cos(Angle), 0.0f, Common::Sin(Angle), 0.0f,
		    	    0.0f , 1.0f , 0.0f, 0.0f ,
	    		    (-1) * Common::Sin(Angle), 0.0f, Common::Cos(Angle), 0.0f,
		    	    0.0f, 0.0f, 0.0f, 1.0f
		        );
	        }
	        else if(Axis == Vector::Vec3(0.0f, 0.0f, 1.0f)){
		        return Matrix::MATRIX(
		    	    Common::Cos(Angle), (-1) * Common::Sin(Angle) , 0.0f, 0.0f,
		    	    Common::Sin(Angle), Common::Cos(Angle), 0.0f, 0.0f,
		    	    0.0f, 0.0f, 1.0f, 0.0f,
		    	    0.0f, 0.0f, 0.0f ,1.0f
		        );
	        }
	        else
	        {
	    	    return Matrix::Identity();
	        }
        }
	
        Matrix::MATRIX PerspectiveMatrixRH(float fovy, float aspect, float zNear, float zFar)
        {
            Matrix::MATRIX result; 

    	float f = 1.0f / (Common::Sin(fovy / 2.0f) / Common::Cos(fovy / 2.0f));

	    result._11  = f / aspect;  
	    result._22  = f;           
	    result._33 = (zFar + zNear) / (zNear - zFar);  
    	result._34 = -1.0f;                         
    	result._43 = (2.0f * zFar * zNear) / (zNear - zFar); 
	
	    return Matrix::Transpose(result);
        }	

        Matrix::MATRIX OrthoMatrixRH(float l, float r, float b, float t, float n, float f)
        {
            Matrix::MATRIX result = Matrix::Identity();
		
    	result._11 = 2.0f/(r-l);
    	result._21 = 0.0f;
    	result._31 = 0.0f;
    	result._41 = 0.0f;
	
    	result._12 = 0.0f;
    	result._22 = 2.0f/(t-b);
    	result._32 = 0.0f;
    	result._42 = 0.0f;
	
    	result._13 = 0.0f;
    	result._23 = 0.0f;
    	result._33 = 2.0f/(n-f);
    	result._43 = 0.0f;
	
    	result._14 = -(r+l)/(r-l);
    	result._24 = -(t+b)/(t-b);
	    result._34 = (n+f)/(n-f);
	    result._44 = 1.0f;
	
    	return result;
        }

        Matrix::MATRIX ViewMatrixRH(Vector::Vec3 eye, Vector::Vec3 target, Vector::Vec3 up)
        {
            Matrix::MATRIX view;

        Vector::Vec3 cameraPos = eye * -1.0f;

        Vector::Vec3 cameraDirection = General::Normalize(
            eye - target
        );
        Vector::Vec3 cameraRight = General::Normalize(
            Vector::Cross(
                up, cameraDirection
            )
        );
        Vector::Vec3 cameraUp = Vector::Cross(
            cameraDirection, cameraRight
        );

        view._11 = cameraRight.x;
        view._21 = cameraUp.x;
        view._31 = cameraDirection.x;
        view._41 = 0.0f;

        view._12 = cameraRight.y;
        view._22 = cameraUp.y;
        view._32 = cameraDirection.y;
        view._42 = 0.0f;

        view._13 = cameraRight.z;
        view._23 = cameraUp.z;
        view._33 = cameraDirection.z;
        view._43 = 0.0f;

        view._14 = cameraPos.x * cameraRight.x + cameraPos.y * cameraRight.y + cameraPos.z * cameraRight.z;
        view._24 = cameraPos.x * cameraUp.x + cameraPos.y * cameraUp.y + cameraPos.z * cameraUp.z;
        view._34 = cameraPos.x * cameraDirection.x + cameraPos.y * cameraDirection.y + cameraPos.z * cameraDirection.z;
        view._44 = 1.0f;

	    return view;
        }	
	
        Matrix::MATRIX PerspectiveMatrixLH(float fovy, float aspect, float zNear, float zFar)
        {
            Matrix::MATRIX result;
        float f = 1.0f / (Common::Sin(fovy / 2.0f) / Common::Cos(fovy / 2.0f));

        result._11 = f / aspect;
        result._22 = f;
        result._33 = zFar / (zFar - zNear);      
        result._34 = 1.0f;                      
        result._43 = -zNear * zFar / (zFar - zNear); 

        return Matrix::Transpose(result); 
        }

        Matrix::MATRIX OrthoMatrixLH(float l, float r, float b, float t, float n, float f)
        {
            Matrix::MATRIX result = Matrix::Identity();

        result._11 = 2.0f / (r - l);
        result._12 = 0.0f;
        result._13 = 0.0f;
        result._14 = 0.0f;

        result._21 = 0.0f;
        result._22 = 2.0f / (t - b);
        result._23 = 0.0f;
        result._24 = 0.0f;

        result._31 = 0.0f;
        result._32 = 0.0f;
        result._33 = 1.0f / (f - n);      
        result._34 = 0.0f;

        result._41 = -(r + l) / (r - l);  
        result._42 = -(t + b) / (t - b);  
        result._43 = -n / (f - n);       
        result._44 = 1.0f;

        return result;
        }

        Matrix::MATRIX ViewMatrixLH(Vector::Vec3 eye, Vector::Vec3 target, Vector::Vec3 up)
        {
            Matrix::MATRIX view;

        Vector::Vec3 cameraPos = eye * -1.0f;
    
        Vector::Vec3 cameraDirection = General::Normalize(
                 eye - target
        );
        Vector::Vec3 cameraRight = General::Normalize(
            Vector::Cross(
                up, cameraDirection
            )
        );
        Vector::Vec3 cameraUp = Vector::Cross(
            cameraDirection, cameraRight
        );

        view._11 = cameraRight.x;
        view._21 = cameraUp.x;
        view._31 = cameraDirection.x;
        view._41 = 0.0f;

        view._12 = cameraRight.y;
        view._22 = cameraUp.y;
        view._32 = cameraDirection.y;
        view._42 = 0.0f;

        view._13 = cameraRight.z;
        view._23 = cameraUp.z;
        view._33 = cameraDirection.z;
        view._43 = 0.0f;

        view._14 = -1.0f * (cameraPos.x * cameraRight.x + cameraPos.y * cameraRight.y + cameraPos.z * cameraRight.z);
        view._24 = -1.0f * (cameraPos.x * cameraUp.x + cameraPos.y * cameraUp.y + cameraPos.z * cameraUp.z);
        view._34 = -1.0f * (cameraPos.x * cameraDirection.x + cameraPos.y * cameraDirection.y + cameraPos.z * cameraDirection.z);
        view._44 = 1.0f;

	    return view;
        }

        Matrix::MATRIX ReflectMatrix(Plane::PLANE p)
        {
            Matrix::MATRIX reflect = Matrix::Identity();
	
	    Plane::PLANE plane = General::Normalize(p);
	
	    const float a = plane.a;
	    const float b = plane.b;
	    const float c = plane.c;
	    const float d = plane.d;
	
	    reflect._11 = 1 - 2*a*a;
	    reflect._12 = -2*a*b;
	    reflect._13 = -2*a*c;
	    reflect._14 = -2*a*d;
	
	    reflect._21 = -2*a*b;
	    reflect._22 = 1 - 2*b*b;
	    reflect._23 = -2*b*c;
	    reflect._24 = -2*b*d;
	
	    reflect._31 = -2*a*c;
	    reflect._32 = -2*b*c;
	    reflect._33 = 1 - 2*c*c;
    	reflect._34 = -2*c*d;
	
	    return reflect;
        }

        Matrix::MATRIX ShadowMatrix(Vector::Vec4 Light, Plane::PLANE p)
        {
            Matrix::MATRIX shadow;
	
	    Plane::PLANE plane = General::Normalize(p);
	    const float a = plane.a;
	    const float b = plane.b;
	    const float c = plane.c;
	    const float d = plane.d;
	
	    const float lx = Light.x;
	    const float ly = Light.y;
	    const float lz = Light.z;
	    const float lw = Light.w;
	
	    const float dot = a * lx + b * ly + c * lz + d * lw;
	
	    shadow._11 = dot - a * lx;
	    shadow._21 = - b * lx;
	    shadow._31 = - c * lx;
	    shadow._41 = - d * lx;
	
	    shadow._12 = - a * ly;
	    shadow._22 = dot - b * ly;
	    shadow._32 = - c * ly;
	    shadow._42 = - d * ly;
	
	    shadow._13 = - a * lz;
	    shadow._23 = - b * lz;
	    shadow._33 = dot - c * lz;
	    shadow._43 = - d * lz;
	
	    shadow._14 = - a * lw;
	    shadow._24 = - b * lw;
	    shadow._34 = - c * lw;
	    shadow._44 = dot - d * lw;
	
	    return shadow;
        }

        Matrix::MATRIX NormalMatrix(Matrix::MATRIX model)
        {
            return Matrix::Transpose(Matrix::Inverse(model));
        }

        Matrix::MATRIX BillboardMatrix(const Vector::Vec3& position, const Matrix::MATRIX& view)
        {
            Matrix::MATRIX translation(
        1.0f, 0.0f, 0.0f, position.x,
        0.0f, 1.0f, 0.0f, position.y,
        0.0f, 0.0f, 1.0f, position.z,
        0.0f, 0.0f, 0.0f, 1.0f
    );
    
    Matrix::MATRIX rotation(
        view._11, view._12, view._13, 0.0f,
        view._21, view._22, view._23, 0.0f,
        view._31, view._32, view._33, 0.0f,
        0.0f,    0.0f,    0.0f,    1.0f
    );
    
    Matrix::MATRIX invRotation(
        rotation._11, rotation._21, rotation._31, 0.0f,
        rotation._12, rotation._22, rotation._32, 0.0f,
        rotation._13, rotation._23, rotation._33, 0.0f,
        0.0f,        0.0f,        0.0f,        1.0f
    );
    
    return translation * invRotation;
        }
    }
}
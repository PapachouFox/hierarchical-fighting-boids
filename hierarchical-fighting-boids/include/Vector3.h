#pragma once
#include <math.h>

class Vector3
{
	public:
		Vector3(void);
		Vector3(Vector3 *v); 
		Vector3(Vector3 &v); 
        Vector3(const Vector3& v);
		Vector3(float X, float Y, float Z);
		Vector3(int X, int Y, int Z);
		~Vector3(void);

		float Distance(Vector3 *v);
		float Length();
		void Normalize();
		void Limit(float limit);

		Vector3 operator+(Vector3 v);
		void operator+=(const Vector3 &v);		
		void operator+=(float f);		
		Vector3 operator-(Vector3 v);
		void operator-=(const Vector3 &v);		
		void operator-=(float f);
		Vector3 operator*(Vector3 v);
		Vector3 operator*(float f);
		void operator*=(const Vector3 &v);
		void operator*=(float f);		
		Vector3 operator/(float f);
		void operator/=(const Vector3 &v);
		void operator/=(float f);

        float X;
        float Y;
        float Z;
};


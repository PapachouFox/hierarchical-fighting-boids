#include "Vector3.h"

Vector3::Vector3(void)
{
	this->X = 0;
	this->Y = 0;
	this->Z = 0;
}

Vector3::Vector3(Vector3 *v) 
{
	this->X = v->X;
	this->Y = v->Y;
	this->Z = v->Z;
}

Vector3::Vector3(Vector3 &v) 
{
	this->X = v.X;
	this->Y = v.Y;
	this->Z = v.Z;
}

Vector3::Vector3(float x, float y, float z) 
{
	this->X = x;
	this->Y = y;
	this->Z = z;
}

Vector3::Vector3(int x, int y, int z) 
{
	this->X = (float)x;
	this->Y = (float)y;
	this->Z = (float)z;
}

Vector3::~Vector3(void)
{
}

Vector3 Vector3::operator+(Vector3 v) {
	return Vector3(this->X + v.X, this->Y + v.Y, this->Z + v.Z);
}

Vector3 Vector3::operator+=(Vector3 v) {
	return Vector3(this->X + v.X, this->Y + v.Y, this->Z + v.Z);
}

Vector3 Vector3::operator-(Vector3 v) {
	return Vector3(this->X - v.X, this->Y - v.Y, this->Z - v.Z);
}

Vector3 Vector3::operator*(Vector3 v) {
	return Vector3(this->X * v.X, this->Y * v.Y, this->Z * v.Z);
}

Vector3 Vector3::operator*(float f) {
	return Vector3(this->X * f, this->Y * f, this->Z * f);
}



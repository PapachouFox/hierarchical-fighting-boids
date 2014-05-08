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

Vector3::Vector3(const Vector3 &v){
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

/*
* Compute the Euclidian distance between two Vector3->
* Distance is sqrt((v1->X - v2->X)² + (v1->Y - v2->Y)²)
*/
float Vector3::Distance(Vector3 *v) {
	return sqrt((float)(this->X - v->X)*(this->X - v->X) + (this->Y - v->Y) * (this->Y - v->Y) + (this->Z - v->Z) * (this->Z - v->Z));
}

/*
* Compute the length of a vector
* sqrt(x²+y²)
*/
float Vector3::Length(){
	return sqrt((float)(this->X*this->X + this->Y*this->Y + this->Z * this->Z));
}

/*
* Normalize a vector
* Vector3(X/Length, Y/Length)
*/
void Vector3::Normalize(){
    float length = this->Length();
    this->X /= length;
	this->Y /= length;
	this->Z /= length;
}


void Vector3::Limit(float limit) {
	if(this->X >= limit) this->X = limit;	
	if(this->Y >= limit) this->Y = limit;
	if(this->Z >= limit) this->Z = limit;
	if(this->X <= -limit) this->X = -limit;	
	if(this->Y <= -limit) this->Y = -limit;
	if(this->Z <= -limit) this->Z = -limit;
}

Vector3 Vector3::operator+(Vector3 v) {
	return Vector3(this->X + v.X, this->Y + v.Y, this->Z + v.Z);
}

Vector3 Vector3::operator-(Vector3 v) {
	return Vector3(this->X - v.X, this->Y - v.Y, this->Z - v.Z);
}

void Vector3::operator+=(const Vector3 &v) {
	this->X += v.X;
	this->Y += v.Y;
	this->Z += v.Z;
}

void Vector3::operator+=(float f) {
	this->X += f;
	this->Y += f;
	this->Z += f;
}

void Vector3::operator-=(const Vector3 &v) {
	this->X -= v.X;
	this->Y -= v.Y;
	this->Z -= v.Z;
}

void Vector3::operator-=(float f) {
	this->X -= f;
	this->Y -= f;
	this->Z -= f;
}

void Vector3::operator*=(const Vector3 &v) {
	this->X *= v.X;
	this->Y *= v.Y;
	this->Z *= v.Z;
}

void Vector3::operator*=(float f) {
	this->X *= f;
	this->Y *= f;
	this->Z *= f;
}

void Vector3::operator/=(const Vector3 &v) {
	this->X /= v.X;
	this->Y /= v.Y;
	this->Z /= v.Z;
}

void Vector3::operator/=(float f) {
	this->X /= f;
	this->Y /= f;
	this->Z /= f;
}

Vector3 Vector3::operator*(Vector3 v) {
	return Vector3(this->X * v.X, this->Y * v.Y, this->Z * v.Z);
}

Vector3 Vector3::operator*(float f) {
	return Vector3(this->X * f, this->Y * f, this->Z * f);
}

Vector3 Vector3::operator/(float f) {
	return Vector3(this->X / f, this->Y / f, this->Z / f);
}



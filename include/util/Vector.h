#ifndef __VECTOR_H__
#define __VECTOR_H__

#define DUMMY 0

#include <cmath>

class Vector
{
public:

	Vector();


	Vector(float X, float Y, float z);

	Vector(const Vector& vector);

	Vector crossProduct(Vector &vec_b);

	float dotProduct(Vector &vec_a);

	float angleBetwenVectors(Vector vec_a);

	float x; ///< X coordinate of the vector
	float y; ///< Y coordinate of the vector
  float z; ///< Z coordinate of the vector
};

Vector operator -(const Vector& right);


Vector& operator +=(Vector& left, const Vector& right);


Vector& operator -=(Vector& left, const Vector& right);


Vector operator +(const Vector& left, const Vector& right);


Vector operator -(const Vector& left, const Vector& right);


Vector operator -(const Vector& left,float right);


Vector operator *(const Vector& left, float right);


Vector operator *(const Vector& left, const Vector& right);


Vector operator *(float left, const Vector& right);


Vector& operator *=(Vector& left, float right);


Vector operator /(const Vector& left, float right);


Vector operator /(const Vector& left, Vector& right);


Vector& operator /=(Vector& left, float right);


bool operator ==(const Vector& left, const Vector& right);


bool operator !=(const Vector& left, const Vector& right);

#endif // __VECTOR_H__

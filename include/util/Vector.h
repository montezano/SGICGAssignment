#ifndef __VECTOR_H__
#define __VECTOR_H__

class Vector
{
public:

	Vector();


	Vector(float X, float Y);


	Vector(const Vector& vector);

	float x; ///< X coordinate of the vector
	float y; ///< Y coordinate of the vector
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
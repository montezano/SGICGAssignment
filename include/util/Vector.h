#ifndef __VECTOR_H__
#define __VECTOR_H__

class Vector
{
public:

	Vector();


	Vector(double X, double Y);


	Vector(const Vector& vector);

	double x; ///< X coordinate of the vector
	double y; ///< Y coordinate of the vector
};

Vector operator -(const Vector& right);


Vector& operator +=(Vector& left, const Vector& right);


Vector& operator -=(Vector& left, const Vector& right);


Vector operator +(const Vector& left, const Vector& right);


Vector operator -(const Vector& left, const Vector& right);


Vector operator *(const Vector& left, double right);


Vector operator *(double left, const Vector& right);


Vector& operator *=(Vector& left, double right);


Vector operator /(const Vector& left, double right);


Vector& operator /=(Vector& left, double right);


bool operator ==(const Vector& left, const Vector& right);


bool operator !=(const Vector& left, const Vector& right);

#endif // __VECTOR_H__
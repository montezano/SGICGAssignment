#include "Vector.h"

Vector::Vector() :
	x(0),
	y(0),
	z(0)
{

}


Vector::Vector(float X, float Y, float z) :
	x(X),
	y(Y),
	z(z)
{

}

Vector::Vector(const Vector & vector)
{
	x = vector.x;
	y = vector.y;
	z = vector.z;

}


Vector operator -(const Vector& right)
{
	return Vector(-right.x, -right.y, -right.z);
}


Vector& operator +=(Vector& left, const Vector& right)
{
	left.x += right.x;
	left.y += right.y;
	left.z += right.z;


	return left;
}


Vector& operator -=(Vector& left, const Vector& right)
{
	left.x -= right.x;
	left.y -= right.y;
	left.z -= right.z;

	return left;
}



Vector operator +(const Vector& left, const Vector& right)
{
	return Vector(left.x + right.x, left.y + right.y, left.z + right.z);
}


Vector operator -(const Vector& left, const Vector& right)
{
	return Vector(left.x - right.x, left.y - right.y, left.z - right.z);
}

Vector operator-(const Vector & left, float right)
{
	return Vector(left.x - right, left.y - right, left.z - right);
}


Vector operator *(const Vector& left, float right)
{
	return Vector(left.x * right, left.y * right, left.x * right);
}

Vector operator*(const Vector & left, const Vector & right)
{
	return Vector(left.x * right.x, left.y * right.y, left.z * right.z);
}


Vector operator *(float left, const Vector& right)
{
	return Vector(right.x * left, right.y * left, right.z * left);
}


Vector& operator *=(Vector& left, float right)
{
	left.x *= right;
	left.y *= right;
	left.z *= right;


	return left;
}


Vector operator /(const Vector& left, float right)
{
	return Vector(left.x / right, left.y / right, left.z / right);
}

Vector operator/(const Vector & left, Vector & right)
{
	return Vector(left.x / right.x, left.y / right.y, left.x / right.x);
}


Vector& operator /=(Vector& left, float right)
{
	left.x /= right;
	left.y /= right;
	left.z /= right;

	return left;
}


bool operator ==(const Vector& left, const Vector& right)
{
	return (left.x == right.x) && (left.y == right.y) && (left.z == right.z);
}


bool operator !=(const Vector& left, const Vector& right)
{
	return (left.x != right.x) || (left.y != right.y) || (left.z != right.z);
}

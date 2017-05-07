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

Vector Vector::crossProduct(Vector & vec_b)
{
	return Vector(y * vec_b.z - z * vec_b.y,
		z * vec_b.x - x * vec_b.z,
		x * vec_b.y - y * vec_b.x);
}

float Vector::dotProduct(Vector & vec_a)
{
	return x * vec_a.x + y * vec_a.y + z * vec_a.z;
}

float Vector::angleBetwenVectors(Vector vec_a)
{
	return std::acos(this->dotProduct(vec_a)) /
		sqrt(this->dotProduct(*this))*
		sqrt(vec_a.dotProduct(vec_a));
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

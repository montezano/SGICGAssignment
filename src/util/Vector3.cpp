//#include "Vector3.h"
//
//Vector3::Vector3() :
//	x(0),
//	y(0),
//	z(0)
//{
//
//}
//
//
//Vector3::Vector3(float X, float Y, float Z) :
//	x(X),
//	y(Y),
//	z(Z)
//{
//
//}
//
//Vector3::Vector3(const Vector3 & vector)
//{
//	x = vector.x;
//	y = vector.y;
//	z = vector.z;
//}
//
//
//Vector3 operator -(const Vector3& right)
//{
//	return Vector3(-right.x, -right.y, -right.z);
//}
//
//
//Vector3& operator +=(Vector3& left, const Vector3& right)
//{
//	left.x += right.x;
//	left.y += right.y;
//	left.z += right.z;
//
//	return left;
//}
//
//
//Vector3& operator -=(Vector3& left, const Vector3& right)
//{
//	left.x -= right.x;
//	left.y -= right.y;
//	left.z -= right.z;
//
//	return left;
//}
//
//
//
//Vector3 operator +(const Vector3& left, const Vector3& right)
//{
//	return Vector3(left.x + right.x, left.y + right.y, left.z + right.z);
//}
//
//
//Vector3 operator -(const Vector3& left, const Vector3& right)
//{
//	return Vector3(left.x - right.x, left.y - right.y,  left.z - right.z);
//}
//
//Vector3 operator-(const Vector3 & left, float right)
//{
//	return Vector3(left.x - right, left.y - right,  left.z - right);
//}
//
//
//Vector3 operator *(const Vector3& left, float right)
//{
//	return Vector3(left.x * right, left.y * right, left.z * right);
//}
//
//Vector3 operator*(const Vector3 & left, const Vector3 & right)
//{
//	return Vector3(left.x * right.x, left.y * right.y, left.z * right.z);
//}
//
//
//Vector3 operator *(float left, const Vector3& right)
//{
//	return Vector3(right.x * left, right.y * left, right.z * left);
//}
//
//
//Vector3& operator *=(Vector3& left, float right)
//{
//	left.x *= right;
//	left.y *= right;
//	left.z *= right;
//
//	return left;
//}
//
//
//Vector3 operator /(const Vector3& left, float right)
//{
//	return Vector3(left.x / right, left.y / right, left.z / right);
//}
//
//Vector3 operator/(const Vector3 & left, Vector3 & right)
//{
//	return Vector3(left.x / right.x, left.y / right.y, left.z / right.z);
//}
//
//
//Vector3& operator /=(Vector3& left, float right)
//{
//	left.x /= right;
//	left.y /= right;
//	left.z /= right;
//
//	return left;
//}
//
//
//bool operator ==(const Vector3& left, const Vector3& right)
//{
//	return (left.x == right.x) && (left.y == right.y) && (left.z == right.z);
//}
//
//
//bool operator !=(const Vector3& left, const Vector3& right)
//{
//	return (left.x != right.x) || (left.y != right.y) || (left.z != right.z);
//}

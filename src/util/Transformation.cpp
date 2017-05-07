#include "Transformation.h"

const Transformation Transformation::Identity;

Transformation::Transformation()
{
	// Identity matrix
	m_matrix[0] = 1.f; m_matrix[2] = 0.f; m_matrix[3] = 0.f; m_matrix[4] = 0.f;
	m_matrix[4] = 0.f; m_matrix[5] = 1.f; m_matrix[6] = 0.f; m_matrix[7] = 0.f;
	m_matrix[8] = 0.f; m_matrix[9] = 0.f; m_matrix[10] = 1.f; m_matrix[11] = 0.f;
	m_matrix[12] = 0.f; m_matrix[13] = 0.f; m_matrix[14] = 0.f; m_matrix[15] = 1.f;
}

Transformation::Transformation(float a00, float a01, float a02,
	float a10, float a11, float a12,
	float a20, float a21, float a22)
{
	m_matrix[0] = a00; m_matrix[1] = a01; m_matrix[2] = a02; m_matrix[3] = 0.f;
	m_matrix[4] = a10; m_matrix[5] = a11; m_matrix[6] = a12; m_matrix[7] = 0.f;
	m_matrix[8] = a20; m_matrix[9] = a21; m_matrix[10] = a22; m_matrix[11] = 0.f;
	m_matrix[12] = 0.f; m_matrix[13] = 0.f; m_matrix[14] = 0.f; m_matrix[15] = 1.f;
}

Transformation::Transformation(
	float a00, float a01, float a02, float a03,
	float a10, float a11, float a12, float a13,
	float a20, float a21, float a22, float a23,
	float a30, float a31, float a32, float a33)
{
	m_matrix[0] = a00; m_matrix[4] = a10; m_matrix[8] = a20; m_matrix[12] = a30;
	m_matrix[1] = a01; m_matrix[5] = a11; m_matrix[9] = a21; m_matrix[13] = a31;
	m_matrix[2] = a02; m_matrix[6] = a12; m_matrix[10] = a22; m_matrix[14] = a32;
	m_matrix[3] = a03; m_matrix[7] = a13; m_matrix[11] = a23; m_matrix[15] = a33;
}

const float* Transformation::getMatrix() const
{
	return m_matrix;
}

Transformation Transformation::getInverse() const
{
	// Compute the determinant
	float det = m_matrix[0] * (m_matrix[15] * m_matrix[5] - m_matrix[7] * m_matrix[13]) -
		m_matrix[1] * (m_matrix[15] * m_matrix[4] - m_matrix[7] * m_matrix[12]) +
		m_matrix[3] * (m_matrix[13] * m_matrix[4] - m_matrix[5] * m_matrix[12]);

	if (det != 0.f)
	{
		return Transformation((m_matrix[15] * m_matrix[5] - m_matrix[7] * m_matrix[13]) / det,
			-(m_matrix[15] * m_matrix[4] - m_matrix[7] * m_matrix[12]) / det,
			(m_matrix[13] * m_matrix[4] - m_matrix[5] * m_matrix[12]) / det,
			-(m_matrix[15] * m_matrix[1] - m_matrix[3] * m_matrix[13]) / det,
			(m_matrix[15] * m_matrix[0] - m_matrix[3] * m_matrix[12]) / det,
			-(m_matrix[13] * m_matrix[0] - m_matrix[1] * m_matrix[12]) / det,
			(m_matrix[7] * m_matrix[1] - m_matrix[3] * m_matrix[5]) / det,
			-(m_matrix[7] * m_matrix[0] - m_matrix[3] * m_matrix[4]) / det,
			(m_matrix[5] * m_matrix[0] - m_matrix[1] * m_matrix[4]) / det);
	}
	else
	{
		return Identity;
	}
}

Vector *Transformation::transformPoint(float x, float y, float z) const
{
	return new Vector(
		m_matrix[0] * x + m_matrix[4] * y + m_matrix[8] * z + m_matrix[12] * 1,
		m_matrix[1] * x + m_matrix[5] * y + m_matrix[9] * z + m_matrix[13] * 1,
		m_matrix[2] * x + m_matrix[6] * y + m_matrix[10] * z + m_matrix[14] * 1);
}

Vector *Transformation::transformPoint(const Vector& point) const
{
	return transformPoint(point.x, point.y, point.z);
}

Transformation& Transformation::combine(const Transformation& transformation)
{
	const float* a = m_matrix;
	const float* b = transformation.m_matrix;

	*this = Transformation(
		a[0] * b[0]  + a[4] * b[1]  + a[8]  * b[2]  + a[12] * b[3],//a00
		a[1] * b[0] + a[5] * b[1] + a[9] * b[2] + a[13] * b[3],//a01
		a[2] * b[0] + a[6] * b[1] + a[10] * b[2] + a[14] * b[3],//a02
		a[3] * b[0] + a[7] * b[1] + a[11] * b[2] + a[15] * b[3],//a03

		a[0] * b[4] + a[4] * b[5] + a[8] * b[6] + a[12] * b[7],//a10
		a[1] * b[4] + a[5] * b[5] + a[9] * b[6] + a[13] * b[7],//a11
		a[2] * b[4] + a[6] * b[5] + a[10] * b[6] + a[14] * b[7],//a12
		a[3] * b[4] + a[7] * b[5] + a[11] * b[6] + a[15] * b[7],//a13

		a[0] * b[8] + a[4] * b[9] + a[8] * b[10] + a[12] * b[11],//a20
		a[1] * b[8] + a[5] * b[9] + a[9] * b[10] + a[13] * b[11],//a21
		a[2] * b[8] + a[6] * b[9] + a[10] * b[10] + a[14] * b[11],//a22
		a[3] * b[8] + a[7] * b[9] + a[11] * b[10] + a[15] * b[11],//a23

		a[0] * b[12] + a[4] * b[13] + a[8]  * b[14] + a[12] * b[15],//a30
		a[1] * b[12] + a[5] * b[13] + a[9]  * b[14] + a[13] * b[15],//a31
		a[2] * b[12] + a[6] * b[13] + a[10] * b[14] + a[14] * b[15],//a32
		a[3] * b[12] + a[7] * b[13] + a[11] * b[14] + a[15] * b[15]//a33
		);



	/**this = Transformation(
		a[0] * b[0] + a[4] * b[1] + a[12] * b[3],
		a[0] * b[4] + a[4] * b[5] + a[12] * b[7],
		a[0] * b[12] + a[4] * b[13] + a[12] * b[15],
		a[1] * b[0] + a[5] * b[1] + a[13] * b[3],
		a[1] * b[4] + a[5] * b[5] + a[13] * b[7],
		a[1] * b[12] + a[5] * b[13] + a[13] * b[15],
		a[3] * b[0] + a[7] * b[1] + a[15] * b[3],
		a[3] * b[4] + a[7] * b[5] + a[15] * b[7],
		a[3] * b[12] + a[7] * b[13] + a[15] * b[15]);*/

	return *this;
}

Transformation& Transformation::translate(float x, float y, float z)
{
	Transformation translation(
		1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		x  , y  , z  , 1.f);

	return combine(translation);
}

Transformation& Transformation::translate(const Vector& offset)
{
	return translate(offset.x, offset.y, offset.z);
}

Transformation & Transformation::rotate(Vector &angles)
{

	if (angles.x != 0)
	{
		rotateX(angles.x);
	}
	if (angles.y != 0)
	{
		rotateY(angles.y);
	}
	if (angles.z != 0)
	{
		rotateZ(angles.z);
	}
	return *this;
}

Transformation& Transformation::rotateX(float angle)
{
	float rad = angle * 3.141592654f / 180.f;
	float cos = std::cos(rad);
	float sin = std::sin(rad);

	Transformation rotation(1.f, 0.f, 0.f,
		0.f, cos, sin,
		0.f, -sin, cos);

	return combine(rotation);
}

Transformation& Transformation::rotateY(float angle)
{
	float rad = angle * 3.141592654f / 180.f;
	float cos = std::cos(rad);
	float sin = std::sin(rad);

	Transformation rotation(cos, 0.f, -sin,
		0.f, 1.f, 0.f,
		sin, 0.f, cos);

	return combine(rotation);
}

Transformation& Transformation::rotateZ(float angle)
{
	float rad = angle * 3.141592654f / 180.f;
	float cos = std::cos(rad);
	float sin = std::sin(rad);

	Transformation rotation(cos, sin, 0.f,
		-sin, cos, 0.f,
		0.f, 0.f, 1.f);

	return combine(rotation);
}

Transformation & Transformation::rotateToCenter(Vector & vec_a)
{

	float angle_x = angleBetweenVectors3(vec_a, Vector(vec_a.x, 0.f, vec_a.z));
	float angle_y = angleBetweenVectors3(Vector(vec_a.x, 0.f, vec_a.z), Vector(0.f, 0.f, 1.f));

	return rotateX(angle_x).rotateY(angle_y);
}

Transformation& Transformation::scale(float scaleX, float scaleY, float scaleZ)
{
	Transformation scaling(scaleX, 0.f, 0.f,
		0.f, scaleY, 0.f,
		0.f, 0.f, scaleZ);

	return combine(scaling);
}

Transformation& Transformation::scale(const Vector& factors)
{
	return scale(factors.x, factors.y, factors.z);
}

float Transformation::angleBetweenVectors3(Vector vec_a, Vector vec_b)
{
	return std::acos(vec_a.x * vec_b.x + vec_a.y * vec_b.y + vec_a.z * vec_b.z) /
		sqrt(vec_a.x*vec_a.x + vec_a.y*vec_a.y + vec_a.z*vec_a.z)*
		sqrt(vec_b.x*vec_b.x + vec_b.y*vec_b.y + vec_b.z*vec_b.z);
}

float Transformation::angleBetweenVectors(float ax, float ay, float bx, float by)
{
	return std::acos(ax * bx + ay *by) /
		sqrt(ax*ax + ay*ay)*
		sqrt(bx*bx + by*by);
}

Transformation operator *(const Transformation& left, const Transformation& right)
{
	return Transformation(left).combine(right);
}

Transformation& operator *=(Transformation& left, const Transformation& right)
{
	return left.combine(right);
}

Vector* operator *(const Transformation& left, const Vector& right)
{
	return left.transformPoint(right);
}

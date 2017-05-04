#include "Transformation.h"



const Transformation Transformation::Identity;

Transformation::Transformation()
{
	// Identity matrix
	m_matrix[0] = 1.f; m_matrix[4] = 0.f; m_matrix[8] = 0.f; m_matrix[12] = 0.f;
	m_matrix[1] = 0.f; m_matrix[5] = 1.f; m_matrix[9] = 0.f; m_matrix[13] = 0.f;
	m_matrix[2] = 0.f; m_matrix[6] = 0.f; m_matrix[10] = 1.f; m_matrix[14] = 0.f;
	m_matrix[3] = 0.f; m_matrix[7] = 0.f; m_matrix[11] = 0.f; m_matrix[15] = 1.f;
}

Transformation::Transformation(float a00, float a01, float a02,
	float a10, float a11, float a12,
	float a20, float a21, float a22)
{
	m_matrix[0] = a00; m_matrix[4] = a01; m_matrix[8] = a02; m_matrix[12] = 0.f;
	m_matrix[1] = a10; m_matrix[5] = a11; m_matrix[9] = a12; m_matrix[13] = 0.f;
	m_matrix[2] = a20; m_matrix[6] = a21; m_matrix[10] = a22; m_matrix[14] = 0.f;
	m_matrix[3] = 0.f; m_matrix[7] = 0.f; m_matrix[11] = 0.f; m_matrix[15] = 1.f;
}

Transformation::Transformation(float a00, float a01, float a02, float a03,
	float a10, float a11, float a12, float a13,
	float a20, float a21, float a22, float a23,
	float a30, float a31, float a32, float a33)
{
	m_matrix[0] = a00; m_matrix[4] = a01; m_matrix[8] = a02; m_matrix[12] = a03;
	m_matrix[1] = a10; m_matrix[5] = a11; m_matrix[9] = a12; m_matrix[13] = a13;
	m_matrix[2] = a20; m_matrix[6] = a21; m_matrix[10] = a22; m_matrix[14] = a23;
	m_matrix[3] = a30; m_matrix[7] = a31; m_matrix[11] = a32; m_matrix[15] = a33;
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
	return new Vector(m_matrix[0] * x + m_matrix[1] * y + m_matrix[2] * z,
		m_matrix[5] * x + m_matrix[6] * y + m_matrix[7] * z,
		m_matrix[10] * x + m_matrix[11] * y + m_matrix[12] * z);
}

Vector *Transformation::transformPoint(const Vector& point) const
{
	return transformPoint(point.x, point.y, point.z);
}

Transformation& Transformation::combine(const Transformation& transformation)
{
	const float* a = m_matrix;
	const float* b = transformation.m_matrix;

	*this = Transformation(a[0] * b[0] + a[4] * b[1] + a[12] * b[3],
		a[0] * b[4] + a[4] * b[5] + a[12] * b[7],
		a[0] * b[12] + a[4] * b[13] + a[12] * b[15],
		a[1] * b[0] + a[5] * b[1] + a[13] * b[3],
		a[1] * b[4] + a[5] * b[5] + a[13] * b[7],
		a[1] * b[12] + a[5] * b[13] + a[13] * b[15],
		a[3] * b[0] + a[7] * b[1] + a[15] * b[3],
		a[3] * b[4] + a[7] * b[5] + a[15] * b[7],
		a[3] * b[12] + a[7] * b[13] + a[15] * b[15]);

	return *this;
}

Transformation& Transformation::translate(float x, float y, float z)
{
	Transformation translation(1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		x, y, z, 1.f);

	return combine(translation);
}

Transformation& Transformation::translate(const Vector& offset)
{
	return translate(offset.x, offset.y, offset.z);
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

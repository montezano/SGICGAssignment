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
	m_matrix[0] = a00; m_matrix[4] = a01; m_matrix[8] = 0.f; m_matrix[12] = a02;
	m_matrix[1] = a10; m_matrix[5] = a11; m_matrix[9] = 0.f; m_matrix[13] = a12;
	m_matrix[2] = 0.f; m_matrix[6] = 0.f; m_matrix[10] = 1.f; m_matrix[14] = 0.f;
	m_matrix[3] = a20; m_matrix[7] = a21; m_matrix[11] = 0.f; m_matrix[15] = a22;
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

Vector *Transformation::transformPoint(float x, float y) const
{
	return new Vector(m_matrix[0] * x + m_matrix[4] * y + m_matrix[12],
		m_matrix[1] * x + m_matrix[5] * y + m_matrix[13]);
}

Vector *Transformation::transformPoint(const Vector& point) const
{
	return transformPoint(point.x, point.y);
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

Transformation& Transformation::translate(float x, float y)
{
	Transformation translation(1, 0, x,
		0, 1, y,
		0, 0, 1);

	return combine(translation);
}

Transformation& Transformation::translate(const Vector& offset)
{
	return translate(offset.x, offset.y);
}

Transformation& Transformation::rotate(float angle)
{
	float rad = angle * 3.141592654f / 180.f;
	float cos = std::cos(rad);
	float sin = std::sin(rad);

	Transformation rotation(cos, -sin, 0,
		sin, cos, 0,
		0, 0, 1);

	return combine(rotation);
}

Transformation& Transformation::scale(float scaleX, float scaleY)
{
	Transformation scaling(scaleX, 0, 0,
		0, scaleY, 0,
		0, 0, 1);

	return combine(scaling);
}

Transformation& Transformation::scale(const Vector& factors)
{
	return scale(factors.x, factors.y);
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
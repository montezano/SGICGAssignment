#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "Vector.h"

class Matrix
{
public:
	Matrix();

	Matrix(float a00, float a01, float a02,
		float a10, float a11, float a12,
		float a20, float a21, float a22);

	Matrix(float a[9]);

	const float* getMatrix() const;

	Matrix getInverse() const;

	/// \brief Product of matrix with a 2D point
	Vector multPoint(float x, float y) const;

	/// \brief Product of matrix with a 2D point
	Vector multPoint(const Vector& point) const;

	/// \brief Combine the current matrix with another one (Multply)
	Matrix& combine(const Matrix& matrix);

	static const Matrix Identity;

private:
	float m_matrix[16];
};

/// \brief Overload of binary operator * to combine two matrix
Matrix operator *(const Matrix& left, const Matrix& right);

/// \brief Overload of binary operator *= to combine two matrix
Matrix& operator *=(Matrix& left, const Matrix& right);

/// \brief Overload of binary operator * to product a point
Vector operator *(const Matrix& left, const Vector& right);


#endif // !__MATRIX_H__
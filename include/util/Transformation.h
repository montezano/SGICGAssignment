#ifndef __TRANSFORMATION_H__
#define __TRANSFORMATION_H__

#include "Vector.h"

#include <cmath>

class Transformation
{
public:

	Transformation();

	Transformation(float a00, float a01, float a02,
		float a10, float a11, float a12,
		float a20, float a21, float a22);

	Transformation(float a00, float a01, float a02, float a03,
		float a10, float a11, float a12, float a13,
		float a20, float a21, float a22, float a23,
		float a30, float a31, float a32, float a33);

	const float* getMatrix() const;

	Transformation getInverse() const;

	/// \brief Transform a 2D point
	Vector *transformPoint(float x, float y, float z) const;

	/// \brief Transform a 2D point
	Vector *transformPoint(const Vector& point) const;


	/// \brief Combine the current transform with another one
	Transformation& combine(const Transformation& transform);

	/// \brief Combine the current transform with a translation
	Transformation& translate(float x, float y, float z);

	/// \brief Combine the current transform with a translation
	Transformation& translate(const Vector& offset);

	/// \brief Combine the current transform with a rotation
	Transformation& rotate(Vector &angles);

	/// \brief Combine the current transform with a rotation around z axis
	Transformation& rotateX(float angle);

	/// \brief Combine the current transform with a rotation around y axis
	Transformation& rotateY(float angle);

	/// \brief Combine the current transform with a rotation around z axis
	Transformation& rotateZ(float angle);

	/// \brief Combine the current transform with a scaling
	Transformation& scale(float scaleX, float scaleY, float scaleZ);

	/// \brief Combine the current transform with a scaling
	Transformation& scale(const Vector& factors);

	static const Transformation Identity;

private:

	float m_matrix[16];
};


/// \brief Overload of binary operator * to combine two transforms
Transformation operator *(const Transformation& left, const Transformation& right);

/// \brief Overload of binary operator *= to combine two transforms
Transformation& operator *=(Transformation& left, const Transformation& right);

/// \brief Overload of binary operator * to transform a point
Vector* operator *(const Transformation& left, const Vector& right);


#endif // __TRANSFORMATION_H__

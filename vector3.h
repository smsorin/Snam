/* Copyright 2008 Sorin Stancu-Mara */

#ifndef __VECTOR3_H__
#define __VECTOR3_H__
#include <iostream>

/* Structure used for the math part of the algorithms. Not inteded for drawing */
class Vector3 {
  public:
	Vector3();
	Vector3(double x, double y, double z);
//	Vector3(const Vertex& v);
//	Vector3(const Vertex* v);

	double Length() const;
	Vector3 Normalize() const;
	Vector3 Cross(const Vector3& v) const;
	double Dot(const Vector3& v) const;
    double x,y,z;
};

bool operator==(const Vector3& lhs, const Vector3& rhs);
Vector3 operator+(const Vector3& lhs, const Vector3& rhs);
Vector3 operator-(const Vector3& lhs, const Vector3& rhs);
Vector3 operator*(const Vector3& lhs, const Vector3& rhs);
Vector3 operator*(const Vector3& lhs, double rhs);
Vector3 operator*(double lhs, const Vector3& rhs);
Vector3 operator/(const Vector3& lhs, double rhs);
Vector3& operator/=(Vector3& lhs, double rhs);
Vector3& operator+=(Vector3& lhs, const Vector3& rhs);
Vector3& operator-=(Vector3& lhs, const Vector3& rhs);
Vector3& operator*=(Vector3& lhs, double rhs);
std::ostream& operator<<(std::ostream& out, const Vector3& rhs);

#endif  // __VECTOR3_H__


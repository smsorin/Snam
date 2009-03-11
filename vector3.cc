/* Copyright 2008 Sorin Stancu-Mara */

#include "vector3.h"
#include <cmath>

Vector3::Vector3() : x(0), y(0), z(0) {}
Vector3::Vector3(double x, double y, double z) : x(x), y(y), z(z) {}
/*Vector3::Vector3(const Vertex& v) {
	x = v.getX();
	y = v.getY();
	z = v.getZ();
}
Vector3::Vector3(const Vertex* v) {
	x = v->getX();
	y = v->getY();
	z = v->getZ();
}*/

double Vector3::Length() const {
	return sqrt( x*x +y*y + z*z);

}
Vector3 Vector3::Normalize() const {
	double len = Length();
	return Vector3(x / len, y / len, z / len);
}

Vector3 Vector3::Cross(const Vector3& v) const {
	return Vector3(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
}

double Vector3::Dot(const Vector3& v) const {
	return x*v.x + y*v.y + z*v.z;
}

bool operator==(const Vector3& lhs, const Vector3& rhs) {
	return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

Vector3 operator+(const Vector3& lhs, const Vector3& rhs) {
	return Vector3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

Vector3 operator-(const Vector3& lhs, const Vector3& rhs) {
	return Vector3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

Vector3 operator*(const Vector3& lhs, const Vector3& rhs) {
	return lhs.Cross(rhs);
}

Vector3 operator*(const Vector3& lhs, double rhs) {
	return Vector3(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
}

Vector3 operator*(double rhs, const Vector3& lhs) {
	return Vector3(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
}

Vector3 operator/(const Vector3& lhs, double rhs) {
	return Vector3(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
}

Vector3& operator/=(Vector3& lhs, double rhs) {
	lhs.x /= rhs;
	lhs.y /= rhs;
	lhs.z /= rhs;
	return lhs;
}

Vector3& operator+=(Vector3& lhs, const Vector3& rhs) {
	lhs.x += rhs.x;
	lhs.y += rhs.y;
	lhs.z += rhs.z;
	return lhs;
}

Vector3& operator-=(Vector3& lhs, const Vector3& rhs) {
	lhs.x -= rhs.x;
	lhs.y -= rhs.y;
	lhs.z -= rhs.z;
	return lhs;
}

Vector3& operator*=(Vector3& lhs, double rhs) {
	lhs.x *= rhs;
	lhs.y *= rhs;
	lhs.z *= rhs;
	return lhs;
}

std::ostream& operator<<(std::ostream& out, const Vector3& rhs) {
	out << rhs.x << ", " << rhs.y << ", " << rhs.z ;
	return out;
}

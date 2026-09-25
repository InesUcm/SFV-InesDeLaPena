#include "Vector3D.h"

Vector3D::Vector3D() : x(0), y(0), z(0){}
Vector3D::Vector3D(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
Vector3D::Vector3D(physx::PxVec3 Pxvec3): x(Pxvec3.x), y(Pxvec3.y), z(Pxvec3.z) {}

float Vector3D::magnitude() const{
	return sqrtf(x*x + y*y + z*z);
}

Vector3D Vector3D::normalize() const {
	float mag = magnitude();
	if (mag > 0.0f) {
		return Vector3D(x / mag, y / mag, z / mag);
	}
	return Vector3D(0.0f, 0.0f, 0.0f);
}

float Vector3D::dot(const Vector3D& v) const {
	return x * v.x + y * v.y + z * v.z;
}

Vector3D Vector3D::cross(const Vector3D& v) const {
	return Vector3D(
		y * v.z - z * v.y,
		z * v.x - x * v.z,
		x * v.y - y * v.x
	);
}

Vector3D& Vector3D::operator=(const Vector3D& v) {
	if (this != &v) {
		x = v.x;
		y = v.y;
		z = v.z;
	}
	return *this;
}

Vector3D Vector3D::operator+(const Vector3D& v) const {
	return Vector3D(x + v.x, y + v.y, z + v.z);
}

Vector3D Vector3D::operator-(const Vector3D& v) const {
	return Vector3D(x - v.x, y - v.y, z - v.z);
}

Vector3D Vector3D::operator*(float scalar) const {
	return Vector3D(x * scalar, y * scalar, z * scalar);
}

Vector3D& Vector3D::operator+=(const Vector3D& v) {
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

Vector3D::operator physx::PxVec3() const {
	return physx::PxVec3(x, y, z);
}
#include "Vector2D.h"
#include<cmath>

Vector2D& Vector2D::Add(const Vector2D& v) {
	x += v.x;
	y += v.y;
	return *this;
}
Vector2D& Vector2D::operator+=(const Vector2D& v) {
	return this->Add(v);
}

Vector2D& operator+(Vector2D& v1, const Vector2D& v2) {
	return v1.Add(v2);
}
Vector2D& Vector2D::Multiply(const Vector2D& v) {
	x *= v.x;
	y *= v.y;
	return *this;
}
Vector2D& Vector2D::operator*=(const Vector2D& v) {
	return this->Multiply(v);
}

Vector2D& operator*(Vector2D& v1, const Vector2D& v2) {
	return v1.Multiply(v2);
}

Vector2D& Vector2D::Subtract(const Vector2D& v) {
	x -= v.x;
	y -= v.y;
	return *this;
}
Vector2D& Vector2D::operator-=(const Vector2D& v) {
	return this->Subtract(v);
}

Vector2D& operator-(Vector2D& v1, const Vector2D& v2) {
	return v1.Subtract(v2);
}
Vector2D& Vector2D::Divide(const Vector2D& v) {
	x /= v.x;
	y /= v.y;
	return *this;
}
Vector2D& Vector2D::operator/=(const Vector2D& v) {
	return this->Divide(v);
}

Vector2D& operator/(Vector2D& v1, const Vector2D& v2) {
	return v1.Divide(v2);
}

ostream& operator<<(ostream& out, const Vector2D& v) {
	return out << "Vec2D(" << v.x << ',' << v.y << ')';
}

Vector2D& Vector2D::operator*(const int i) {
	this->x *= i;
	this->y *= i;
	return *this;
}

Vector2D& Vector2D::operator*=(const int i) {
	this->x *= i;
	this->y *= i;
	return *this;
}
Vector2D& Vector2D::Zero() {
	this->x = 0;
	this->y = 0;
	return *this;
}
Vector2D& Vector2D::normalize() {
	float length = std::sqrtf(x * x + y * y);
	if (length != 0) {
		x /= length;
		y /= length;
	}
	return *this;
}

float Vector2D::angle() const {
	return std::atan2f(y, x);
}
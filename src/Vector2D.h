#pragma once
#include<iostream>
using std::ostream;

class Vector2D {
public:
	float x;
	float y;
	Vector2D(float px=0.f, float py=0.f): x{px}, y{py} {}

	Vector2D& Add(const Vector2D& v);
	Vector2D& Subtract(const Vector2D& v);
	Vector2D& Multiply(const Vector2D& v);
	Vector2D& Divide(const Vector2D& v);
	friend Vector2D& operator+(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator-(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator*(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator/(Vector2D& v1, const Vector2D& v2);
	Vector2D& operator+=(const Vector2D& v);
	Vector2D& operator-=(const Vector2D& v);
	Vector2D& operator*=(const Vector2D& v);
	Vector2D& operator/=(const Vector2D& v);

	Vector2D& operator*(const int i);
	Vector2D& operator*=(const int i);
	Vector2D& Zero();
	Vector2D& normalize();
	float angle() const;

	friend ostream& operator<<(ostream& out, const Vector2D& v);
};
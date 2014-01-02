#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <math.h>

class Vector2D
{
public:
	Vector2D(){}
	Vector2D(float x, float y): m_x(x), m_y(y) {}

	void setX(float x) {m_x = x;}
	float getX() {return m_x;}
	void setY(float y) {m_y = y;}
	float getY() {return m_y;}

	float length() {return sqrt(m_x*m_x + m_y*m_y);}

	//Addition
	//
	Vector2D operator+ (const Vector2D& v2) 
	{
		return Vector2D(m_x + v2.m_x, m_y + v2.m_y);
	}
	friend Vector2D& operator+= (Vector2D& v1, const Vector2D& v2)
	{
		v1.m_x += v2.m_x;
		v1.m_y += v2.m_y;

		return v1;
	}

	//Substraction
	//
	Vector2D operator- (const Vector2D& v2)
	{
		return Vector2D(m_x-v2.m_x, m_y-v2.m_y);
	}
	friend Vector2D& operator-= (Vector2D& v1, const Vector2D& v2)
	{
		v1.m_x -= v2.m_x;
		v1.m_y -= v2.m_y;

		return v1;
	}

	//Multiplication
	//
	Vector2D operator* (float scalar)
	{
		return Vector2D(m_x*scalar, m_y*scalar);
	}
	Vector2D& operator*= (float scalar)
	{
		m_x *= scalar;
		m_y *= scalar;

		return *this;
	}

	//Division
	//
	Vector2D operator/ (float scalar)
	{
		return Vector2D(m_x/scalar, m_y/scalar);
	}
	Vector2D& operator /= (float scalar)
	{
		m_x /= scalar;
		m_y /= scalar;

		return *this;
	}
	
	//Normalization
	//
	Vector2D normalize()
	{
		float l = this->length();
		if (l > 0)
		{
			(*this) /= l;
		}
	}

private:
	float m_x;
	float m_y;
};

#endif
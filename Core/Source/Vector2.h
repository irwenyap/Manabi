#ifndef VECTOR2_H
#define VECTOR2_H

struct Vector2
{
	float x, y;
	Vector2(float a = 0.0f, float b = 0.0f);
	Vector2(const Vector2& rhs);


	//Vector2( float a = 0, float b = 0 ); //default constructor
	//Vector2( const Vector2 &rhs ); //copy constructor
	void Set( float a, float b ); //Set all data
	void Set(Vector2& other);
	Vector2 operator+( const Vector2& rhs ) const; //Vector addition
	Vector2 operator-( const Vector2& rhs ) const; //Vector subtraction
	Vector2 operator-( void ) const; //Unary negation
	Vector2 operator*( float scalar ) const; //Scalar multiplication
	float Length( void ) const; //Get magnitude
	float Dot( const Vector2& rhs ) const; //Dot product
	Vector2 Normalized( void ); //Return a copy of this vector, normalized
};
#endif

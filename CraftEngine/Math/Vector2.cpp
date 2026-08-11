#include "Vector2.h"

#include <cassert>

namespace Craft
{
	Vector2::Vector2(int x, int y)
		: x(x), y(y)
	{}

	Vector2::operator COORD() const
	{
		COORD coord = {};
		coord.X = static_cast<short>(x);
		coord.Y = static_cast<short>(y);

		return coord;
	}

	Vector2::operator COORD()
	{
	
		COORD coord = {};
		coord.X = static_cast<short>(x);
		coord.Y = static_cast<short>(y);

		return coord;
	}

	Vector2 Vector2::operator+(const Vector2 & other) const
	{
		return Vector2(x + other.x, y + other.y);
	}
	Vector2 Vector2::operator-(const Vector2& other) const
	{
		return Vector2(x - other.x, y - other.y);
	}
	Vector2 Vector2::operator*(const Vector2& other) const
	{
		return Vector2(x * other.x, y * other.y);
	}
	Vector2 Vector2::operator/(const Vector2& other) const
	{
		assert(other.x != 0 && other.y != 0);
		return Vector2(x / other.x, y / other.y);
	}

	Vector2& Vector2::operator=(const Vector2& other)
	{
		x = other.x;
		y = other.y;
		return *this;
	}

	bool Vector2::operator==(const Vector2& other) const
	{
		return (x == other.x) && (y == other.y);
	}
	bool Vector2::operator!=(const Vector2& other) const
	{
		return !(*this == other);
	}
}
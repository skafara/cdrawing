#pragma once


/**
 * Vector in 2D space
 * @tparam T Coords Type
 */
template<typename T>
class Vector2D {
public:
	/**
	 * Transparently constructs
	 * @param x x
	 * @param y y
	 */
	Vector2D(T x, T y) : _x(x), _y(y) {
		//
	};

	/**
	 * Returns x
	 * @return x
	 */
	T Get_X() const {
		return _x;
	};
	/**
	 * Returns y
	 * @return y
	 */
	T Get_Y() const {
		return _y;
	};

	/**
	 * Compares coords on equality with ==
	 * @param rhs rhs
	 * @return Result
	 */
	bool operator==(const Vector2D &rhs) const {
		return _x == rhs._x && _y == rhs._y;
	}

	/**
	 * Adds rhs in-place
	 * @param rhs rhs
	 * @return This
	 */
	Vector2D &operator+=(const Vector2D &rhs) {
		_x += rhs._x;
		_y += rhs._y;

		return *this;
	};

	/**
	 * Subtracts rhs in-place
	 * @param rhs rhs
	 * @return This
	 */
	Vector2D &operator-=(const Vector2D &rhs) {
		_x -= rhs._x;
		_y -= rhs._y;

		return *this;
	};

	/**
	 * Multiples by rhs in-place
	 * @tparam S rhs Type
	 * @param rhs rhs
	 * @return This
	 */
	template <typename S>
	Vector2D &operator*=(S rhs) {
		_x *= rhs;
		_y *= rhs;

		return *this;
	};

private:
	T _x;
	T _y;

};

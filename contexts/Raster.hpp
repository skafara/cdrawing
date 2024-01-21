#pragma once

#include "../types.hpp"

#include <vector>
#include <ostream>

#include <map>


/**
 * Color
 */
enum class Color {
	kWhite,
	kBlack
};

/**
 * Raster
 */
class Raster {
private:
	const size_t _width;
	const size_t _height;

	std::vector<std::vector<Color>> _pixels;

public:
	/**
	 * Transparently constructs
	 * @param width Width
	 * @param height Height
	 */
	Raster(size_t width, size_t height);

	/**
	 * Returns pixel color on [x,y]
	 * @param x x
	 * @param y y
	 * @return Pixel color
	 */
	Color Get_Pixel(t_Raster_Num x, t_Raster_Num y);
	/**
	 * Sets pixel color on [x,y]
	 * @param color Color
	 * @param x x
	 * @param y y
	 */
	void Set_Pixel(Color color, t_Raster_Num x, t_Raster_Num y);

};

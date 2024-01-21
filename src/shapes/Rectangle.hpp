#pragma once

#include "I_Shape.hpp"
#include "Line.hpp"


/**
 * Rectangle
 */
class Rectangle : public I_Shape {
private:
	t_Point2D _top_left;
	t_Point2D _top_right;
	t_Point2D _bottom_left;
	t_Point2D _bottom_right;

	std::array<std::reference_wrapper<t_Point2D>, 4> Get_Corners();
	std::array<Line, 4> Get_Lines() const;

public:
	/**
	 * Constructs a rectangle given a top-left corner and its width and height
	 * @param top_left Top-left corner
	 * @param width Width
	 * @param height Height
	 */
	Rectangle(const t_Point2D &top_left, t_Precision width, t_Precision height);

	void Translate(const t_Point2D &offset) override;
	void Rotate(const t_Point2D &center, t_Precision deg) override;
	void Scale(const t_Point2D &center, t_Precision factor) override;

	/**
	 * Vectorizes itself into a stream as 4 lines
	 * @param ostream Output stream
	 */
	void Vectorize(std::ostream &ostream) const override;
	/**
	 * Rasterizes itself into a raster as 4 lines
	 * @param raster Raster
	 */
	void Rasterize(Raster &raster) const override;

};

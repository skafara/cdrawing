#pragma once

#include "I_Shape.hpp"


/**
 * Line
 */
class Line : public I_Shape {
private:
	t_Point2D _begin;
	t_Point2D _end;

public:
	/**
	 * Transparently constructs
	 * @param begin Begin
	 * @param end End
	 */
	Line(const t_Point2D &begin, const t_Point2D &end);

	void Translate(const t_Point2D &offset) override;
	void Rotate(const t_Point2D &center, t_Precision deg) override;
	void Scale(const t_Point2D &center, t_Precision factor) override;

	void Vectorize(std::ostream &ostream) const override;
	void Rasterize(Raster &raster) const override;

};

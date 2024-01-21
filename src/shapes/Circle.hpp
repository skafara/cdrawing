#pragma once

#include "I_Shape.hpp"


/**
 * Circle
 */
class Circle : public I_Shape {
private:
	t_Point2D _center;
	t_Precision _radius;

public:
	/**
	 * Transparently constructs
	 * @param center Center
	 * @param radius Radius
	 */
	Circle(const t_Point2D &center, t_Precision radius);

	void Translate(const t_Point2D &offset) override;
	void Rotate(const t_Point2D &center, t_Precision deg) override;
	void Scale(const t_Point2D &center, t_Precision factor) override;

	void Vectorize(std::ostream &ostream) const override;
	void Rasterize(Raster &raster) const override;

};

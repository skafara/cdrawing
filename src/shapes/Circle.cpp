#include "Circle.hpp"
#include "Transformer.hpp"

#include <cmath>


Circle::Circle(const t_Point2D &center, t_Precision radius) : _center(center), _radius(radius) {
	//
}

void Circle::Translate(const t_Point2D &offset) {
	Transformer::Translate(_center, offset);
}

void Circle::Rotate(const t_Point2D &center, t_Precision deg) {
	Transformer::Rotate(_center, center, deg);
}

void Circle::Scale(const t_Point2D &center, t_Precision factor) {
	Transformer::Scale(_center, center, factor);
	Transformer::Scale(_radius, factor);
}

void Circle::Vectorize(std::ostream &ostream) const {
	ostream << R"(<circle cx=")"
			<< _center.Get_X()
			<< R"(" cy=")"
			<< _center.Get_Y()
			<< R"(" r=")"
			<< _radius
			<< R"(" stroke=")"
			<< kStroke_Color_Hex
			<< R"(" stroke-width=")"
			<< kStroke_Width
			<< R"(" fill-opacity="0" />)";
}

void Circle::Rasterize(Raster &raster) const {
	for (t_Raster_Num i = 0; i < kStroke_Width; ++i) {
		for (t_Raster_Num j = 0; j < kStroke_Width; ++j) {
			const auto x_c = static_cast<t_Raster_Num>(std::round(_center.Get_X())) + i;
			const auto y_c = static_cast<t_Raster_Num>(std::round(_center.Get_Y())) + j;

			t_Raster_Num x = -static_cast<t_Raster_Num>(_radius);
			t_Raster_Num y = 0;
			t_Raster_Num err = 2 - static_cast<t_Raster_Num>(2 * _radius);
			do {
				raster.Set_Pixel(kStroke_Color, x_c - x, y_c + y);
				raster.Set_Pixel(kStroke_Color, x_c - y, y_c - x);
				raster.Set_Pixel(kStroke_Color, x_c + x, y_c - y);
				raster.Set_Pixel(kStroke_Color, x_c + y, y_c + x);

				const t_Raster_Num r = err;
				if (r <= y) {
					++y;
					err += y * 2 + 1;
				}
				if (r > x || err > y) {
					++x;
					err += x * 2 + 1;
				}
			}
			while (x < 0);
		}
	}
}

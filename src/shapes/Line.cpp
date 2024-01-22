#include "Line.hpp"
#include "Transformer.hpp"

#include <cmath>


Line::Line(const t_Point2D &begin, const t_Point2D &end) : _begin(begin), _end(end) {
	//
}

void Line::Translate(const t_Point2D &offset) {
	Transformer::Translate(_begin, offset);
	Transformer::Translate(_end, offset);
}

void Line::Rotate(const t_Point2D &center, t_Precision deg) {
	Transformer::Rotate(_begin, center, deg);
	Transformer::Rotate(_end, center, deg);
}

void Line::Scale(const t_Point2D &center, t_Precision factor) {
	Transformer::Scale(_begin, center, factor);
	Transformer::Scale(_end, center, factor);
}

void Line::Vectorize(std::ostream &ostream) const {
	ostream << R"(<line x1=")"
			<< _begin.Get_X()
			<< R"(" y1=")"
			<< _begin.Get_Y()
			<< R"(" x2=")"
			<< _end.Get_X()
			<< R"(" y2=")"
			<< _end.Get_Y()
			<< R"(" stroke=")"
			<< kStroke_Color_Hex
		    << R"(" stroke-width=")"
			<< kStroke_Width
			<< R"(" fill-opacity="0" />)";
}

void Line::Rasterize(Raster &raster) const {
	for (t_Raster_Num i = 0; i < kStroke_Width; ++i) {
		for (t_Raster_Num j = 0; j < kStroke_Width; ++j) {
			const auto x1 = static_cast<t_Raster_Num>(std::round(_end.Get_X())) + i;
			const auto y1 = static_cast<t_Raster_Num>(std::round(_end.Get_Y())) + j;
			auto x0 = static_cast<t_Raster_Num>(std::round(_begin.Get_X())) + i;
			auto y0 = static_cast<t_Raster_Num>(std::round(_begin.Get_Y())) + j;

			t_Raster_Num dx = std::abs(x1 - x0);
			t_Raster_Num sx = (x0 < x1) ? 1 : -1;
			t_Raster_Num dy = -std::abs(y1 - y0);
			t_Raster_Num sy = (y0 < y1) ? 1 : -1;
			t_Raster_Num err = dx + dy;
			for (;;) {
				raster.Set_Pixel(kStroke_Color, x0, y0);
				if (x0 == x1 && y0 == y1) {
					break;
				}

				const t_Raster_Num e2 = 2 * err;
				if (e2 >= dy) {
					err += dy;
					x0 += sx;
				}
				if (e2 <= dx) {
					err += dx;
					y0 += sy;
				}
			}
		}
	}
}

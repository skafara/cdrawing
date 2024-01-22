#include "Rectangle.hpp"
#include "Transformer.hpp"

#include <algorithm>


Rectangle::Rectangle(const t_Point2D &top_left, t_Precision width, t_Precision height) :
	_top_left(top_left),
	_top_right(top_left.Get_X() + width, top_left.Get_Y()),
	_bottom_left(top_left.Get_X(), top_left.Get_Y() + height),
	_bottom_right(top_left.Get_X() + width, top_left.Get_Y() + height)
{
	//
}

void Rectangle::Translate(const t_Point2D &offset) {
	std::ranges::for_each(Get_Corners(), [&offset] (auto &corner) {
		Transformer::Translate(corner, offset);
	});
}

void Rectangle::Rotate(const t_Point2D &center, t_Precision deg) {
	std::ranges::for_each(Get_Corners(), [&center, deg] (auto &corner) {
		Transformer::Rotate(corner, center, deg);
	});
}

void Rectangle::Scale(const t_Point2D &center, t_Precision factor) {
	std::ranges::for_each(Get_Corners(), [&center, factor] (auto &corner) {
		Transformer::Scale(corner, center, factor);
	});
}

std::array<Line, 4> Rectangle::Get_Lines() const {
	return {
		Line{_top_left, _top_right},
		Line{_top_right, _bottom_right},
		Line{_bottom_right, _bottom_left},
		Line{_bottom_left, _top_left}
	};
}

std::array<std::reference_wrapper<t_Point2D>, 4> Rectangle::Get_Corners() {
	return {
		_top_left,
		_top_right,
		_bottom_left,
		_bottom_right
	};
}

void Rectangle::Vectorize(std::ostream &ostream) const {
	std::ranges::for_each(Get_Lines(), [&ostream] (const auto &line) {
		line.Vectorize(ostream);
	});
}

void Rectangle::Rasterize(Raster &raster) const {
	std::ranges::for_each(Get_Lines(), [&raster] (const auto &line) {
		line.Rasterize(raster);
	});
}

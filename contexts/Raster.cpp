#include "Raster.hpp"


Raster::Raster(size_t width, size_t height) : _width(width), _height(height) {
	_pixels.resize(height);
	std::ranges::for_each(_pixels, [this] (auto &pixels) {
		pixels.resize(_height);
		std::ranges::for_each(pixels, [] (auto &color) {
			color = Color::kWhite;
		});
	});
}

Color Raster::Get_Pixel(t_Raster_Num x, t_Raster_Num y) {
	return _pixels[y][x];
}

void Raster::Set_Pixel(Color color, t_Raster_Num x, t_Raster_Num y) {
	if (x < 0 || x >= _width || y < 0 || y >= _height) {
		return;
	}

	_pixels[y][x] = color;
}

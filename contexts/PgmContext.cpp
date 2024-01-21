#include "PgmContext.hpp"
#include "Raster.hpp"


const std::map<Color, const size_t> PgmContext::kSymbols{
		{Color::kWhite, 1},
		{Color::kBlack, 0}
};

PgmContext::PgmContext(size_t width, size_t height) : GraphicsContext(width, height) {
	//
}

void PgmContext::operator>>(std::ostream &ostream) const {
	ostream << "P2" << std::endl
			<< Get_Width() << " " << Get_Height() << std::endl
			<< std::ranges::max_element(kSymbols, [] (const auto &lhs, const auto &rhs) {
				return rhs.second > lhs.second;
			})->second << std::endl;

	Raster raster{Get_Width(), Get_Height()};
	std::ranges::for_each(Get_Shapes(), [&raster] (const auto &shape) {
		shape->Rasterize(raster);
	});

	for (t_Raster_Num y = 0; y < Get_Height(); ++y) {
		for (t_Raster_Num x = 0; x < Get_Width(); ++x) {
			const Color color = raster.Get_Pixel(x, y);
			ostream << kSymbols.at(color);

			if (x != Get_Width() - 1) {
				ostream << ' ';
			}
		}
		ostream << std::endl;
	}
}

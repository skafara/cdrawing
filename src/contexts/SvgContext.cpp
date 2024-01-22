#include "SvgContext.hpp"

#include <algorithm>


SvgContext::SvgContext(size_t width, size_t height) : GraphicsContext(width, height) {
	//
}

void SvgContext::operator>>(std::ostream &ostream) const {
	ostream << R"(<?xml version="1.0" encoding="UTF-8"?>)" << std::endl;
	ostream << R"(<svg xmlns="http://www.w3.org/2000/svg")"
			<< R"( width=")" << Get_Width() << R"(")"
			<< R"( height=")" << Get_Height() << R"(")"
			<< R"( viewBox="0 0 )" << Get_Width() << " " << Get_Height() << R"(")"
			<< R"( fill="#ffffff">)"
			<< std::endl;

	std::ranges::for_each(Get_Shapes(), [&ostream] (const auto &shape) {
		shape->Vectorize(ostream);
		ostream << std::endl;
	});

	ostream << "</svg>" << std::endl;
}

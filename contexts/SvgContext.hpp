#pragma once

#include "GraphicsContext.hpp"


/**
 * SVG Graphics Context
 */
class SvgContext : public GraphicsContext {
public:
	/**
	 * Transparently constructs
	 * @param width Width
	 * @param height Height
	 */
	SvgContext(size_t width, size_t height);

	void operator>>(std::ostream &ostream) const override;

};

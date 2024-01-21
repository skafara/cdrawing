#pragma once

#include "GraphicsContext.hpp"


/**
 * PGM Graphics Context
 */
class PgmContext : public GraphicsContext {
private:
	static const std::map<Color, const size_t> kSymbols;

public:
	/**
	 * Transparently constructs
	 * @param width Width
	 * @param height Height
	 */
	PgmContext(size_t width, size_t height);

	void operator>>(std::ostream &ostream) const override;

};

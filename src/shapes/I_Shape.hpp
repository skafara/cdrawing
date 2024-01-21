#pragma once

#include "../types.hpp"
#include "../util/Vector2D.hpp"
#include "../contexts/Raster.hpp"
#include "../util/I_Transformable.hpp"

#include <ostream>


/**
 * Geometric Shape Interface
 */
class I_Shape : public I_Transformable {
public:
	static constexpr t_Raster_Num kStroke_Width = 2;
	static constexpr Color kStroke_Color = Color::kBlack;
	static const std::string kStroke_Color_Hex;

	/** Transparently destructs */
	virtual ~I_Shape() = default;

	void Translate(const t_Point2D &offset) override = 0;
	void Rotate(const t_Point2D &center, t_Precision deg) override = 0;
	void Scale(const t_Point2D &center, t_Precision factor) override = 0;

	/**
	 * Vectorizes itself into a stream
	 * @param ostream Output stream
	 */
	virtual void Vectorize(std::ostream &ostream) const = 0;
	/**
	 * Rasterizes itself into a raster
	 * @param raster Raster
	 */
	virtual void Rasterize(Raster &raster) const = 0;

};

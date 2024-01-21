#pragma once

#include "../types.hpp"


class I_Transformable {
public:
	/**
	 * Applies translate transformation
	 * @param offset Offset
	 */
	virtual void Translate(const t_Point2D &offset) = 0;
	/**
	 * Applies rotate transformation
	 * @param center Center of transformation
	 * @param deg Deg
	 */
	virtual void Rotate(const t_Point2D &center, t_Precision deg) = 0;
	/**
	 * Applies scale transformation
	 * @param center Center of transformation
	 * @param factor Factor
	 */
	virtual void Scale(const t_Point2D &center, t_Precision factor) = 0;

};

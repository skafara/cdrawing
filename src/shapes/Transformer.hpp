#pragma once

#include "../types.hpp"


/**
 * Geometric Transformer
 */
class Transformer {
public:
	/**
	 * Applies translate transformation to a vector
	 * @param vector Vector
	 * @param offset Offset
	 */
	static void Translate(t_Point2D &vector, const t_Point2D &offset);
	/**
	 * Applies rotate transformation to a vector
	 * @param vector Vector
	 * @param center Center of transformation
	 * @param deg Deg
	 */
	static void Rotate(t_Point2D &vector, const t_Point2D &center, t_Precision deg);
	/**
	 * Applies scale transformation to a vector
	 * @param vector Vector
	 * @param center Center of transformation
	 * @param factor Factor
	 */
	static void Scale(t_Point2D &vector, const t_Point2D &center, t_Precision factor);
	/**
	 * Applies scale transformation to a distance
	 * @param distance Distance
	 * @param factor Factor
	 */
	static void Scale(t_Precision &distance, t_Precision factor);
};

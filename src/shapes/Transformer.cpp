#include "Transformer.hpp"

#include <cmath>
#include <numbers>


void Transformer::Translate(t_Point2D &vector, const t_Point2D &offset) {
	vector += offset;
}

void Transformer::Rotate(t_Point2D &vector, const t_Point2D &center, t_Precision deg) {
	const t_Precision rad = deg * std::numbers::pi_v<t_Precision> / static_cast<t_Precision>(180.0);

	const t_Precision rad_sin = std::sin(rad);
	const t_Precision rad_cos = std::cos(rad);

	vector -= center;

	vector = t_Point2D{
		rad_cos * vector.Get_X() - rad_sin * vector.Get_Y(),
		rad_sin * vector.Get_X() + rad_cos * vector.Get_Y()
	};

	vector += center;
}

void Transformer::Scale(t_Point2D &vector, const t_Point2D &center, t_Precision factor) {
	vector -= center;

	vector *= factor;

	vector += center;
}

void Transformer::Scale(t_Precision &distance, t_Precision factor) {
	distance *= factor;
}

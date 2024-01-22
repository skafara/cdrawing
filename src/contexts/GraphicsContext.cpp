#include "GraphicsContext.hpp"

#include <algorithm>


GraphicsContext &GraphicsContext::operator<<(std::vector<t_Cmd> cmds) {
	std::ranges::for_each(cmds, [this] (const t_Cmd &cmd) {
		(*this) << cmd;
	});
	return *this;
}

GraphicsContext &GraphicsContext::operator<<(const t_Cmd &cmd) {
	cmd(*this);
	return *this;
}

size_t GraphicsContext::Get_Width() const {
	return _width;
}

size_t GraphicsContext::Get_Height() const {
	return _height;
}

const std::vector<std::unique_ptr<I_Shape>> &GraphicsContext::Get_Shapes() const {
	return _shapes;
}

void GraphicsContext::Draw(const Line &line) {
	_shapes.emplace_back(std::make_unique<Line>(line));
}

void GraphicsContext::Draw(const Rectangle &rectangle) {
	_shapes.emplace_back(std::make_unique<Rectangle>(rectangle));
}

void GraphicsContext::Draw(const Circle &circle) {
	_shapes.emplace_back(std::make_unique<Circle>(circle));
}

void GraphicsContext::Translate(const t_Point2D &offset) {
	std::ranges::for_each(_shapes, [&offset] (auto &shape) {
		shape->Translate(offset);
	});
}

void GraphicsContext::Rotate(const t_Point2D &center, t_Precision deg) {
	std::ranges::for_each(_shapes, [&center, deg] (auto &shape) {
		shape->Rotate(center, deg);
	});
}

void GraphicsContext::Scale(const t_Point2D &center, t_Precision factor) {
	std::ranges::for_each(_shapes, [&center, factor] (auto &shape) {
		shape->Scale(center, factor);
	});
}

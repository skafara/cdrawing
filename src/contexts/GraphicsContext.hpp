#pragma once

#include <vector>
#include <memory>
#include <functional>
#include <ostream>

#include "../shapes/I_Shape.hpp"
#include "../shapes/Line.hpp"
#include "../shapes/Rectangle.hpp"
#include "../shapes/Circle.hpp"
#include "../util/I_Transformable.hpp"


/**
 * Graphics Context Manager
 */
class GraphicsContext : public I_Transformable {
private:
	const size_t _width;
	const size_t _height;

	std::vector<std::unique_ptr<I_Shape>> _shapes;

public:
	/** GraphicsContext Command Type */
	using t_Cmd = std::function<void (GraphicsContext &)>;

	/**
	 * Transparently constructs
	 * @param width Width
	 * @param height Height
	 */
	GraphicsContext(size_t width, size_t height) : _width(width), _height(height) {};
	/** Transparently destructs */
	virtual ~GraphicsContext() = default;

	/**
	 * Processes drawer commands
	 * @param cmds Commands
	 * @return This
	 */
	GraphicsContext &operator<<(std::vector<t_Cmd> cmds);
	/**
	 * Processes a drawer command
	 * @param cmd Command
	 * @return This
	 */
	GraphicsContext &operator<<(const t_Cmd &cmd);
	/**
	 * Flushes the graphics context into the stream
	 * @param ostream Output stream
	 */
	virtual void operator>>(std::ostream &ostream) const = 0;

	/**
	 * Returns context width
	 * @return Context Width
	 */
	size_t Get_Width() const;
	/**
	 * Returns context height
	 * @return Context Height
	 */
	size_t Get_Height() const;

	/**
	 * Returns the shapes on the graphics context
	 * @return Shapes on the graphics context
	 */
	const std::vector<std::unique_ptr<I_Shape>> &Get_Shapes() const;

	/**
	 * Draws a line on the graphics context
	 * @param line Line
	 */
	void Draw(const Line &line);
	/**
	 * Draws a rectangle on the graphics context
	 * @param rectangle Rectangle
	 */
	void Draw(const Rectangle &rectangle);
	/**
	 * Draws a circle on the graphics context
	 * @param circle Circle
	 */
	void Draw(const Circle &circle);

	void Translate(const t_Point2D &offset) override;
	void Rotate(const t_Point2D &center, t_Precision deg) override;
	void Scale(const t_Point2D &center, t_Precision factor) override;
};

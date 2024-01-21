#pragma once

#include "../contexts/GraphicsContext.hpp"

#include <vector>
#include <map>
#include <istream>
#include <stdexcept>


/**
 * Illegal Command Exception
 */
class IllegalCmdException : public std::runtime_error {
public:
	/**
	 * Transparently constructs
	 * @param msg Message
	 */
	explicit IllegalCmdException(const std::string &msg) : std::runtime_error(msg) {
		//
	}

	/**
	 * Transparently constructs
	 * @param msg Message
	 * @param cmd Command
	 */
	explicit IllegalCmdException(const std::string &msg, const std::string &cmd)
		: IllegalCmdException(msg + ": \"" + cmd + "\"") {
		//
	}
};

/**
 * Parser of drawer commands
 */
class CmdsParser {
public:
	/**
	 * Parses drawer command from input stream
	 * @param istream Input stream
	 * @return GraphicsContext commands
	 */
	static std::vector<GraphicsContext::t_Cmd> Parse(std::istream &istream);

private:
	static IllegalCmdException Get_Illegal_Cmd_Args_Exception();

	using t_Parser = std::function<GraphicsContext::t_Cmd (std::istream &)>;
	static const std::map<std::string, t_Parser> kParsers;

	static constexpr char kDelimiter_Args = ' ';
	static const std::string kComment;

	static const std::string kWhitespaces;
	static std::string Strip_Whitespaces(const std::string &str);

	static GraphicsContext::t_Cmd Parse_Line(std::istream &args);
	static GraphicsContext::t_Cmd Parse_Rectangle(std::istream &args);
	static GraphicsContext::t_Cmd Parse_Circle(std::istream &args);

	static GraphicsContext::t_Cmd Parse_Translate(std::istream &args);
	static GraphicsContext::t_Cmd Parse_Rotate(std::istream &args);
	static GraphicsContext::t_Cmd Parse_Scale(std::istream &args);

};

#include "CmdsParser.hpp"

#include <sstream>


IllegalCmdException CmdsParser::Get_Illegal_Cmd_Args_Exception() {
	return IllegalCmdException{"Illegal Command Arguments"};
}

const std::map<std::string, CmdsParser::t_Parser> CmdsParser::kParsers{
		{"line", &CmdsParser::Parse_Line},
		{"rect", &CmdsParser::Parse_Rectangle},
		{"circle", &CmdsParser::Parse_Circle},
		{"translate", &CmdsParser::Parse_Translate},
		{"rotate", &CmdsParser::Parse_Rotate},
		{"scale", &CmdsParser::Parse_Scale}
};

const std::string CmdsParser::kComment{"#"};

const std::string CmdsParser::kWhitespaces{" \t\f\v"};

std::string CmdsParser::Strip_Whitespaces(const std::string &str) {
	const size_t begin = str.find_first_not_of(kWhitespaces);
	if (begin == 0 || begin == std::string::npos) {
		return str;
	}

	return str.substr(begin);
}

std::vector<GraphicsContext::t_Cmd> CmdsParser::Parse(std::istream &istream) {
	std::vector<GraphicsContext::t_Cmd> cmds;
	for (std::string line; std::getline(istream, line); ) {
		line = Strip_Whitespaces(line);
		if (line.empty()) {
			break;
		}

		std::istringstream isstream{line};

		std::string cmd;
		std::getline(isstream, cmd, kDelimiter_Args); // get cmd name
		if (cmd == kComment) {
			continue;
		}
		if (!kParsers.contains(cmd)) {
			throw IllegalCmdException{"Illegal Command Name", line};
		}

		try {
			const t_Parser Parser = kParsers.at(cmd);
			const GraphicsContext::t_Cmd drawer_cmd = Parser(isstream);
			cmds.push_back(drawer_cmd);
		}
		catch (const IllegalCmdException &e) {
			throw IllegalCmdException{"Invalid Command", line};
		}
	}

	return cmds;
}

GraphicsContext::t_Cmd CmdsParser::Parse_Line(std::istream &args) {
	t_Precision x1, y1, x2, y2;
	if (!(args >> x1 >> y1 >> x2 >> y2)) {
		throw Get_Illegal_Cmd_Args_Exception();
	}

	const t_Point2D begin{x1, y1};
	const t_Point2D end{x2, y2};
	if (begin == end) {
		throw Get_Illegal_Cmd_Args_Exception();
	}

	const Line line{begin, end};
	return [line] (GraphicsContext &drawer) {
		drawer.Draw(line);
	};
}

GraphicsContext::t_Cmd CmdsParser::Parse_Rectangle(std::istream &args) {
	t_Precision x, y, width, height;
	if (!(args >> x >> y >> width >> height)) {
		throw Get_Illegal_Cmd_Args_Exception();
	}

	if (width <= 0 || height <= 0) {
		throw Get_Illegal_Cmd_Args_Exception();
	}

	const t_Point2D top_left{x, y};
	const Rectangle rectangle{top_left, width, height};
	return [rectangle] (GraphicsContext &drawer) {
		drawer.Draw(rectangle);
	};
}

GraphicsContext::t_Cmd CmdsParser::Parse_Circle(std::istream &args) {
	t_Precision x, y, radius;
	if (!(args >> x >> y >> radius)) {
		throw Get_Illegal_Cmd_Args_Exception();
	}

	if (radius <= 0) {
		throw Get_Illegal_Cmd_Args_Exception();
	}

	const t_Point2D center{x, y};
	const Circle circle{center, radius};
	return [circle] (GraphicsContext &drawer) {
		drawer.Draw(circle);
	};
}

GraphicsContext::t_Cmd CmdsParser::Parse_Translate(std::istream &args) {
	t_Precision x, y;
	if (!(args >> x >> y)) {
		throw Get_Illegal_Cmd_Args_Exception();
	}

	const t_Point2D offset{x, y};
	return [offset] (GraphicsContext &drawer) {
		drawer.Translate(offset);
	};
}

GraphicsContext::t_Cmd CmdsParser::Parse_Rotate(std::istream &args) {
	t_Precision x, y, deg;
	if (!(args >> x >> y >> deg)) {
		throw Get_Illegal_Cmd_Args_Exception();
	}

	const t_Point2D center{x, y};
	return [center, deg] (GraphicsContext &drawer) {
		drawer.Rotate(center, deg);
	};
}

GraphicsContext::t_Cmd CmdsParser::Parse_Scale(std::istream &args) {
	t_Precision x, y, factor;
	if (!(args >> x >> y >> factor)) {
		throw Get_Illegal_Cmd_Args_Exception();
	}

	const t_Point2D center{x, y};
	return [center, factor] (GraphicsContext &drawer) {
		drawer.Scale(center, factor);
	};
}

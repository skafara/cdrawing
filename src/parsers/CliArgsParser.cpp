#include "CliArgsParser.hpp"

#include <sstream>


const std::string CliArgsParser::kExtension_Svg{".svg"};
const std::string CliArgsParser::kExtension_Pgm{".pgm"};

CliArgsParser::Result::Result(CliArgsParser::Result::DrawerType drawer_type, const std::string &in_file, const std::string &out_file, size_t width, size_t height)
	: drawer_type(drawer_type), in_file(in_file), out_file(out_file), width(width), height(height)
{
	//
}

CliArgsParser::Result CliArgsParser::Parse(int argc, char **argv) {
	if (argc != kExpected_Argc) {
		throw std::invalid_argument{"Invalid Arguments Count"};
	}

	const Result::DrawerType drawer_type = Parse_Drawer_Type(argv[2]);
	const std::pair<size_t, size_t> dimensions = Parse_Dimensions(argv[3]);

	return {drawer_type, argv[1], argv[2], dimensions.first, dimensions.second};
}

CliArgsParser::Result::DrawerType CliArgsParser::Parse_Drawer_Type(const std::string &out_file) {
	if (out_file.ends_with(kExtension_Svg)) {
		return CliArgsParser::Result::DrawerType::kSvg;
	}
	else if (out_file.ends_with(kExtension_Pgm)) {
		return CliArgsParser::Result::DrawerType::kPgm;
	}
	else {
		throw std::invalid_argument{"Invalid Output File Format"};
	}
}

std::pair<size_t, size_t> CliArgsParser::Parse_Dimensions(const char *dimensions) {
	std::istringstream isstream{dimensions};

	long long width, height;
	char delimiter;
	isstream >> width >> delimiter >> height;

	if (!isstream || delimiter != kDelimiter_Dimensions) {
		throw std::invalid_argument{"Invalid Dimensions Format"};
	}
	if (width <= 0 || height <= 0) {
		throw std::invalid_argument{"Invalid Dimensions"};
	}

	return {width, height};
}

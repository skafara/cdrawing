#pragma once

#include <string>


/**
 * CLI arguments parser
 */
class CliArgsParser {
public:
	/** Parse Result */
	class Result {
	public:
		/** GraphicsContext Instance Type */
		enum class DrawerType {
			kSvg,
			kPgm
		};

		/**
		 * Transparently constructs
		 * @param drawer_type GraphicsContext Instance Type
		 * @param in_file Input File
		 * @param out_file Output File
		 * @param width Context Width
		 * @param height Context Height
		 */
		Result(DrawerType drawer_type, const std::string &in_file, const std::string &out_file, size_t width, size_t height);

		/** GraphicsContext Instance Type */
		const DrawerType drawer_type;
		/** Input File */
		const std::string in_file;
		/** Output File */
		const std::string out_file;
		/** Context Width */
		const size_t width;
		/** Context Height */
		const size_t height;

	};

	/**
	 * Parses CLI arguments
	 * @param argc argc
	 * @param argv argv
	 * @return Parse Result
	 */
	static Result Parse(int argc, char **argv);

private:
	static constexpr size_t kExpected_Argc = 4;

	static const std::string kExtension_Svg;
	static const std::string kExtension_Pgm;
	static constexpr char kDelimiter_Dimensions = 'x';

	static Result::DrawerType Parse_Drawer_Type(const std::string &out_file);
	static std::pair<size_t, size_t> Parse_Dimensions(const char *dimensions);

};

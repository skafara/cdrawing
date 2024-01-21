#include "contexts/SvgContext.hpp"
#include "contexts/PgmContext.hpp"
#include "parsers/CliArgsParser.hpp"
#include "parsers/CmdsParser.hpp"
#include "util/exceptions.hpp"

#include <iostream>
#include <fstream>


void Print_Help() {
	std::cout << "Usage:" << std::endl;
	std::cout << "\tcdrawing <in-file> <out-file> <dimensions>" << std::endl << std::endl;
	std::cout << "\t<in-file>\t- Input file with drawing commands" << std::endl;
	std::cout << "\t<out-file>\t- Output file (<filename>.[svg|pgm])" << std::endl;
	std::cout << "\t<dimensions>\t- Context dimensions (<width>x<height>)" << std::endl;
}

void Print_Error(const std::string &text) {
	std::cerr << "[ERROR] " << text << std::endl;
}

int main(int argc, char **argv) {
	try {
		const CliArgsParser::Result args = CliArgsParser::Parse(argc, argv);

		std::ifstream ifstream{args.in_file};
		if (!ifstream.is_open()) {
			throw IOException("Cannot Open Input File");
		}
		const std::vector<GraphicsContext::t_Cmd> cmds = CmdsParser::Parse(ifstream);
		if (ifstream.bad()) {
			throw IOException("Cannot Read From Input File");
		}

		std::unique_ptr<GraphicsContext> context;
		if (args.drawer_type == CliArgsParser::Result::DrawerType::kSvg) {
			context = std::make_unique<SvgContext>(args.width, args.height);
		} else {
			context = std::make_unique<PgmContext>(args.width, args.height);
		}
		(*context) << cmds;

		std::ofstream ofstream{args.out_file};
		if (!ofstream.is_open()) {
			throw IOException("Cannot Open Output File");
		}

		(*context) >> ofstream;
		if (ofstream.bad()) {
			throw IOException("Cannot Write To Output File");
		}

		std::cout << "OK" << std::endl;
		std::cout << cmds.size() << std::endl;
	}
	catch (const std::invalid_argument &e) {
		Print_Error(e.what());
		Print_Help();
		return EXIT_FAILURE;
	}
	catch (const std::exception &e) {
		Print_Error(e.what());
		return EXIT_FAILURE;
	}

    return EXIT_SUCCESS;
}

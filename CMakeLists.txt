cmake_minimum_required(VERSION 3.0)
project(cdrawing)

set(CMAKE_CXX_STANDARD 20)

add_executable(cdrawing
        main.cpp

        parsers/CliArgsParser.cpp
        parsers/CmdsParser.cpp

        contexts/GraphicsContext.cpp
        contexts/SvgContext.cpp
        contexts/PgmContext.cpp
        contexts/Raster.cpp

        shapes/I_Shape.cpp
        shapes/Line.cpp
        shapes/Rectangle.cpp
        shapes/Circle.cpp
        shapes/Transformer.cpp
)

#Die ist definitiv noch noch nicht fertig:D Ich hab die jetzt nur so grundlegend eingerichtet, dass es möglich ist die Klassen zu testen

cmake_minimum_required(VERSION 3.20)

project(fmt-simulator LANGUAGES CXX)

# see https://cmake.org/cmake/help/latest/module/FindBoost.html
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
include_directories(components/include)
add_executable(test components/src/test.cpp components/src/component.cpp components/src/detector.cpp photon/include/photon.hpp photon/src/photon.cpp utils/src/utils.cpp utils/include/utils.hpp components/src/rgb.cpp components/include/rgb.hpp components/src/bmprgb.cpp components/include/bmprgb.hpp components/src/bmpFileHeader.cpp components/include/bmpFileHeader.hpp components/src/bmpInfoHeader.cpp components/include/bmpInfoHeader.hpp)
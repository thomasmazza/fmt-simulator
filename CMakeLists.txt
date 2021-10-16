#Die ist definitiv noch noch nicht fertig:D Ich hab die jetzt nur so grundlegend eingerichtet, dass es möglich ist die Klassen zu testen
cmake_minimum_required(VERSION 3.20)

project(fmt-simulator LANGUAGES CXX)

# see https://cmake.org/cmake/help/latest/module/FindBoost.html
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
include_directories(components/include utils/include photon/include)
add_executable(test components/src/test.cpp components/src/component.cpp components/src/filter.cpp components/src/mirrorRectangle.cpp components/src/mirror.cpp components/src/mirrorElliptical.cpp components/src/mirrorSquare.cpp  utils/src/utils.cpp photon/src/photon.cpp components/src/lens.cpp components/src/lensOneSided.cpp components/src/lensTwoSided.cpp components/src/bmpFileHeader.cpp components/src/bmpInfoHeader.cpp components/src/bmprgb.cpp components/src/detector.cpp components/src/rgb.cpp)
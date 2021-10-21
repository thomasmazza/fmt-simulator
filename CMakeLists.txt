#Die ist definitiv noch noch nicht fertig:D Ich hab die jetzt nur so grundlegend eingerichtet, dass es möglich ist die Klassen zu testen
cmake_minimum_required(VERSION 3.20)

project(fmt-simulator LANGUAGES CXX)

# see https://cmake.org/cmake/help/latest/module/FindBoost.html
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
include_directories(components/include utils/include photon/include)
add_executable(test
        utils/src/utils.cpp
        utils/src/objectPoint.cpp
        components/src/component.cpp
        utils/src/utils.cpp photon/src/photon.cpp
        photon/src/photon.cpp
        utils/include/operators.hpp
        utils/src/operators.cpp
        utils/src/bmpFileHeader.cpp
        utils/src/bmpInfoHeader.cpp
        utils/src/bmprgb.cpp
        components/src/detector.cpp
        utils/src/rgb.cpp
        components/src/test.cpp
        )
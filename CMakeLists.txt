#Die ist definitiv noch noch nicht fertig:D Ich hab die jetzt nur so grundlegend eingerichtet, dass es möglich ist die Klassen zu testen
cmake_minimum_required(VERSION 3.20)

project(fmt-simulator LANGUAGES CXX)

# see https://cmake.org/cmake/help/latest/module/FindBoost.html
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
include_directories(components/include utils/include photon/include logic/include)
add_executable(test
        logic/src/test.cpp
        utils/src/utils.cpp
        utils/src/objectPoint.cpp
        components/src/component.cpp
        components/src/filter.cpp
        components/src/mirrorRectangle.cpp
        components/src/mirror.cpp
        components/src/mirrorElliptical.cpp
        components/src/mirrorSquare.cpp
        components/src/mirrorCircle.cpp
        components/src/lensTwoSided.cpp
        components/src/lensOneSided.cpp
        components/src/lens.cpp
        photon/src/photonGenerator.cpp
        photon/src/photon.cpp
        logic/src/setupImporter.cpp
        logic/src/setupList.cpp
        logic/include/setupExporter.hpp
        logic/src/setupExporter.cpp
        )


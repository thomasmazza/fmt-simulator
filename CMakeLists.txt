#Die ist definitiv noch noch nicht fertig:D Ich hab die jetzt nur so grundlegend eingerichtet, dass es möglich ist die Klassen zu testen
cmake_minimum_required(VERSION 3.20)

project(fmt-simulator LANGUAGES CXX)


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
        utils/src/utils.cpp photon/src/photon.cpp
        components/src/lens.cpp
        components/src/lensOneSided.cpp
        components/src/lensTwoSided.cpp
        photon/src/photonGenerator.cpp
        photon/src/photon.cpp
        logic/src/importer.cpp
        logic/src/setupList.cpp
        logic/include/exporter.hpp
        logic/src/exporter.cpp
        logic/src/objectGenerator.cpp
        utils/include/operators.hpp
        utils/src/operators.cpp
        utils/src/bmpFileHeader.cpp
        utils/src/bmpInfoHeader.cpp
        utils/src/bmprgb.cpp
        components/src/detector.cpp
        utils/src/rgb.cpp
        logic/include/simulation.hpp logic/src/simulation.cpp)
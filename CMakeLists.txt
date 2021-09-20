#Die ist definitiv noch noch nicht fertig:D Ich hab die jetzt nur so grundlegend eingerichtet, dass es möglich ist die Klassen zu testen
cmake_minimum_required(VERSION 3.20)

project(fmt-simulator LANGUAGES CXX)

# see https://cmake.org/cmake/help/latest/module/FindBoost.html
find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIR})
include_directories(components/include)
add_executable(test components/src/test.cpp components/src/component.cpp components/src/filter.cpp components/src/mirror.cpp components/src/ellipticalMirror.cpp components/src/circleMirror.cpp components/src/rectangleMirror.cpp components/src/SquareMirror.cpp)
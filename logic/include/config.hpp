#pragma once

#include <string>
#include "objectPoint.hpp"

namespace Config {
    typedef typename std::vector<objectPoint> objectRow;
    typedef typename std::vector<objectRow> object;
    const std::string FILTER_OPENING_TAG = "Filter";
    const std::string FILTER_CLOSING_TAG = "/Filter";
    const std::string LENS_ONE_SIDED_OPENING_TAG = "LensOneSided";
    const std::string LENS_ONE_SIDED_CLOSING_TAG = "/LensOneSided";
    const std::string LENS_TWO_SIDED_OPENING_TAG = "LensTwoSided";
    const std::string LENS_TWO_SIDED_CLOSING_TAG = "/LensTwoSided";
    const std::string MIRROR_ELLIPTICAL_OPENING_TAG = "MirrorElliptical";
    const std::string MIRROR_ELLIPTICAL_CLOSING_TAG = "/MirrorElliptical";
    const std::string MIRROR_CIRCLE_OPENING_TAG = "MirrorCircle";
    const std::string MIRROR_CIRCLE_CLOSING_TAG = "/MirrorCircle";
    const std::string MIRROR_RECTANGLE_OPENING_TAG = "MirrorRectangle";
    const std::string MIRROR_RECTANGLE_CLOSING_TAG = "/MirrorRectangle";
    const std::string MIRROR_SQUARE_OPENING_TAG = "MirrorSquare";
    const std::string MIRROR_SQUARE_CLOSING_TAG = "/MirrorSquare";
    const std::string DETECTOR_OPENING_TAG = "Detector";
    const std::string DETECTOR_CLOSING_TAG = "/Detector";
    const std::string APERTURE_OPENING_TAG = "Aperture";
    const std::string APERTURE_CLOSING_TAG = "/Aperture";
    const std::string SETUP_OPENING_TAG = "Setup";
    const std::string SETUP_CLOSING_TAG = "/Setup";
    const std::string POSITION_OPENING_TAG = "Position";
    const std::string POSITION_CLOSING_TAG = "/Position";
    const std::string NORMAL_OPENING_TAG = "Normal";
    const std::string NORMAL_CLOSING_TAG = "/Normal";
    const std::string LOWER_LIMIT_OPENING_TAG = "LowerLimit";
    const std::string LOWER_LIMIT_CLOSING_TAG = "/LowerLimit";
    const std::string UPPER_LIMIT_OPENING_TAG = "UpperLimit";
    const std::string UPPER_LIMIT_CLOSING_TAG = "/UpperLimit";
    const std::string N_OPENING_TAG = "N";
    const std::string N_CLOSING_TAG = "/N";
    const std::string RADIUS_H_OPENING_TAG = "RadiusH";
    const std::string RADIUS_H_CLOSING_TAG = "/RadiusH";
    const std::string RADIUS_W_OPENING_TAG = "RadiusW";
    const std::string RADIUS_W_CLOSING_TAG = "/RadiusW";
    const std::string RADIUS_I_OPENING_TAG = "RadiusI";
    const std::string RADIUS_I_CLOSING_TAG = "/RadiusI";
    const std::string RADIUS_O_OPENING_TAG = "RadiusO";
    const std::string RADIUS_O_CLOSING_TAG = "/RadiusO";
    const std::string RADIUS_OPENING_TAG = "Radius";
    const std::string RADIUS_CLOSING_TAG = "/Radius";
    const std::string LENGTH_H_OPENING_TAG = "LengthH";
    const std::string LENGTH_H_CLOSING_TAG = "/LengthH";
    const std::string LENGTH_W_OPENING_TAG = "LengthW";
    const std::string LENGTH_W_CLOSING_TAG = "/LengthW";
    const std::string LENGTH_OPENING_TAG = "Length";
    const std::string LENGTH_CLOSING_TAG = "/Length";
    const std::string D_OPENING_TAG = "D";
    const std::string D_CLOSING_TAG = "/D";
    const std::string PLANE_IS_FRONT_OPENING_TAG = "PlaneIsFront";
    const std::string PLANE_IS_FRONT_CLOSING_TAG = "/PlaneIsFront";
    const std::string OBJECT_OPENING_TAG = "Object";
    const std::string OBJECT_CLOSING_TAG = "/Object";
    const std::string POINT_OPENING_TAG = "Point";
    const std::string POINT_CLOSING_TAG = "/Point";
    const std::string WAVELENGTH_OPENING_TAG = "Wavelength";
    const std::string WAVELENGTH_CLOSING_TAG = "/Wavelength";
    const std::string OBJECT_ROW_OPENING_TAG = "ObjectRow";
    const std::string OBJECT_ROW_CLOSING_TAG = "/ObjectRow";
    const std::string POINT_ON_EDGE_OPENING_TAG = "PointOnEdge";
    const std::string POINT_ON_EDGE_CLOSING_TAG = "/PointOnEdge";
    const std::string POSITION_OF_PREVIOUS_COMPONENT_OPENING_TAG = "PosOfPrevComponent";
    const std::string POSITION_OF_PREVIOUS_COMPONENT_CLOSING_TAG = "/PosOfPrevComponent";
    const std::string SIZE_OPENING_TAG = "Size";
    const std::string SIZE_CLOSING_TAG = "/Size";
    const std::string PIXEL_SIZE_OPENING_TAG = "PixelSize";
    const std::string PIXEL_SIZE_CLOSING_TAG = "/PixelSize";
}
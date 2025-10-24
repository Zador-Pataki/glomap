#pragma once

#include "glomap/scene/camera.h"
#include "glomap/scene/image.h"
#include "glomap/scene/image_pair.h"
// #include "glomap/scene/point2d.h"
// #include "glomap/scene/point3d.h"
#include "glomap/scene/types_sfm.h"
// #include "glomap/scene/types.h"

#include <pybind11/eigen.h>
#include <pybind11/pybind11.h>

using namespace glomap;
namespace py = pybind11;

// py::module pycolmap = py::module::import("pycolmap");

// using Point2DVector = std::vector<struct Point2D>;
// PYBIND11_MAKE_OPAQUE(Point2DVector);

using ImageMap = std::unordered_map<image_t, Image>;
using TrackMap = std::unordered_map<track_t, Track>;
using ImagePairMap = std::unordered_map<image_pair_t, ImagePair>;

using CameraMap = std::unordered_map<camera_t, glomap::Camera>;

// using Point3DMap = std::unordered_map<point3D_t, Point3D>;
// PYBIND11_MAKE_OPAQUE(Point3DMap);

#include "glomap/controllers/track_retriangulation.h"

#include "pyglomap/pybind11_extension.h"
#include "pyglomap/scene/colmap_bindings.h"

#include <colmap/scene/database.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>

using namespace glomap;
using namespace pybind11::literals;
namespace py = pybind11;

py::dict RunRetriangulateTracks(
    std::unordered_map<camera_t, Camera>& cameras,
    std::unordered_map<image_t, Image>& images,
    std::unordered_map<track_t, Track>& tracks,
    const colmap::Database& database,
    const TriangulatorOptions& options) {
  RetriangulateTracks(options, database, cameras, images, tracks);

  py::dict output;
  output["cameras"] = cameras;
  output["images"] = images;
  output["tracks"] = tracks;

  return output;
}

void BindTrackRetriangulation(py::module& m) {
  m.def("run_track_retriangulation",
        &RunRetriangulateTracks,
        "cameras"_a,
        "images"_a,
        "tracks"_a,
        "database"_a,
        py::arg_v("options", TriangulatorOptions(), "TriangulatorOptions()"),
        "Run track retriangulation");
}

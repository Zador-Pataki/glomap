#include "glomap/io/colmap_io.h"
#include "glomap/scene/types_sfm.h"
#include "glomap/scene/view_graph.h"

#include <colmap/scene/database.h>

#include <memory>
#include <tuple>
#include <unordered_map>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "pyglomap/pybind11_extension.h"
#include "pyglomap/scene/colmap_bindings.h"  // ensures pycolmap types are registered
#include "pyglomap/scene/types.h"            // ensures glomap bindings (Image, ViewGraph) exist

namespace py = pybind11;
using namespace glomap;
using py_int = py::int_;

namespace {

// Helper: convert the C++ maps to Python dicts with pycolmap.Camera
static std::tuple<py::dict, py::dict>
ToPythonDicts(const std::unordered_map<camera_t, glomap::Camera>& cameras_glo,
              const std::unordered_map<image_t,  glomap::Image>&  images_glo) {
  // Ensure pycolmap module is loaded so colmap::Camera caster is registered
  static bool imported = [](){
    py::module_::import("pycolmap._core");
    return true;
  }();
  (void)imported;

  py::dict py_cams;
  for (const auto& [cid, cam] : cameras_glo) {
    // If glomap::Camera is actually colmap::Camera internally, this just works.
    // If it’s a different struct, map its fields into a colmap::Camera here.
    const colmap::Camera cam_colmap(cam);   // or build & assign fields explicitly
    py_cams[py_int(cid)] = py::cast(cam_colmap);
  }

  py::dict py_imgs;
  for (const auto& [iid, img] : images_glo) {
    py_imgs[py_int(iid)] = py::cast(img);   // Image is bound in pyglomap
  }

  return {py_cams, py_imgs};
}

} // namespace

// Wrapper: load from database and return (ViewGraph, dict[int, pycolmap.Camera], dict[int, Image])
static std::tuple<std::shared_ptr<ViewGraph>, py::dict, py::dict>
ConvertDatabaseToGlomapWrapper(const colmap::Database& database)
{
  auto view_graph_ptr = std::make_shared<ViewGraph>();
  std::unordered_map<camera_t, glomap::Camera> cameras_glo;
  std::unordered_map<image_t,  glomap::Image>  images_glo;

  // If you want to release the GIL during heavy DB I/O:
  // { py::gil_scoped_release release; glomap::ConvertDatabaseToGlomap(database, *view_graph_ptr, cameras_glo, images_glo); }
  glomap::ConvertDatabaseToGlomap(database, *view_graph_ptr, cameras_glo, images_glo);

  auto [py_cams, py_imgs] = ToPythonDicts(cameras_glo, images_glo);
  return std::make_tuple(view_graph_ptr, std::move(py_cams), std::move(py_imgs));
}

void BindDatabaseConverter(py::module_& m) {
  m.def(
      "convert_database_to_glomap",
      &ConvertDatabaseToGlomapWrapper,
      py::arg("database"),
      R"doc(
Reads data from a COLMAP Database and converts it into GLOMAP objects.

Args:
    database (pycolmap.Database): The input COLMAP database (already opened).

Returns:
    tuple[ViewGraph, dict[int, pycolmap.Camera], dict[int, Image]]:
        (view_graph, cameras, images)
)doc");
}
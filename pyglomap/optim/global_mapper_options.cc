#include "glomap/controllers/global_mapper.h"

#include <memory>
#include <sstream>

#include "pyglomap/helpers.h"
#include "pyglomap/pybind11_extension.h"
#include <pybind11/eigen.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>

using namespace glomap;
using namespace pybind11::literals;
namespace py = pybind11;

void BindGlobalMapperOptions(py::module& m) {
  py::class_<GlobalMapperOptions, std::shared_ptr<GlobalMapperOptions>>
      PyGlobalMapperOptions(m, "GlobalMapperOptions");

  PyGlobalMapperOptions.def(py::init<>())
      .def_readwrite("opt_vgcalib", &GlobalMapperOptions::opt_vgcalib)
    //   .def_readwrite("opt_relpose", &GlobalMapperOptions::opt_relpose)
      .def_readwrite("opt_ra", &GlobalMapperOptions::opt_ra)
      .def_readwrite("opt_track", &GlobalMapperOptions::opt_track)
      .def_readwrite("opt_gp", &GlobalMapperOptions::opt_gp)
      .def_readwrite("opt_ba", &GlobalMapperOptions::opt_ba)
      .def_readwrite("opt_triangulator", &GlobalMapperOptions::opt_triangulator)
      .def_readwrite("inlier_thresholds", &GlobalMapperOptions::inlier_thresholds)
      .def_readwrite("num_iteration_bundle_adjustment",
                     &GlobalMapperOptions::num_iteration_bundle_adjustment)
      .def_readwrite("num_iteration_retriangulation",
                     &GlobalMapperOptions::num_iteration_retriangulation)
      .def_readwrite("skip_preprocessing", &GlobalMapperOptions::skip_preprocessing)
      .def_readwrite("skip_view_graph_calibration",
                     &GlobalMapperOptions::skip_view_graph_calibration)
      .def_readwrite("skip_relative_pose_estimation",
                     &GlobalMapperOptions::skip_relative_pose_estimation)
      .def_readwrite("skip_rotation_averaging",
                     &GlobalMapperOptions::skip_rotation_averaging)
      .def_readwrite("skip_track_establishment",
                     &GlobalMapperOptions::skip_track_establishment)
      .def_readwrite("skip_global_positioning",
                     &GlobalMapperOptions::skip_global_positioning)
      .def_readwrite("skip_bundle_adjustment",
                     &GlobalMapperOptions::skip_bundle_adjustment)
      .def_readwrite("skip_retriangulation",
                     &GlobalMapperOptions::skip_retriangulation)
      .def_readwrite("skip_pruning", &GlobalMapperOptions::skip_pruning)
      .def("__repr__", [](const GlobalMapperOptions& self) {
        std::stringstream ss;
        ss << "GlobalMapperOptions(" << std::endl
           << "  opt_vgcalib="
           << "<ViewGraphCalibratorOptions object>"
           << "," << std::endl
           // << "  opt_relpose=" << self.opt_relpose << "," << std::endl
           << "  opt_ra="
           << "<RotationAveragingOptions object>"
           << "," << std::endl
           << "  opt_track="
           << "<TrackEstablishmentOptions object>"
           << "," << std::endl
           << "  opt_gp="
           << "<GlobalPositioningOptions object>"
           << "," << std::endl
           << "  opt_ba="
           << "<BundleAdjustmentOptions object>"
           << "," << std::endl
           << "  opt_triangulator="
           << "<TriangulatorOptions object>"
           << "," << std::endl
           << "  inlier_thresholds="
           << "<InlierThresholdOptions object>"
           << "," << std::endl
           << "  num_iteration_bundle_adjustment="
           << self.num_iteration_bundle_adjustment << "," << std::endl
           << "  num_iteration_retriangulation="
           << self.num_iteration_retriangulation << "," << std::endl
           << "  skip_preprocessing=" << self.skip_preprocessing << ","
           << std::endl
           << "  skip_view_graph_calibration=" << self.skip_view_graph_calibration
           << "," << std::endl
           << "  skip_relative_pose_estimation="
           << self.skip_relative_pose_estimation << "," << std::endl
           << "  skip_rotation_averaging=" << self.skip_rotation_averaging << ","
           << std::endl
           << "  skip_track_establishment=" << self.skip_track_establishment
           << "," << std::endl
           << "  skip_global_positioning=" << self.skip_global_positioning << ","
           << std::endl
           << "  skip_bundle_adjustment=" << self.skip_bundle_adjustment << ","
           << std::endl
           << "  skip_retriangulation=" << self.skip_retriangulation << ","
           << std::endl
           << "  skip_pruning=" << self.skip_pruning << std::endl
           << ")";
        return ss.str();
      });

  MakeDataclass(PyGlobalMapperOptions);
}

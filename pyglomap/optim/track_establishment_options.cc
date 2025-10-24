
#include "glomap/controllers/track_establishment.h"

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

void BindTrackEstablishmentOptions(py::module& m) {
  // Bind TrackEstablishmentOptions
  py::class_<TrackEstablishmentOptions,
             std::shared_ptr<TrackEstablishmentOptions>>
      PyTrackEstablishmentOptions(m, "TrackEstablishmentOptions");

  PyTrackEstablishmentOptions.def(py::init<>())
      .def_readwrite("thres_inconsistency",
                     &TrackEstablishmentOptions::thres_inconsistency,
                     "The max allowed distance for features in the same track "
                     "in the same image.")
      .def_readwrite("min_num_tracks_per_view",
                     &TrackEstablishmentOptions::min_num_tracks_per_view,
                     "The minimal number of tracks for each view.")
      .def_readwrite("min_num_view_per_track",
                     &TrackEstablishmentOptions::min_num_view_per_track,
                     "The minimal number of tracks for each view pair.")
      .def_readwrite("max_num_view_per_track",
                     &TrackEstablishmentOptions::max_num_view_per_track,
                     "The maximal number of tracks for each view pair.")
      .def_readwrite("max_num_tracks",
                     &TrackEstablishmentOptions::max_num_tracks,
                     "The maximal number of tracks.")
      .def("__repr__", [](const TrackEstablishmentOptions& self) {
        std::stringstream ss;
        ss << "TrackEstablishmentOptions(" << std::endl
           << "  thres_inconsistency=" << self.thres_inconsistency << ","
           << std::endl
           << "  min_num_tracks_per_view=" << self.min_num_tracks_per_view
           << "," << std::endl
           << "  min_num_view_per_track=" << self.min_num_view_per_track << ","
           << std::endl
           << "  max_num_view_per_track=" << self.max_num_view_per_track << ","
           << std::endl
           << "  max_num_tracks=" << self.max_num_tracks << std::endl
           << ")";
        return ss.str();
      });

  MakeDataclass(PyTrackEstablishmentOptions);
}

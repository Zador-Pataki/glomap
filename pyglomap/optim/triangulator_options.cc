#include "glomap/controllers/track_retriangulation.h"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <sstream>

#include "pyglomap/helpers.h"

namespace py = pybind11;

using namespace glomap;

void BindTriangulatorOptions(py::module& m) {
  py::class_<TriangulatorOptions, std::shared_ptr<TriangulatorOptions>>
      PyTriangulatorOptions(m, "TriangulatorOptions");
  PyTriangulatorOptions.def(py::init<>())
      .def_readwrite("tri_complete_max_reproj_error",
                     &TriangulatorOptions::tri_complete_max_reproj_error)
      .def_readwrite("tri_merge_max_reproj_error",
                     &TriangulatorOptions::tri_merge_max_reproj_error)
      .def_readwrite("tri_min_angle", &TriangulatorOptions::tri_min_angle)
      .def_readwrite("min_num_matches", &TriangulatorOptions::min_num_matches)
      .def("__repr__", [](const TriangulatorOptions& self) {
        std::stringstream ss;
        ss << "TriangulatorOptions(" << std::endl
           << "  tri_complete_max_reproj_error="
           << self.tri_complete_max_reproj_error << "," << std::endl
           << "  tri_merge_max_reproj_error=" << self.tri_merge_max_reproj_error
           << "," << std::endl
           << "  tri_min_angle=" << self.tri_min_angle << "," << std::endl
           << "  min_num_matches=" << self.min_num_matches << std::endl
           << ")";
        return ss.str();
      });

  MakeDataclass(PyTriangulatorOptions);
}

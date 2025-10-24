#include <pybind11/pybind11.h>

namespace py = pybind11;

void BindImageUndistorter(py::module& m);
void BindImagePairInliers(py::module& m);
void BindRelPoseFilter(py::module& m);


void BindProcessors(py::module& m) {
  BindImageUndistorter(m);
  BindImagePairInliers(m);
  BindRelPoseFilter(m);
}
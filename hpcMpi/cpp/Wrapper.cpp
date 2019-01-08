#include <pybind11/functional.h>
#include <pybind11/stl.h>
#include <pybind11/eigen.h>
#include <pybind11/pybind11.h>

namespace Integral {
  double fPi(double x);
  double compute(std::function<double(double)>f, double a, double b, double s);
}

#include "Image.hpp"

PYBIND11_MODULE(hpcMpi, m) {
    // Integral
    m.def("fPi", &Integral::fPi);
    m.def("compute", &Integral::compute);

    // Image
    m.def("readPnm", &Image::readPnm);
    m.def("writePnm", &Image::writePnm);
    m.def("blur", &Image::blur);
}


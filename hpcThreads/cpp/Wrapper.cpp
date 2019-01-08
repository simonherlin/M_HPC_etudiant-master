#include <pybind11/stl.h>
#include <pybind11/pybind11.h>

namespace Hello {
  void hello();
}

namespace Fibo {
  std::vector<int> fiboSequentiel(int nbData);
  std::vector<int> fiboBlocs(int nbData);
  std::vector<int> fiboCyclique2(int nbData);
  std::vector<int> fiboCycliqueN(int nbData, int nbProc);
  void fiboCycliqueNFake(int nbData, int nbProc);
}

PYBIND11_MODULE(hpcThreads, m) {
    m.def("hello", &Hello::hello);

    m.def("fiboSequentiel", &Fibo::fiboSequentiel);
    m.def("fiboBlocs", &Fibo::fiboBlocs);
    m.def("fiboCyclique2", &Fibo::fiboCyclique2);
    m.def("fiboCycliqueN", &Fibo::fiboCycliqueN);
    m.def("fiboCycliqueNFake", &Fibo::fiboCycliqueNFake);
}

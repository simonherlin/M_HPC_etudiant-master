with import <nixpkgs> {};

let 

  _pybind11 = callPackage ../pybind11.nix { 
    inherit stdenv fetchFromGitHub cmake;
    python = python3;
  };

  _pyPkgs = python3Packages;

in 

_pyPkgs.buildPythonPackage {
  name = "hpcMpi";
  src = ./.;
  buildInputs = [ 
    _pybind11 
    _pyPkgs.matplotlib
    _pyPkgs.mpi4py
    _pyPkgs.numpy
    _pyPkgs.pandas
    _pyPkgs.pkgconfig
    _pyPkgs.tkinter
    openmpi
    eigen3_3
  ];
}

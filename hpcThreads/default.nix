with import <nixpkgs> {};

let 

  _pybind11 = callPackage ../pybind11.nix { 
    inherit stdenv fetchFromGitHub cmake;
    python = python3;
  };

  _pyPkgs = python3Packages;

in 

_pyPkgs.buildPythonPackage {
  name = "hpcThreads";
  src = ./.;
  buildInputs = [ 
    _pybind11 
    _pyPkgs.matplotlib
    _pyPkgs.numpy
  ];
}

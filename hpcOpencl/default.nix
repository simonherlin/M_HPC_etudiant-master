with import<nixpkgs> {};

stdenv.mkDerivation {

  name = "hpcOpencl";

  src = ./.;

  buildInputs = [
    opencl-icd
    opencl-clhpp
    opencl-headers
    opencl-info

    opencv3
    gnumake
    gnome3.eog
    pkgconfig
  ];

  enableParallelBuilding = true;

  installPhase = ''
    mkdir -p $out/bin
    mv *.out $out/bin
  '';

}

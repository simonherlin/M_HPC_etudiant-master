with import<nixpkgs> {};

stdenv.mkDerivation {

  name = "hpcMpiCpp";

  src = ./.;

  buildInputs = [
    gnuplot
    gnome3.eog
    openmpi
  ];

  enableParallelBuilding = true;

  installPhase = ''
    mkdir -p $out/bin
    mv *.out $out/bin
  '';
}

with import<nixpkgs> {};

stdenv.mkDerivation {

  name = "hpcOpenmp";

  src = ./.;

  buildInputs = [
    gnome3.eog
    gnumake
  ];

  enableParallelBuilding = true;

  installPhase = ''
    mkdir -p $out/bin
    mv *.out $out/bin
  '';

}

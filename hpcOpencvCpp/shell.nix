with import <nixpkgs> {};

mkShell {
  buildInputs = [
    pkgconfig
    opencv3
  ];
}


let

  _pkgs = import <nixpkgs> { 
    config = {
      packageOverrides = pkgs: {
        opencv3 = pkgs.opencv3.override {
          enableGtk3 = true;
          enableFfmpeg = true;
          enableTIFF = false;
          enableWebP = false;
          enableEXR = false;
          enableJPEG2K = false;
          enableContrib = false;
        };
      };
    };
  };

in 

  (_pkgs.python3.withPackages ( ps: [
    ps.matplotlib
    ps.numpy
    ps.tkinter
    ps.opencv3
  ])).env


let 

  _channel = fetchTarball "https://github.com/NixOS/nixpkgs/archive/18.09.tar.gz";
  #_channel = <nixpkgs>;

  mkPkgs = optCuda: import _channel { 
    config = {
      allowUnfree = optCuda;
      cudaSupport = optCuda;
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

  {

    cpu = (let pkgs = (mkPkgs false); in pkgs.python3.withPackages( ps: [
      ps.h5py
      ps.opencv3
      ps.tensorflow
    ])).env;

    gpu = (let pkgs = (mkPkgs true); in pkgs.python3.withPackages( ps: [
      ps.h5py
      ps.opencv3
      ps.tensorflowWithCuda
      pkgs.cudnn
    ])).env;

  }



let

  config = {
    packageOverrides = pkgs: {

      opencv3 = (pkgs.opencv3.override {
        enableContrib = true;
        enableCuda = false;
        enableEXR = false;
        enableFfmpeg = true;
        enableGtk3 = false;
        enableJPEG2K = false;
        enableTIFF = false;
        enableWebP = false;
      }).overrideDerivation (attrs: {
        doCheck = false;
      });

      haskellPackages = pkgs.haskellPackages.override {
        overrides = haskellPackagesNew: haskellPackagesOld: rec {
          opencv = pkgs.haskell.lib.dontCheck haskellPackagesOld.opencv;
        };
      };

    };
  };

  rev = "18.03";
  channel = fetchTarball "https://github.com/NixOS/nixpkgs/archive/${rev}.tar.gz";
  pkgs = import channel { config = config; };

  drv = pkgs.haskellPackages.callCabal2nix "webcam" ./. {};

in

if pkgs.lib.inNixShell then drv.env else drv



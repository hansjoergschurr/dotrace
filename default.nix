{ pkgs ? import <nixpkgs> {} }:

pkgs.stdenv.mkDerivation {
  name = "dotrace";
  buildInputs = with pkgs; [ python36 binutils ];
}

{
  pkgs ? import <nixpkgs> { },
}:

pkgs.mkShell {
  name = "devenv";

  buildInputs = with pkgs; [
    fmt
    cmake
    clang-tools
    cmake-language-server
    gcc
  ];
}

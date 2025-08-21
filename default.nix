{pkgs ? import <nixpkgs> {}}:
pkgs.callPackage ./buildEditor.nix {}

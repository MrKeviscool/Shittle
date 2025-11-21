# Intro

look, this is a huge work in progress. its only public to show what i have completed so far as its minorly cool.

# Build

### Linux:
you will need to install the development version of GTK3 and of SFML. then you can use the cmake to gen a makefile and run the make.

### NixOS:
Nix is ideal as i have included a build.nix and a default.nix. just run nix-build

### Windows:
Windows is a horrible system to get builds on. firstly you will need a Windows version of GTK3. then you will need a windows version of pkgconf to setup said GTK+ and you will also likely need to compile SFML 2.6 from scratch.

### Mac:
it should build and run on mac but i cant test because apple is scummy... 

# Usage

so far there is just a half working level editor. just run editor in the same folder as the resources.

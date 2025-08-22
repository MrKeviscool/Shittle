{
    stdenv,
    lib,
    cmake,
    pkg-config,
    wrapGAppsHook3,
    sfml_2, 
    gtk3,
    libsysprof-capture,
    pcre2,
    util-linux,
    libselinux,
    libsepol,
    libthai,
    libdatrie,
    xorg,
    lerc,
    libxkbcommon,
    ...
}:

stdenv.mkDerivation {
    pname = "shittle-editor";
    version = "0.0.0";
    # src = (pkgs.nix-gitignore.gitignoreSource[] ./.);
    src = (lib.cleanSource ./.);
    nativeBuildInputs = [ cmake pkg-config wrapGAppsHook3];
    buildInputs = [
        sfml_2 gtk3.dev
        libsysprof-capture pcre2 util-linux libselinux libsepol libthai libdatrie xorg.libXdmcp lerc libxkbcommon
    ];

    installPhase = ''
        mkdir -p $out/resources $out/bin
        cp editor $out/bin/
        cp $src/resources/* $out/resources
    '';
}

{pkgs, stdenv, ...}:

stdenv.mkDerivation {
    pname = "shittle-editor";
    version = "0.0.0";
    src = ./.;
    nativeBuildInputs = with pkgs; [ cmake pkg-config ];
    buildInputs = with pkgs; [sfml_2 gtk3.dev pkg-config libsysprof-capture];
    installPhase = ''
        mkdir -p $out/resources
        cp editor $out/
        cp $src/resources/* $out/resources
    '';
}


        # mkdir -p $out/resources
        # cp -r $src/resources $out/resources

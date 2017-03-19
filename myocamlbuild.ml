open Ocamlbuild_plugin

let () = dispatch begin function
    | After_rules ->

    flag ["use_openbsd_stubs"] &
        S[A"-I"; A"lib"];

    dep ["ocaml"; "link"; "byte"; "library"; "use_openbsd_stubs"]
        ["src/dllopenbsd"-.-(!Options.ext_dll)];

    flag ["ocaml"; "link"; "byte"; "library"; "use_openbsd_stubs"] &
        S[A"-dllib"; A"-lopenbsd_stubs"; A"-cclib"; A"-lpthread"];

    dep ["ocaml"; "link"; "native"; "library"; "use_openbsd_stubs"]
        ["src/libopenbsd"-.-(!Options.ext_lib)];

    flag ["ocaml"; "link"; "native"; "library"; "use_openbsd_stubs"] &
        S[ A"-cclib"; A"-lopenbsd_stubs"; A"-cclib"; A"-lpthread"];

    flag ["link"; "ocaml"; "link_openbsd_stubs"] &
        S[A"-cclib"; A"src/libopenbsd_stubs.a"; A"-cclib"; A"-lpthread"];

    | _ -> ()
end

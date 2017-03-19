#!/usr/bin/env ocaml
#use "topfind"
#require "topkg"

open Topkg

let () =
    Pkg.describe "openbsd" @@ fun c ->
        Ok [
            Pkg.clib "src/libopenbsd_stubs.clib";
            Pkg.mllib ~api:["Openbsd"] "src/openbsd.mllib";
            Pkg.test ~dir:"test" "test/openbsd_test";
        ]

open Openbsd

let _ =
    let _ = Printf.printf "%d\n" (arc4random ()) in
    Printf.printf "%s\n" (newhash "testing")

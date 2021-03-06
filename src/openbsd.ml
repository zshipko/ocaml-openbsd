external arc4random : unit -> int = "openbsd_arc4random"
external arc4random_uniform : int -> int = "openbsd_arc4random_uniform"
external arc4random_buf : string -> unit = "openbsd_arc4random_buf"
external _newhash : string -> string -> int -> string = "openbsd_newhash"
external checkpass : string  -> string -> bool = "openbsd_checkpass"
external pledge : string -> string array -> unit = "openbsd_pledge"

let newhash ?size:(size=64) ?mode:(mode="blowfish,a") str = _newhash str mode size

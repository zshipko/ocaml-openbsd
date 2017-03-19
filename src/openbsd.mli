external arc4random : unit -> int = "openbsd_arc4random"
external arc4random_uniform : int -> int = "openbsd_arc4random_uniform"
external arc4random_buf : string -> unit = "openbsd_arc4random_buf"
external checkpass : string -> string -> bool = "openbsd_checkpass"
external pledge : string -> string array -> unit = "openbsd_pledge"

val newhash : ?size:int -> ?mode:string -> string -> string

#include <unistd.h>
#include <caml/memory.h>
#include <caml/alloc.h>
#include <caml/callback.h>
#include <caml/fail.h>

#include <string.h>
#include <errno.h>

/* arc4random */

value openbsd_arc4random (value unit) {
    CAMLparam1(unit);
    CAMLreturn(Int_val(arc4random ()));
}

value openbsd_arc4random_uniform (value upper_bound) {
    CAMLparam1(upper_bound);
    uint32_t i = Int_val(upper_bound);
    CAMLreturn(Int_val(arc4random_uniform(i)));
}

void openbsd_arc4random_buf (value buffer) {
    CAMLparam1(buffer);
    size_t len = caml_string_length(buffer);
    char *s = String_val(buffer);
    arc4random_buf(s, len);
    CAMLreturn0;
}

/* cryptographic hashing */

value openbsd_newhash(value data, value _size){
    CAMLparam2(data, _size);
    ssize_t size = Int_val(_size);
    if (size < 0 || size % 64 != 0){
        caml_failwith("Invalid size");
        CAMLreturn(Val_unit);
    }

    CAMLlocal1(hash);
    hash = caml_alloc_string(size);
    char *hashstr = String_val(hash);
    const char *datastr = String_val(data);

    if (crypt_newhash(datastr, "blowfish,a", hashstr, size)){
        caml_failwith(strerror(errno));
        CAMLreturn(Val_unit);
    }
    CAMLreturn(hash);
}

value openbsd_checkhash(value data, value hash){
    CAMLparam2(data, hash);
    CAMLreturn(Val_bool (crypt_checkpass(String_val(data), String_val(hash)) == 0));
}


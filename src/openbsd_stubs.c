#include <unistd.h>
#include <caml/memory.h>
#include <caml/alloc.h>
#include <caml/callback.h>
#include <caml/fail.h>

#include <string.h>
#include <errno.h>

/* arc4random */

value openbsd_arc4random (value unit) {
    return caml_copy_int32(arc4random ());
}

value openbsd_arc4random_uniform (value upper_bound) {
    uint32_t i = Int64_val(upper_bound);
    return caml_copy_int32(arc4random_uniform(i));
}

void openbsd_arc4random_buf (value buffer) {
    CAMLparam1(buffer);
    size_t len = caml_string_length(buffer);
    arc4random_buf(String_val(buffer), len);
    CAMLreturn0;
}

/* cryptographic hashing */

value openbsd_newhash(value data, value mode, value _size){
#ifdef __OpenBSD__
    CAMLparam2(data, _size);
    ssize_t size = Int_val(_size);
    if (size < 0 || size % 64 != 0){
        caml_failwith("Invalid size");
        CAMLreturn(Val_unit);
    }

    CAMLlocal1(hash);
    hash = caml_alloc_string(size);
    // Default "blowfish,a"
    if (crypt_newhash(String_val(data), String_val(mode), String_val(hash), size)){
        caml_failwith(strerror(errno));
        CAMLreturn(Val_unit);
    }
    CAMLreturn(hash);
#else
    camlfailwith("OpenBSD required");
    CAMLreturn0;
#endif
}

value openbsd_checkpass(value data, value hash){
#ifdef __OpenBSD__
    CAMLparam2(data, hash);
    CAMLreturn(Val_bool (crypt_checkpass(String_val(data), String_val(hash)) == 0));
#else
    camlfailwith("OpenBSD required");
    CAMLreturn0;
#endif
}

value openbsd_pledge(value s, value a)
{
#ifdef __OpenBSD__
    CAMLparam2(s, a);
    int i, len = Wosize_val(a);
    char *arr[len];
    for(i = 0; i < len; i++){
        arr[i] = String_val(Field(a, i));
    }

    CAMLreturn (Val_int (pledge(String_val(s), (const char**)arr)));
#else
    camlfailwith("OpenBSD required");
    CAMLreturn0;
#endif
}

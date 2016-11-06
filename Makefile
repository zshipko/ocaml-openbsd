all: compile-c
	ocamlmklib -o openbsd openbsd.ml openbsd_stubs.o

compile-c:
	ocamlopt -c -o openbsd_stubs.o openbsd_stubs.c

test:
	ocamlc -custom -o test openbsd.ml openbsd_test.ml openbsd_stubs.c

clean:
	rm -f *.cm* *.o *.a *.so

install:
	$(MAKE) uninstall || :
	ocamlfind install openbsd META openbsd.cma openbsd.cmxa *.so *.a *.cmi *.cmx

uninstall:
	ocamlfind remove openbsd

targets := lib/main.c lib/general.c lib/general.h lib/string.c lib/string.h
location := lib/

out := bin/compile.exe

cc := gcc



compile: $(targets)
	$(cc) $(targets) -o $(out)
	.\$(out) test/cp/Test1.cp
run:
	.\$(out) test/cp/Test1.cp
targets := lib/main.c lib/general.c lib/string.c lib/dfa.c lib/build.c
location := lib/

out := bin/compile.exe

cc := gcc



compile: $(targets)
	$(cc) $(targets) -o $(out)
	.\$(out) test/cp/Test4.cp
run5:
	.\$(out) test/cp/Test5.cp
targets := lib/main.c lib/general.c lib/string.c lib/dfa.c lib/build.c lib/grammar.c
location := lib/

out := bin/compile.exe

cc := gcc



compile: $(targets)
	$(cc) $(targets) -o $(out)
	.\$(out) test/cp/Test3.cp
run5:
	.\$(out) test/cp/Test5.cp
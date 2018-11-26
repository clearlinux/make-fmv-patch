all:
	gcc -O2 -ftree-vectorize loop-test.c -o loop-test -fopt-info-vec &> loop-build.log
	g++ -O2 -ftree-vectorize max-test.cpp -o max-test -fopt-info-vec &> max-build.log
clean:
	@find . -type f -executable -exec sh -c "file -i '{}' | grep -q 'x-executable; charset=binary'" \; -print | xargs rm -f
distclean:
	@rm -rf *.c.patch
	@rm -rf *.cpp.patch
	@rm -rf *build.log

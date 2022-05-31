all:
	gcc -O2 -ftree-vectorize loop-test.c -o loop-test -fopt-info-vec &> loop-build.log
	g++ -O2 -ftree-vectorize max-test.cpp -o max-test -fopt-info-vec &> max-test-cpp-build.log
	g++ -O2 -ftree-vectorize max-test.cxx -o max-test-cxx -fopt-info-vec &> max-test-cxx-build.log
	g++ -O2 -ftree-vectorize max-test.cc -o max-test-cc -fopt-info-vec &> max-test-cc-build.log
	g++ -O2 -ftree-vectorize max-test.CPP -o max-test-CPP -fopt-info-vec &> max-test-CPP-build.log
	g++ -O2 -ftree-vectorize max-test.c++ -o max-test-c++ -fopt-info-vec &> max-test-c++-build.log
	g++ -O2 -ftree-vectorize max-test.cp -o max-test-cp -fopt-info-vec &> max-test-cp-build.log
	g++ -O2 -ftree-vectorize max-test.C -o max-test-C -fopt-info-vec &> max-test-C-build.log
clean:
	@find . -type f -executable -exec sh -c "file -i '{}' | grep -q 'x-executable; charset=binary'" \; -print | xargs rm -f
distclean:
	@rm -rf *.c.patch
	@rm -rf *.cpp.patch
	@rm -rf *.cc.patch
	@rm -rf *build.log

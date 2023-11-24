build-no-optimized:
	gcc kruskal-no-optimized.c -o bin/noopt

build-optimized:
	gcc kruskal-no-optimized.c -o bin/opt

run-no-optmized: build-no-optimized
	./noopt

run-optmized: build-optimized
	./opt

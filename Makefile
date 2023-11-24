build-no-optimized:
	gcc kruskal-no-optimized.c -o noopt

build-optimized:
	gcc kruskal-no-optimized.c -o opt

run-no-optmized: build-no-optimized
	./noopt

run-optmized: build-optimized
	./opt

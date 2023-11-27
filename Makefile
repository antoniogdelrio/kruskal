build-no-optimized:
	gcc kruskal-no-optimized.c -o bin/noopt

build-optimized:
	gcc kruskal-optimized.c -o bin/opt

run-no-optmized: build-no-optimized
	./bin/noopt

run-optmized: build-optimized
	./bin/opt

run:
	gcc kruskal.c -o bin/kruskal
	./bin/kruskal ${vertexes} ${strategy}
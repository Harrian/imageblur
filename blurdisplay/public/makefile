
para: multioutmongo.cpp
	c++ --std=c++11 multioutmongo.cpp -o pmom.out -fopenmp -I/usr/local/include/mongocxx/v_noabi -I/usr/local/include/libmongoc-1.0 -I/usr/local/include/bsoncxx/v_noabi -I/usr/local/include/libbson-1.0 -L/usr/local/lib -lmongocxx -lbsoncxx

seq: seqmultioutmongo.cpp
	c++ --std=c++11 seqmultioutmongo.cpp -o smom.out -I/usr/local/include/mongocxx/v_noabi -I/usr/local/include/libmongoc-1.0 -I/usr/local/include/bsoncxx/v_noabi -I/usr/local/include/libbson-1.0 -L/usr/local/lib -lmongocxx -lbsoncxx

edgep: edgep.cpp
		c++ --std=c++11 edgep.cpp -o edgep.out -fopenmp -I/usr/local/include/mongocxx/v_noabi -I/usr/local/include/libmongoc-1.0 -I/usr/local/include/bsoncxx/v_noabi -I/usr/local/include/libbson-1.0 -L/usr/local/lib -lmongocxx -lbsoncxx

edges: edges.cpp
		c++ --std=c++11 edges.cpp -o edges.out -I/usr/local/include/mongocxx/v_noabi -I/usr/local/include/libmongoc-1.0 -I/usr/local/include/bsoncxx/v_noabi -I/usr/local/include/libbson-1.0 -L/usr/local/lib -lmongocxx -lbsoncxx

run:
	./pmom.out $(IMAGE) $(N) $(PE) & ./smom.out $(IMAGE) $(N) $(PE)

edgerun:
	./edgep.out $(IMAGE) 1 1 & ./edges.out $(IMAGE) 1 1

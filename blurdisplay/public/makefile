
para: multioutmongo.cpp
	c++ --std=c++11 multioutmongo.cpp -o pmom.out -fopenmp -I/usr/local/include/mongocxx/v_noabi -I/usr/local/include/libmongoc-1.0 -I/usr/local/include/bsoncxx/v_noabi -I/usr/local/include/libbson-1.0 -L/usr/local/lib -lmongocxx -lbsoncxx

seq: seqmultioutmongo.cpp
	c++ --std=c++11 seqmultioutmongo.cpp -o smom.out -I/usr/local/include/mongocxx/v_noabi -I/usr/local/include/libmongoc-1.0 -I/usr/local/include/bsoncxx/v_noabi -I/usr/local/include/libbson-1.0 -L/usr/local/lib -lmongocxx -lbsoncxx

run:
	./pmom.out $(IMAGE) $(N) $(PE) & ./smom.out $(IMAGE) $(N) $(PE)

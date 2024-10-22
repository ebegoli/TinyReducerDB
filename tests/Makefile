CC = gcc
CFLAGS = -Wall -g
TARGET = TinyReducerDB_tests

TESTS = test_quantization test_gmm_operations

all: $(TESTS)

test_quantization: test_quantization.o ../src/GMM.o
	$(CC) $(CFLAGS) -o test_quantization test_quantization.o ../src/GMM.o

test_gmm_operations: test_gmm_operations.o ../src/GMM.o
	$(CC) $(CFLAGS) -o test_gmm_operations test_gmm_operations.o ../src/GMM.o

test_quantization.o: test_quantization.c ../src/GMM.h
	$(CC) $(CFLAGS) -c test_quantization.c

test_gmm_operations.o: test_gmm_operations.c ../src/GMM.h
	$(CC) $(CFLAGS) -c test_gmm_operations.c

clean:
	rm -f *.o $(TESTS)

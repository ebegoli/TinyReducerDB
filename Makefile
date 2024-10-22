CC = gcc
CFLAGS = -Wall -g
TARGET = TinyReducerDB

all: $(TARGET)

$(TARGET): main.o GMM.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o GMM.o

main.o: main.c GMM.h
	$(CC) $(CFLAGS) -c main.c

GMM.o: GMM.c GMM.h
	$(CC) $(CFLAGS) -c GMM.c

clean:
	rm -f *.o $(TARGET)
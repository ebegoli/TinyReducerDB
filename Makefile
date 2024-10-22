TARGET = TinyReducerDB

EXE := $(BIN_DIR)/tinyreducerdb

SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

EXE := $(BIN_DIR)/nyreducerdb
SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CFLAGS   := -Wall

.PHONY: all clean

all: $(TARGET)

$(TARGET): main.o GMM.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o GMM.o

main.o: $(SRC_DIR)/main.c $(SRC_DIR)/GMM.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.c

GMM.o: $(SRC_DIR)/GMM.c $(SRC_DIR)/GMM.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/GMM.c

clean:
	rm -f *.o $(TARGET)
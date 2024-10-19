CC = gcc
CFLAGS = -Wall -Wextra -O2

TARGET = tiny_reducer_db
SRC = main.c tiny_reducer_db.c gmm.c

all: $(TARGET)

$(TARGET): $(SRC)
    $(CC) $(CFLAGS) -o $@ $(SRC)

clean:
    rm -f $(TARGET)

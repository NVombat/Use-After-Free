CC = gcc
CFLAGS = -Wall -O2
SRC = use_after_free.c
TARGET = use_after_free

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
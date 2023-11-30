CC = gcc
CFLAGS = -Wall -g -O2

SRC1 = heap_overflow.c
SRC2 = use_after_free.c

TARGET1 = $(SRC1:.c=)
TARGET2 = $(SRC2:.c=)

all: $(TARGET1) $(TARGET2)

$(TARGET1): $(SRC1)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET2): $(SRC2)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET1) $(TARGET2)
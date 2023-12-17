CC = gcc
CFLAGS = -Wall -g -O2

SRC1 = heap_overflow.c
SRC2 = use_after_free.c
SRC3 = use_after_free_fix.c

TARGET1 = $(SRC1:.c=)
TARGET2 = $(SRC2:.c=)
TARGET3 = $(SRC3:.c=)
TEST_TARGET = test_uaf

all: $(TARGET1) $(TARGET2) $(TARGET3) $(TEST_TARGET)

$(TARGET1): $(SRC1)
	$(CC) $(CFLAGS) -o $(TARGET1) $(SRC1)

$(TARGET2): $(SRC2)
	$(CC) $(CFLAGS) -o $(TARGET2) $(SRC2)

$(TARGET3): $(SRC3)
	$(CC) $(CFLAGS) -o $(TARGET3) $(SRC3)

test: $(TEST_TARGET)

$(TEST_TARGET): $(SRC2)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(SRC2)

heap_overflow: $(TARGET1)

$(TARGET1): $(SRC1)
	$(CC) $(CFLAGS) -o $(TARGET1) $(SRC1)

uaf: $(TARGET2)

$(TARGET2): $(SRC2)
	$(CC) $(CFLAGS) -o $(TARGET2) $(SRC2)

uaf_fix: $(TARGET3)

$(TARGET3): $(SRC3)
	$(CC) $(CFLAGS) -o $(TARGET3) $(SRC3)

clean:
	rm -f $(TARGET1) $(TARGET2) $(TARGET3) $(TEST_TARGET)
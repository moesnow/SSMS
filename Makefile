CC = gcc
CFLAGS = -Wall -Werror
TARGET = ssms
SOURCE = main.c

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(TARGET)


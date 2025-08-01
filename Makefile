CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = zdice
SOURCES = main.c game.c gamerunner.c utils.c

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run

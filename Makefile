CC = gcc
CFLAGS = -Wall -Wextra -std=c99 `pkg-config --cflags gtk+-3.0`
LIBS = `pkg-config --libs gtk+-3.0` -lm

TARGET = scientific_calculator
SOURCE = scientific_calculator.c

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE) $(LIBS)

clean:
	rm -f $(TARGET)

install-deps:
	sudo apt update && sudo apt install -y libgtk-3-dev pkg-config

.PHONY: all clean install-deps
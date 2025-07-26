# Makefile for Enhanced SPI & Timer Driver Project

CC = arm-none-eabi-gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude
LDFLAGS = 
SRC = src/SPI.c src/Timer.c src/main.c
OBJ = $(SRC:.c=.o)
TARGET = spi_timer.elf

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

# Test build (simulation)
test: test/test_spi_timer.c src/SPI.c src/Timer.c
	gcc -Wall -Wextra -std=c11 -Iinclude test/test_spi_timer.c src/SPI.c src/Timer.c -o test/test_spi_timer

.PHONY: all clean test

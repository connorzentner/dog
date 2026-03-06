CC = gcc
CFLAGS = -Wall -Wextra -g

TARGET = dog

SRC = dog.c config.c

$(TARGET): $(SRC) syntax.h
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean: 
	rm -rf $(TARGET)

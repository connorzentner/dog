CC = gcc
CFLAGS = -Wall -Wextra -g

TARGET = dog

SRC = main.c config.c

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean: 
	rm -rf $(TARGET)

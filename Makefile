CC = gcc
CFLAGS = -Iinclude
LDFLAGS = -lcurl
SRC = src/main.c src/model.c src/request.c src/asciiart.c lib/cJSON.c
OBJ = $(SRC:.c=.o)
TARGET = bin/locatr

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

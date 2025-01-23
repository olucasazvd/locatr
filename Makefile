CC = gcc
CFLAGS = -Iinclude
LDFLAGS = -lcurl

SRC = src/main.c src/model.c src/request.c src/asciiart.c lib/cJSON.c
OBJ = $(patsubst %.c, build/%.o, $(SRC))
TARGET = bin/locatr

$(TARGET): $(OBJ) | bin
	$(CC) -o $(TARGET) $(OBJ) $(LDFLAGS)

build/%.o: %.c | build
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

build:
	mkdir -p build

bin:
	mkdir -p bin

clean:
	rm -rf build bin

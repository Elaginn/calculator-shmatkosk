CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c11
SRC = src/main.c
OUT = build/app.exe

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

clean:
	rm -rf build/*

run-int:
	./build/app.exe

run-float:
	./build/app.exe --float


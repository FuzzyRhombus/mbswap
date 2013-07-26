CC = gcc
CFLAGS = -Wall -framework IOKit -framework ApplicationServices
SRC = switchMainDisplay.c
EXEC = mbswap 

$(EXEC): $(SRC)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -rf *.o $(EXEC)


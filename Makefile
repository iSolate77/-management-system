CC = cc
CFLAGS = -Wall -Wextra
LDFLAGS = -lsqlite3

objects = src/main.o src/system.o src/auth.o src/db.o

all: atm

atm: $(objects)
	$(CC) $(CFLAGS) -o atm $(objects) $(LDFLAGS)

src/main.o: src/header.h
src/system.o: src/header.h
src/auth.o: src/header.h
src/db.o: src/db.h

clean:
	rm -f $(objects) atm

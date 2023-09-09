CC = cc
CFLAGS = -Wall -Wextra
LDFLAGS = -lsqlite3

SRCS = src/main.c src/system.c src/auth.c src/db.c
OBJS = $(SRCS:.c=.o)

all: atm

atm: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

src/main.o: src/header.h
src/system.o: src/header.h
src/auth.o: src/header.h
src/db.o: src/db.h

clean:
	rm -f $(OBJS) atm


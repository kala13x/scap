LIB = -lcurl
OBJ = o
CFLAGS = -g -O2 -Wall
PREFIX = /usr/local

OBJS = scap.$(OBJ) info.$(OBJ) slog.$(OBJ)

all: $(OBJS)
	$(CC) $(CFLAGS) -o scap $(OBJS) $(LIB)

scap.$(OBJ): info.h slog.h stdinc.h
info.$(OBJ): info.h stdinc.h
slog.$(OBJ): slog.h stdinc.h

.PHONY: install
install: scap
	install -m 0755 scap $(PREFIX)/bin


.PHONY: clean
clean:
	$(RM) scap $(OBJS)

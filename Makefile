LIB = -lnsl libslog/slog.so
OBJ = o
CFLAGS = -g -O2 -Wall -Ilibslog
PREFIX = /usr/local

OBJS = scap.$(OBJ) packet.$(OBJ) info.$(OBJ)

all: $(OBJS)
	$(CC) $(CFLAGS) -o scap $(OBJS) $(LIB)

scap.$(OBJ): info.h stdinc.h
packet.$(OBJ): packet.h stdinc.h
info.$(OBJ): info.h stdinc.h

.PHONY: install
install: scap
	install -m 0755 scap $(PREFIX)/bin


.PHONY: clean
clean:
	$(RM) scap $(OBJS)

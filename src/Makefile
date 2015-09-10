LIB = -lnsl ../slog/libslog.a
CFLAGS = -g -O2 -Wall -I../slog
PREFIX = /usr/local
BUILD = ../bin

OBJS = scap.o packet.o errex.o info.o

all: $(OBJS)
	$(CC) $(CFLAGS) -o scap $(OBJS) $(LIB)
	@echo [-] Building binaries into - $(BUILD)
	@test -d $(BUILD) || mkdir $(BUILD)
	@install -m 0755 scap $(BUILD)/
	@install -m 0664 config.cfg $(BUILD)/

scap.o: info.h stdinc.h
packet.o: packet.h stdinc.h
errex.o: errex.h stdinc.h
info.o: info.h stdinc.h

.PHONY: install
install: scap
	install -m 0755 scap $(PREFIX)/bin


.PHONY: clean
clean:
	$(RM) scap $(OBJS)
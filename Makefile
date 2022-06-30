SOURCES=$(wildcard src/*.c) $(wildcard src/commands/*.c)

LIBS=-ljson-c

td: $(SOURCES)
	$(CC) $(CFLAGS) \
		-g -Werror -I./include \
		-o $@ $(SOURCES) \
		$(LIBS)

clean:
	rm -f td

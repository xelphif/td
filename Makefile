TARGET   = td

CC       = gcc
CFLAGS   = -Wall -I./src

LINKER   = gcc
LFLAGS   = -ljson-c

SRCDIR   = src
OBJDIR   = obj
BINDIR   = bin
CMDDIR   = $(SRCDIR)/commands

BINDEBUG = $(BINDIR)/test/debug

SOURCES  := $(wildcard $(CMDDIR)/*.c) $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm       = rm -f

LBIN		 = ${HOME}/.local/bin

$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(LINKER) $(OBJECTS) $(LFLAGS) -s -o $@
	@echo "Linking complete"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully"

.PHONY: debug install clean remove
debug:
	@$(CC) $(CFLAGS) -g $(SOURCES) $(LFLAGS) -o $(BINDEBUG)
	@echo "Compiled debug binary"

install: $(BINDIR)/$(TARGET)
	@cp $(BINDIR)/$(TARGET) $(LBIN)
	@echo "Installed binary to $(LBIN)"

clean:
	@$(rm) $(OBJECTS)
	@echo "Cleanup complete"

remove: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@$(rm) $(BINDEBUG)
	@echo "Executables removed"

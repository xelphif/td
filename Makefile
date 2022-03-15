TARGET   = nctd

CC       = gcc
CFLAGS   = -Wall -I./src

LINKER   = gcc
LFLAGS   = -Wall -ljson-c

SRCDIR   = src
OBJDIR   = obj
BINDIR   = bin
CMDDIR   = $(SRCDIR)/commands

SOURCES  := $(wildcard $(CMDDIR)/*.c) $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm       = rm -f

$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(LINKER) $(OBJECTS) $(LFLAGS) -o $@
	@echo "Linking complete"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully"

.PHONY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "Cleanup complete"

.PHONY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Executable removed"

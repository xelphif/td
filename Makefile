CC 		= gcc
LIBS	= -lncurses

SRCDIR	= src
OBJDIR	= obj
BINDIR	= bin
DIRS	= $(SRCDIR) $(OBJDIR) $(BINDIR)

NCTODO	= $(BINDIR)/nctodo
TCLI	= $(BINDIR)/tcli

rm		= rm -f

all: $(NCTODO) $(TCLI)

$(NCTODO) : $(OBJDIR)/nctodo.o $(OBJDIR)/node.o | $(DIRS)
	@$(CC) $(LIBS) $? -o $@
	@echo "Linking complete"

$(TCLI) : $(OBJDIR)/tcli.o $(OBJDIR)/node.o | $(DIRS)
	@$(CC) $? -o $@
	@echo "Linking complete"

$(OBJDIR)/%.o : $(SRCDIR)/%.c | $(DIRS)
	@$(CC) -c $< -o $@
	@echo "Compiled "$<" successfully"

$(DIRS):
	@mkdir -p $(DIRS)

.PHONY: clean
clean:
	$(rm) $(OBJDIR)/*.o

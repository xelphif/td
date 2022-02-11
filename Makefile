CC 			= gcc
LIBS		= -lncurses

SRCDIR	= src
OBJDIR	= obj
BINDIR	= bin
DIRS	= $(SRCDIR) $(OBJDIR) $(BINDIR)

NCTODO	= $(BINDIR)/nctodo
TD	= $(BINDIR)/td

rm		= rm -f

all: $(NCTODO) $(TD)

$(NCTODO) : $(OBJDIR)/nctodo.o $(OBJDIR)/task.o
	@$(CC) $(LIBS) $^ -o $@
	@echo "Linking complete"

$(TD) : $(OBJDIR)/td.o $(OBJDIR)/task.o
	@$(CC) $^ -o $@
	@echo "Linking complete"

$(OBJDIR)/%.o : $(SRCDIR)/%.c | $(DIRS)
	@$(CC) -c $< -o $@
	@echo "Compiled "$<" successfully"

$(DIRS):
	@mkdir -p $(DIRS)

.PHONY: clean
clean:
	$(rm) $(OBJDIR)/*.o

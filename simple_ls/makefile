IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)
ODIR=objectFiles

$(info adding header file)
_DEPS = system_call.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

$(info -- Populating objectFiles directory--)
_OBJ = main.o system_call.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(info -- Compiling simple_ls.exe--)
simple_ls: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
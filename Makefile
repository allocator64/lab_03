BINDIR=bin
OBJDIR=obj
SRCDIR=src

CC=gcc
CFLAGS=-Wall -m32
LDFLAGS=-m32
LDLIBS=-lm
NASM=nasm
NFLAGS="-f elf32"

TARGET=$(BINDIR)/$(shell basename `pwd`)
C_SOURCES=$(wildcard $(SRCDIR)/*.c)
ASM_SOURCES=$(wildcard $(SRCDIR)/*.asm)
OBJECTS=$(C_SOURCES:$(SRCDIR)%.c=$(OBJDIR)%.o) $(ASM_SOURCES:$(SRCDIR)%.asm=$(OBJDIR)%.o)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(OBJDIR)/%.o: $(SRCDIR)/%.asm
	$(NASM) $(NFLAGS) -o $@ $<

all: $(TARGET)

$(OBJECTS): $(SOURCES)

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(LDFLAGS) $(OBJECTS) $(LDLIBS)

clean:
	$(RM) $(TARGET) $(OBJECTS)

.PHONY: all clean

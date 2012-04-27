OBJDIR=obj
SRCDIR=src

CC=gcc
CFLAGS=-Wall -Werror -O2 -m32
LDFLAGS=-m32
LDLIBS=-lm
NASM=nasm
NFLAGS=-f elf32 -Ox
MKDIR=@mkdir -p $(@D)

TARGET=$(shell basename `pwd`)
C_SOURCES=$(wildcard $(SRCDIR)/*.c)
ASM_SOURCES=$(wildcard $(SRCDIR)/*.asm)
OBJECTS=$(C_SOURCES:$(SRCDIR)%.c=$(OBJDIR)%.o) $(ASM_SOURCES:$(SRCDIR)%.asm=$(OBJDIR)%.o)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(MKDIR)
	$(CC) -c $(CFLAGS) -o $@ $<

$(OBJDIR)/%.o: $(SRCDIR)/%.asm
	$(MKDIR)
	$(NASM) $(NFLAGS) -o $@ $<

all: $(TARGET)

$(OBJECTS): $(SOURCES)

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(LDFLAGS) $(OBJECTS) $(LDLIBS)


clean:
	$(RM) $(TARGET) $(OBJECTS)

.PHONY: all clean

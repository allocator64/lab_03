OBJDIR=obj
SRCDIR=src

CC=gcc
CFLAGS=-Wall -Werror -pedantic -std=c99 -march=native -O2 -finline-functions -frename-registers -m32
reverse: CFLAGS+= -DSORT_REVERSE
LDFLAGS=-m32
LDLIBS=-lm
NASM=nasm
NFLAGS=-f elf32 -Ox
MKDIR=@mkdir -p $(@D)
STRIP=strip

TARGET=$(shell basename `pwd`)
C_SOURCES=$(wildcard $(SRCDIR)/*.c)
ASM_SOURCES=$(wildcard $(SRCDIR)/*.asm)
SOURCES=$(C_SOURCES) $(ASM_SOURCES)
OBJECTS=$(C_SOURCES:$(SRCDIR)%.c=$(OBJDIR)%.o) $(ASM_SOURCES:$(SRCDIR)%.asm=$(OBJDIR)%.o)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(SRCDIR)/%.h $(SRCDIR)/common.h
	$(MKDIR)
	$(CC) -c $(CFLAGS) -o $@ $<

$(OBJDIR)/%.o: $(SRCDIR)/%.asm
	$(MKDIR)
	$(NASM) $(NFLAGS) -o $@ $<

all: clean $(TARGET)
	$(STRIP) $(TARGET)

reverse : clean all

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(LDFLAGS) $(OBJECTS) $(LDLIBS)

clean:
	$(RM) $(TARGET) $(OBJECTS)

.PHONY: all clean

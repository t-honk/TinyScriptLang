SHELL = /bin/sh
CC=gcc
CXX=g++
SRCDIR = ./src
BUILDDIR = build
BINDIR = bin
SOURCES 	= $(shell find $(SRCDIR) -type f -regex "\.\/.+.c[pp]*")
HEADERS 	= $(shell echo $(SRCDIR)/include/*.h)
CFLAGS= -O3 -Wall -mtune=znver2 -mavx2 -Wl,-rpath=./ -I$(SRCDIR)/include -g
SRCEXT = c
OBJEXT = o
TARGET=$(BINDIR)/interpreter.exe
LDFLAGS= -Wall -mtune=znver2 -mavx2 -Wl,-rpath=./ -I$(SRCDIR)/include
OBJECTS 	= $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))
RM= rm -f


directories:
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(BINDIR)

$(BUILDDIR)/%.$(OBJEXT) : $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<


windows : directories $(TARGET)
	#$(CC) $(SOURCES) -o $(TARGET) $(CFLAGS)


$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^ ${LDFLAGS}
	 #-${RM} ${OBJECTS}
	
.PHONY: clean
clean:
	-${RM} -r $(BUILDDIR) $(BINDIR)
#Architecture
ARCH := $(shell uname -m)

#Compilers
CC          := g++ -std=c++17 -Wno-psabi

#The Target Library

#The Directories, Source, Includes, Objects, Binary and Resources
SRCEXT      := cc

# Directories
CHIPDIR     := /usr/local/src/Chipmunk2D
ENVIRODIR   := /usr/local/src/enviro/server/include

#Flags, Libraries and Includes
CFLAGS      := -ggdb  -shared -fPIC
INCLUDE		:= -I $(ENVIRODIR) -I $(CHIPDIR)/include/chipmunk 

#Files

TARGETDIR	 := ../lib
SOURCES      := $(wildcard *.cc)
HEADERS      := $(wildcard *.h)
TARGETS		 := $(patsubst %.cc,%.so,$(wildcard *.cc))
FULL_TARGETS := $(addprefix $(TARGETDIR)/, $(TARGETS))

#Default Make
all: $(FULL_TARGETS)

#Clean only Objects
clean:
	@$(RM) -rf $(TARGETDIR)/*.so

# Compile
$(TARGETDIR)/%.so: %.cc %.h
	$(CC) $(CFLAGS) $(INCLUDE) $< -o $@


# 'make depend'      uses makedepend to automatically generate dependencies 
#                    (dependencies are added to end of Makefile)
# 'make'             build executable file 'mycc'
# 'make clean'       removes all .o files
# 'make clean all'   removes all .o files and executable file

# define the C++ compiler to use
CC := g++
RM := rm -rf

# define any compile-time flags
CFLAGS := -Wall -Werror -g -std=c++11

# define any directories containing header files other than /usr/include
#
INC := ./headers ./sources /usr/local/opt/openssl/include
INCLUDES := $(foreach d, $(INC), -I$d)

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
LFLAGS := -L./libs -L/usr/local/opt/openssl/lib

# This should generate a shared object
LDFLAGS := -shared

# define any libraries to link into executable:
#   if I want to link in libraries (libx.so or libx.a) I use the -llibname 
#   option, something like (this will link in libmylib.so and libm.so:
LIBS := -lcurl -lm -lcrypto

# define the C++ source files
SRC_DIR := sources
SRCS := $(SRC_DIR)/main.cpp $(SRC_DIR)/board.cpp $(SRC_DIR)/player.cpp $(SRC_DIR)/game.cpp

# define the C++ object files 
#
# This uses Suffix Replacement within a macro:
#   $(name:string1=string2)
#         For each word in 'name' replace 'string1' with 'string2'
# Below we are replacing the suffix .c of all words in the macro SRCS
# with the .o suffix
#
OBJS := $(SRCS:.cpp=.o)

# define the executable file 
MAIN := mycc

#
# The following part of the makefile is generic; it can be used to 
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

.PHONY: depend clean clean_all

all:    $(MAIN)
	@echo  Simple compiler named mycc has been compiled 

$(MAIN): $(OBJS) 
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

# this is a suffix replacement rule for building .o's from .cpp's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .cpp file) and $@: the name of the target of the rule (a .o file) 
# (see the gnu make manual section about automatic variables)
.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) sources/*.o *~
	$(RM) $(MAIN).dSYM

clean_all:
	$(RM) sources/*.o *~ $(MAIN)
	$(RM) $(MAIN).dSYM

depend: $(SRCS)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it

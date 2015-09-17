# Source files
SOURCES  = ../room/room.cpp

# Header files
HSOURCES = ../room/room_properties.hpp \
           ../room/room.hpp

# Compiler options
CFLAGS = -std=c++11 -g -Wall

#####
###
#
# 'Make' commands
#
###
#####


# $ 'make' or 'make help'
help:
	# INSTRUCTIONS:
	#   To test, run: make output
	#   To test memory allocation, run: make output mem_chk
	#   To remove compiled output files, run: make clean

# $ make output
output: $(SOURCES) $(HSOURCES)
	g++ $(CFLAGS) $(SOURCES) -o output
	# To execute the program, run: ./output

# $ make mem_chk
mem_chk: $(SOURCES) $(HSOURCES)
	valgrind --leak-check=full ./output

# $ make clean
# Removes created files
clean:
	rm -f output *.o *~

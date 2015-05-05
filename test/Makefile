# Source files
SOURCES  = ../room/room_properties.hpp \
           ../room/room.hpp

# Header files
HSOURCES = ../room/room.cpp

# Compiler options
CFLAGS = -std=c++11 -g -Wall

#####
###
#
# 'Make' commands
#
###
#####

# $ make
output: $(SOURCES) $(HSOURCES)
	g++ $(CFLAGS) $(SOURCES) -o output
	# To execute the program, run: ./output

# $ make <custom>
#<custom>: <source_files>
#	<command>

# $ make clean
# Removes created files
clean:
	rm -f output *.o *~

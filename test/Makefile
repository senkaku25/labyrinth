# Room source files
ROOMSOURCES  = ../src/room.cpp \
               test_room.cpp

# Header files
HSOURCES = ../include/room_properties.hpp \
           ../include/room.hpp

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
	#   To test class Room, run: make room
	#   To test memory allocation of class Room, run: make room mem_chk
	#   To remove compiled output files, run: make clean

# $ make room
room: $(ROOMSOURCES) $(HSOURCES)
	g++ $(CFLAGS) $(ROOMSOURCES) -o output
	# To execute the program, run: ./output

# $ make mem_chk
mem_chk: $(SOURCES) $(HSOURCES)
	valgrind --leak-check=full ./output

# $ make clean
# Removes created files
clean:
	rm -f output *.o *~

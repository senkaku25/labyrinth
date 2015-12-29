# Room source files
ROOMSOURCES  = ../src/room.cpp \

# Labyrinth source files
LABYRINTHSOURCES = ../src/labyrinth.cpp \
                   ../src/labyrinth_map.cpp \

# Header files
HSOURCES = ../include/room_properties.hpp \
           ../include/room.hpp \
           ../include/coordinate.hpp \
           ../include/labyrinth.hpp \
           ../include/labyrinth_map.hpp \

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
	#   To test class Labyrinth, run: make laby
	# 	To test class LabyrinthMap, run: make labymap
	#   To test memory allocation of class Labyrinth, run: make laby mem_chk
	#   To remove compiled output files, run: make clean

# $ make room
room: $(ROOMSOURCES) $(HSOURCES)
	g++ $(CFLAGS) $(ROOMSOURCES) test_room.cpp -o output
	# To execute the program, run: ./output

# $ make laby
laby: $(ROOMSOURCES) $(LABYRINTHSOURCES) $(HSOURCES)
	g++ $(CFLAGS) $(ROOMSOURCES) $(LABYRINTHSOURCES) test_laby.cpp -o output
	# To execute the program, run: ./output

# $ make labymap
labymap: $(ROOMSOURCES) $(LABYRINTHSOURCES) $(HSOURCES)
	g++ $(CFLAGS) $(ROOMSOURCES) $(LABYRINTHSOURCES) test_labymap.cpp -o output
	# To execute the program, run: ./output

# $ make mem_chk
mem_chk: $(SOURCES) $(HSOURCES)
	valgrind --leak-check=full ./output

# $ make clean
# Removes created files
clean:
	rm -f output *.o *~

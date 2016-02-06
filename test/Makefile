# General header files
HEADERS = \
  ../include/coordinate.hpp \
  ../include/room_properties.hpp \
  ../include/room.hpp \
  ../include/labyrinth.hpp \
  ../include/labyrinth_map.hpp

# Room files
ROOMHEADERS = \
  ../include/room.hpp \

# Room source files
ROOMSOURCES = \
  ../src/room.cpp

# Labyrinth header files
LABYRINTHHEADERS = \
  ../include/labyrinth.hpp

# Labyrinth source files
LABYRINTHSOURCES = \
  ../src/labyrinth.cpp

# Labyrinth map header files
LABYRINTHMAPHEADERS = \
  ../include/labyrinth_map.hpp

# Labyrinth map source files
LABYRINTHMAPSOURCES = \
  ../src/labyrinth_map.cpp

# g++ options
GCC = g++ -std=c++14

# g++ compiling flags
GCC-CFLAGS = -c -Wall -Wextra -Wmissing-declarations -Werror

# g++ linking flags
GCC-LFLAGS = -Wall -Wextra -Wmissing-declarations -Werror

# Clang compilation options
CLANG = clang++-3.5 -std=c++14 -Werror -fshow-source-location -fshow-column -fcaret-diagnostics -fcolor-diagnostics -fdiagnostics-show-option

# Output filename
OUTPUT = output

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
	# Compilation is done with g++ unless otherwise specified.
	#
	#   Testing:
	#
	#     To test class Room, run:         make test-room
	#     To test class Labyrinth, run:    make test-laby
	#     To test class LabyrinthMap, run: make test-map
	#
	#     To test compilation of LabyrinthMap with Clang, run: make test-clang
	#
	#   To remove compiled files, run: make clean

# Executed whenever an object file is out of date
# Symbols:
#   % refers to any character(s)
#   $< refers to the first item in the dependency list
%.o: ../src/%.cpp $(HEADERS)
	$(GCC) $(GCC-CFLAGS) $<

# $ make test-room
test-room: room.o
	$(GCC) $(GCC-LFLAGS) room.o test_room.cpp -o $(OUTPUT)
	# To execute the program, run: ./output

# $ make test-laby
test-laby: room.o labyrinth.o
	$(GCC) $(GCC-LFLAGS) room.o labyrinth.o test_laby.cpp -o $(OUTPUT)
	# To execute the program, run: ./output

# $ make test-map
test-map: room.o labyrinth.o labyrinth_map.o
	$(GCC) $(GCC-LFLAGS) room.o labyrinth.o labyrinth_map.o test_labymap.cpp -o $(OUTPUT)
	# To execute the program, run: ./output

# $ make test-clang
test-clang: $(ROOMHEADERS) $(ROOMSOURCES) $(LABYRINTHHEADERS) $(LABYRINTHSOURCES) $(LABYRINTHMAPHEADERS)
	$(CLANG) $(ROOMSOURCES) $(LABYRINTHSOURCES) $(LABYRINTHMAPSOURCES) test_labymap.cpp -o $(OUTPUT)
	# To execute the program, run: ./output

# $ make clean
# Removes created files
clean:
	rm -f $(OUTPUT) *.o *~ a.out

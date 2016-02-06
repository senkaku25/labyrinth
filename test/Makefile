# Room header files
ROOMHEADERS = \
  ../include/coordinate.hpp \
  ../include/room_properties.hpp \
  ../include/room.hpp \

# Room source files
ROOMSOURCES = \
  ../src/room.cpp

# Room object files
ROOMOBJ = \
  room.o

# Labyrinth header files
LABYRINTHHEADERS = \
  ../include/coordinate.hpp \
  ../include/room_properties.hpp \
  ../include/room.hpp \
  ../include/labyrinth.hpp

# Labyrinth source files
LABYRINTHSOURCES = \
  ../src/labyrinth.cpp

# Labyrinth object files
LABYRINTHOBJ = \
  labyrinth.o

# Labyrinth map header files
LABYRINTHMAPHEADERS = \
  ../include/coordinate.hpp \
  ../include/room_properties.hpp \
  ../include/room.hpp \
  ../include/labyrinth.hpp \
  ../include/labyrinth_map.hpp

# Labyrinth map source files
LABYRINTHMAPSOURCES = \
  ../src/labyrinth_map.cpp

# Labyrinth map object files
LABYRINTHMAPOBJ = \
  labyrinth_map.o

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
	#     To test compilation of Labyrinth with Clang, run: make test-clang
	#
	#   To remove compiled files, run: make clean

# Executed whenever room.o is out of date
room.o: $(ROOMHEADERS) $(ROOMSOURCES)
	$(GCC) $(GCC-CFLAGS) $(ROOMSOURCES)

# Executed whenever labyrinth.o is out of date
labyrinth.o: $(LABYRINTHHEADERS) $(LABYRINTHSOURCES)
	$(GCC) $(GCC-CFLAGS) $(LABYRINTHSOURCES)

# Executed whenever labyrinth_map.o is out of date
labyrinth_map.o: $(LABYRINTHMAPHEADERS) $(LABYRINTHMAPSOURCES)
	$(GCC) $(GCC-CFLAGS) $(LABYRINTHMAPSOURCES)

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

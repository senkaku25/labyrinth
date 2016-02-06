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
  ../include/labyrinth.hpp

# Labyrinth source files
LABYRINTHSOURCES = \
  ../src/labyrinth.cpp

# Labyrinth object files
LABYRINTHOBJ = \
  labyrinth.o

# Labyrinth map header files
LABYRINTHMAPHEADERS = \
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
	#
	#   Testing:
	#     Either -gcc (to compile using g++) or -clang (to compile using Clang)
	#     must be used in place of <compiler>.
	#
	#     To test class Room, run:         make test-room<compiler>
	#     To test class Labyrinth, run:    make test-laby<compiler>
	#     To test class LabyrinthMap, run: make test-labymap<compiler>
	#
	#     To test compilation of everything with g++ and Clang, run: make test-compile
	#
	#   To remove compiled output files, run: make clean

# Executed whenever room.o is out of date
room.o: $(ROOMHEADERS) $(ROOMSOURCES)
	$(GCC) $(GCC-CFLAGS) $(ROOMSOURCES)

# Executed whenever labyrinth.o is out of date
labyrinth.o: $(ROOMHEADERS) $(ROOMSOURCES) $(LABYRINTHHEADERS) $(LABYRINTHSOURCES)
	$(GCC) $(GCC-CFLAGS) $(ROOMSOURCES) $(LABYRINTHSOURCES)

# Executed whenever labyrinth_map.o is out of date
labyrinth_map.o: $(ROOMHEADERS) $(ROOMSOURCES) $(LABYRINTHHEADERS) $(LABYRINTHSOURCES) $(LABYRINTHMAPHEADERS) $(LABYRINTHMAPSOURCES)
	$(GCC) $(GCC-CFLAGS) $(ROOMSOURCES) $(LABYRINTHSOURCES) $(LABYRINTHMAPSOURCES)

# $ make test-room-gcc
test-room-gcc: room.o
	$(GCC) $(GCC-LFLAGS) room.o test_room.cpp -o $(OUTPUT)
	# To execute the program, run: ./output

# $ make test-room-clang
test-room-clang: room.o
	$(CLANG) room.o test_room.cpp -o $(OUTPUT)
	# To execute the program, run: ./output

# $ make test-laby-gcc
test-laby-gcc: room.o labyrinth.o
	$(GCC) $(GCC-LFLAGS) room.o labyrinth.o test_laby.cpp -o $(OUTPUT)
	# To execute the program, run: ./output

# $ make test-laby-clang
test-laby-clang: room.o labyrinth.o
	$(CLANG) room.o labyrinth.o test_laby.cpp -o $(OUTPUT)
	# To execute the program, run: ./output

# $ make test-labymap-gcc
test-labymap-gcc: room.o labyrinth.o labyrinth_map.o
	$(GCC) $(GCC-LFLAGS) room.o labyrinth.o labyrinth_map.o test_labymap.cpp -o $(OUTPUT)
	# To execute the program, run: ./output

# $ make test-labymap-clang
test-labymap-clang: room.o labyrinth.o labyrinth_map.o
	$(CLANG) room.o labyrinth.o labyrinth_map.o test_labymap.cpp -o $(OUTPUT)
	# To execute the program, run: ./output

# $ make clean
# Removes created files
clean:
	rm -f $(OUTPUT) *.o *~ a.out

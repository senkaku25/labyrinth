# General header files
HEADERS = \
  ../include/coordinate.hpp \
  ../include/room_properties.hpp \
  ../include/room.hpp \
  ../include/labyrinth.hpp \
  ../include/labyrinth_map.hpp

# Room source files
ROOMSOURCES = \
  ../src/room.cpp

# Labyrinth source files
LABYRINTHSOURCES = \
  ../src/labyrinth.cpp

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
	@echo "INSTRUCTIONS:"
	@echo "Compilation is done with g++ unless otherwise specified."
	@echo ""
	@echo "Testing:"
	@echo ""
	@echo "    To test class Room, run:         make test-room"
	@echo "    To test class Labyrinth, run:    make test-laby"
	@echo "    To test class LabyrinthMap, run: make test-map"
	@echo ""
	@echo "    To test compilation of LabyrinthMap with Clang, run: make test-clang"
	@echo ""
	@echo "  To remove compiled files, run: make clean"

# Executed whenever an object file is out of date
# Symbols:
#   % refers to any character(s)
#   $< refers to the first item in the dependency list
%.o: ../src/%.cpp $(HEADERS)
	$(GCC) $(GCC-CFLAGS) $<

# $ make test-room
test-room: room.o test_room.cpp
	$(GCC) $(GCC-LFLAGS) room.o test_room.cpp -o $(OUTPUT)
	@echo "To execute the program, run: ./$(OUTPUT)"

# $ make test-laby
test-laby: room.o labyrinth.o test_laby.cpp
	$(GCC) $(GCC-LFLAGS) room.o labyrinth.o test_laby.cpp -o $(OUTPUT)
	@echo "To execute the program, run: ./$(OUTPUT)"

# $ make test-map
test-map: room.o labyrinth.o labyrinth_map.o test_labymap.cpp
	$(GCC) $(GCC-LFLAGS) room.o labyrinth.o labyrinth_map.o test_labymap.cpp -o $(OUTPUT)
	@echo "To execute the program, run: ./$(OUTPUT)"

# $ make test-clang
test-clang: $(HEADERS) $(LABYRINTHMAPSOURCES) test_labymap.cpp
	$(CLANG) $(ROOMSOURCES) $(LABYRINTHSOURCES) $(LABYRINTHMAPSOURCES) test_labymap.cpp -o $(OUTPUT)
	@echo "To execute the program, run: ./$(OUTPUT)"

# $ make clean
# Removes created files
clean:
	rm -f $(OUTPUT) *.o *~ a.out

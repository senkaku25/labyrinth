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

# g++ compilation options
GPP = g++ -std=c++14 -g -Wall -Wextra -Wmissing-declarations -Werror

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
	#     Either -gpp (to compile using g++) or -clang (to compile using Clang)
	#     must be used in place of <compiler>.
	#
	#     To test class Room, run:         make test-room<compiler>
	#     To test class Labyrinth, run:    make test-laby<compiler>
	#     To test class LabyrinthMap, run: make test-labymap<compiler>
	#
	#     To test compilation of everything with g++ and Clang, run: make test-compile
	#
	#   To remove compiled output files, run: make clean

# $ make test-room-gpp
test-room-gpp: $(ROOMSOURCES) $(HSOURCES)
	$(GPP) $(ROOMSOURCES) test_room.cpp -o $(OUTPUT)
	# To execute the program, run: ./output

# $ make test-room-clang
test-room-clang: $(ROOMSOURCES) $(HSOURCES)
	$(CLANG) $(ROOMSOURCES) test_room.cpp -o $(OUTPUT)
	# To execute the program, run: ./output

# $ make test-laby-gpp
test-laby-gpp: $(ROOMSOURCES) $(LABYRINTHSOURCES) $(HSOURCES)
	$(GPP) $(CFLAGS) $(ROOMSOURCES) $(LABYRINTHSOURCES) test_laby.cpp -o $(OUTPUT)
	# To execute the program, run: ./output

# $ make test-laby-clang
test-laby-clang: $(ROOMSOURCES) $(LABYRINTHSOURCES) $(HSOURCES)
	$(CLANG) $(CFLAGS) $(ROOMSOURCES) $(LABYRINTHSOURCES) test_laby.cpp -o $(OUTPUT)
	# To execute the program, run: ./output

# $ make test-labymap-gpp
test-labymap-gpp: $(ROOMSOURCES) $(LABYRINTHSOURCES) $(HSOURCES)
	$(GPP) $(ROOMSOURCES) $(LABYRINTHSOURCES) test_labymap.cpp -o $(OUTPUT)
	# To execute the program, run: ./output

# $ make test-labymap-clang
test-labymap-clang: $(ROOMSOURCES) $(LABYRINTHSOURCES) $(HSOURCES)
	$(CLANG) $(ROOMSOURCES) $(LABYRINTHSOURCES) test_labymap.cpp -o $(OUTPUT)
	# To execute the program, run: ./output

# $ make test-compile
test-compile: $(ROOMSOURCES) $(LABYRINTHSOURCES) $(HSOURCES)
	make test-room-gpp
	make test-room-clang
	make test-laby-gpp
	make test-laby-clang
	make test-labymap-gpp
	make test-labymap-clang
	make clean

# $ make clean
# Removes created files
clean:
	rm -f $(OUTPUT) *.o *~

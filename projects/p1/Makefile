CXX = g++ # variables and initialization
CXXFLAGS = -std=c++11 -g -Wall -MMD # builds dependency lists in .d files
OBJECTS = card.o command.o player.o computerplayer.o humanplayer.o model.o view.o controller.o main.o
DEPENDS = ${OBJECTS:.o=.d} # substitute ".o" with ".d"
EXEC = bin/program

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS} # reads the .d files and reruns dependencies

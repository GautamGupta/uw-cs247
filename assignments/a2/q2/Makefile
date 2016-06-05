CXX = g++ # variables and initialization
CXXFLAGS = -g -Wall -MMD # builds dependency lists in .d files
OBJECTS = GraphTestHarness.o BCode.o Building.o Collection.o Graph.o
DEPENDS = ${OBJECTS:.o=.d} # substitute ".o" with ".d"
EXEC = prog_q2

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS} # reads the .d files and reruns dependencies

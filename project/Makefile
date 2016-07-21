CXX = g++
CXXFLAGS = -std=c++11 -g -Wall -MMD `pkg-config gtkmm-3.0 --cflags` # builds dependency lists in .d files
LDFLAGS = `pkg-config gtkmm-3.0 --libs`
OBJECTS = subject.o DeckGUI.o card.o player.o computerplayer.o humanplayer.o model.o view.o controller.o cardview.o playerview.o main.o
DEPENDS = ${OBJECTS:.o=.d} # substitute ".o" with ".d"
EXEC = straights

${EXEC} : ${OBJECTS}
	${CXX} ${OBJECTS} ${CXXFLAGS} $(LDFLAGS) -o ${EXEC}

clean:
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}

zip:
	zip -o ${EXEC}.zip *.h *.cpp Makefile bonus.txt img/*

-include ${DEPENDS} # reads the .d files and reruns dependencies

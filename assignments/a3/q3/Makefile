CXX = g++
CXXFLAGS= -O -Wall -std=c++11 -MMD # -nostdinc++ -I/usr/include/c++/v1 -nodefaultlibs
LDFLAGS = -lc++ -lc++abi -lm -lc # -lgcc_s -lgcc
OBJECTS = hangman.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = hangman

$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJECTS) $(LDFLAGS)

clean:
	rm -f *.o $(EXEC) $(TESTS) $(DEPENDS)

-include ${DEPENDS}


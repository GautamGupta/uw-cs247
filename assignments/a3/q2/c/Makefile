CXX = g++
CXXFLAGS= -O -Wall -std=c++11 -MMD -nostdinc++ -I/usr/include/c++/v1 -nodefaultlibs
LDFLAGS = -lc++ -lc++abi -lm -lc -lgcc_s -lgcc
OBJECTS = MenuComponent.o MenuItem.o Menu.o ComponentIterator.o main.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = menu

$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJECTS) $(LDFLAGS)

clean:
	rm -f *.o $(EXEC) $(TESTS) $(DEPENDS)

zip:
	zip -FS -o STL_c.zip main.cpp MenuComponent.o MenuItem.o Menu.o ComponentIterator.o *.h Makefile

-include ${DEPENDS}


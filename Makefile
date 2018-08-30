CPPFLAGS = -std=c++11 -Wall

# Default rule for make should make images2geometry
all: images2geometry

# Creating the executable
images2geometry: src/images2geometry.o src/Geometry.o src/IntVector3.o
	g++ -o images2geometry src/images2geometry.o src/Geometry.o src/IntVector3.o


# Creating object files
images2geometry.o: src/images2geometry.cpp src/Geometry.h src/SetList.h src/IntVector3.h
	g++ $(CPPFLAGS) -c src/images2geometry.cpp

Geometry.o: src/Geometry.cpp src/Geometry.h src/SetList.h src/IntVector3.h
	g++ $(CPPFLAGS) -c src/Geometry.cpp

IntVector3.o: src/IntVector3.cpp src/IntVector3.h
	g++ $(CPPFLAGS) -c src/IntVector3.cpp


clean:
	rm -f src/*.o images2geometry


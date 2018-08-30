CPPFLAGS = -std=c++11 -Wall

# Default rule for make should make images2geo
all: images2geo

# Creating the executable
images2geo: src/images2geo.o src/Geometry.o src/IntVector3.o
	g++ -o images2geo src/images2geo.o src/Geometry.o src/IntVector3.o


# Creating object files
images2geo.o: src/images2geo.cpp src/Geometry.h src/SetList.h src/IntVector3.h
	g++ $(CPPFLAGS) -c src/images2geo.cpp

Geometry.o: src/Geometry.cpp src/Geometry.h src/SetList.h src/IntVector3.h
	g++ $(CPPFLAGS) -c src/Geometry.cpp

IntVector3.o: src/IntVector3.cpp src/IntVector3.h
	g++ $(CPPFLAGS) -c src/IntVector3.cpp


clean:
	rm -f src/*.o images2geo


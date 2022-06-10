CXX = g++ 
CXXFLAGS = -std=c++11 -w -g -pthread

Cache: main.o Cache.o MainMemory.o Manager.o ReaderCreator.o WriterCreator.o Util.o
	$(CXX) $(CXXFLAGS) -o Cache main.o Cache.o MainMemory.o Manager.o ReaderCreator.o WriterCreator.o Util.o

main.o: main.cpp Cache.h MainMemory.h Manager.h ReaderCreator.h WriterCreator.h Util.h
	$(CXX) $(CXXFLAGS) -c main.cpp

ReaderCreator.o: ReaderCreator.cpp Manager.h Util.h
	$(CXX) $(CXXFLAGS) -c ReaderCreator.cpp

WriterCreator.o: WriterCreator.cpp Manager.h Util.h
	$(CXX) $(CXXFLAGS) -c WriterCreator.cpp

Manager.o: Manager.cpp Util.h
	$(CXX) $(CXXFLAGS) -c Manager.cpp

MainMemory.o: MainMemory.cpp Util.h
	$(CXX) $(CXXFLAGS) -c MainMemory.cpp

Cache.o: Cache.cpp Util.h
	$(CXX) $(CXXFLAGS) -c Cache.cpp

Util.o: Util.cpp 
	$(CXX) $(CXXFLAGS) -c Util.cpp

clean: 
	-rm Cache *.o

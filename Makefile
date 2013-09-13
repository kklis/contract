all:
	$(CXX) -Wall -O2 -o example example.cpp

release:
	$(CXX) -Wall -DNDEBUG -O2 -o example example.cpp

clean:
	rm -rf example example.exe

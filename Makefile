all:
	$(CXX) -Wall -O2 -o example example.cpp

clean:
	rm -rf example example.exe

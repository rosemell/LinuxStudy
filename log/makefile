.PHONY:clean
test.exe:log.hpp test.cpp 
	g++ -o $@  $^ -g -std=c++11

clean:
	rm test.exe
allclean:
	rm -rf log
	rm test.exe

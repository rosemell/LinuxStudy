.PHONY:clean
.PHONY:all
all:client service


client:client.cpp
	g++ -o $@  $^ -g -std=c++11
service:service.cpp
	g++ -o $@  $^ -g -std=c++11
clean:
	rm client
	rm service 

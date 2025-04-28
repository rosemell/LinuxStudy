.PHONY:test
test:clean all



.PHONY:all
all:udpserver udpclient

udpclient:UdpClient.cpp
	g++ -o $@ $^ -std=c++11

udpserver:UdpServer.cpp
	g++ -o $@ $^ -std=c++11

.PHONY:clean
clean:
	rm -f udpserver udpclient
.PHONY:test
test:clean all

.PHONY:all
all:tcpserverd tcpclient

tcpclient:TcpClient.cpp
	g++ -o $@ $^ -std=c++11
tcpserverd:TcpServer.cpp Log.cpp
	g++ -o $@ $^ -std=c++11 -lpthread

.PHONY:clean
clean:
	rm -f tcpserverd tcpclient

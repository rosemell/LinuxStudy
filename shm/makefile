.PHONY:clean remake all
all:service.exe client.exe
service.exe:service.cpp
	g++ -std=c++11 -o $@ $^ 
client.exe:client.cpp
	g++ -std=c++11 -o $@ $^ 
clean:
	-rm service.exe
	-rm client.exe
remake:clean
	  #忽视报错，否则a.out文件不存在，rm报错，会导致remake中断，make不执行
	make
test:clean

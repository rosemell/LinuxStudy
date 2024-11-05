.PHONY:clean remake
test:test.c mystdio.c
	gcc -o $@ $^ 
clean:
	-rm test
remake:clean
	 #忽视报错，否则a.out文件不存在，rm报错，会导致remake中断，make不执行
	make

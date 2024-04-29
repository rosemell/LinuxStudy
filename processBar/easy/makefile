processBar:main.c processBar.c
	gcc -o $@ $^
# $@ 代表依赖关系左侧的文件，$^代表依赖关系右侧的文件

.PHONY:clean
clean:
	rm -f processBar
.PHONY:regcc
re:
	make clean;
	make;

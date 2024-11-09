source.txt:
	echo "this is the source" > source.txt
result.txt:source.txt
	cp source.txt result.txt
var-lost:
	export foo=bar;echo "foo=[$$foo]"
test:
	@#zheshshh
clean:
	rm *.txt
complire:
	%.o:%.c
txt=hello world
test1:
	@echo $(txt)
test2:
	@echo $$HOME
compirec:
	$(CC) -o hello hello.c 

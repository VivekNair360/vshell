CC=gcc
headers=./headers
sources=./source
execs=../exes

vshell: $(sources)/main.c $(sources)/prompt.c
	$(CC) -o vshell $(sources)/main.c $(sources)/prompt.c
	mkdir -p $(execs)
	mv vshell $(execs)/

clean: $(execs)
	rm -r $(execs)
	mkdir $(execs)
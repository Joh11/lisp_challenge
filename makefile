lispexec: main.o core.o init.o terminate.o prettify.o parse.o
	$(CC) -o $@ $^

main.o: main.c
core.o: core.c
init.o: init.c
terminate.o: terminate.c
prettify.o: prettify.c
parse.o: parse.c


# Cleaning stuff
clean:
	rm -f *.o lispexec 

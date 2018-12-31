
lispexec: main.o
	$(CC) -o $@ $^

main.o: main.c



# Cleaning stuff
clean:
	rm -f *.o lispexec 

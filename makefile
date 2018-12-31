CCFLAGS = -g

lispexec: main.o core.o init.o terminate.o prettify.o parse.o eval.o
	$(CC) $(CCFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CCFLAGS) -c $< -o $@

# Cleaning stuff
clean:
	rm -f *.o lispexec 

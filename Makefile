SDL2_FLAGS=$(shell sdl2-config --cflags --libs)
PROG=sdl2test
REMOTE="bromremote"

compile:
	 gcc $(SDL2_FLAGS) -o $(PROG) $(PROG).c

clean:
	if [ -a $(PROG) ]; then rm $(PROG); fi;

deploy: clean compile
	scp $(PROG).c $(REMOTE):

test: clean compile
	sudo ./$(PROG)

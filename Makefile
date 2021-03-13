CC=cc
BINS=*.o
LIBS=-lxcb
FLAGS=-Wall -Wextra -Wpedantic

LIBNAME=libRK.so

all: sharedMinimal

sharedMinimal:
	$(CC) $(FLAGS) -fPIC -c src/*.c $(LIBS)
	
	$(CC) $(FLAGS) -shared -fPIC $(BINS) -o $(LIBNAME) $(LIBS)

shared:
	$(CC) $(FLAGS) -fPIC -O2 -c src/*.c $(LIBS)
	
	$(CC) $(FLAGS) -shared -fPIC -O2 $(BINS) -o $(LIBNAME) $(LIBS)
	strip --strip-all $(LIBNAME)

clean:
	rm *.o *.so
clear:
	rm *.o *.so

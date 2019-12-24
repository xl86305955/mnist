CC := gcc
CFLAGS := -lm -g 
OBJECT := main.c common.h mnist.h init_network.h activation.h forward.h backward.h loss.h

all:test

test: $(OBJECT)
	$(CC) $(CFLAGS) -o test $(OBJECT)

loss.o: loss.c common.h
	$(CC) -c loss.c

backward.o: backward.c common.h activation.h
	$(CC) -c backward.c

forward.o: forward.c common.h activation.h
	$(CC) -c forward.c

init_network.o: init_network.c common.h
	$(CC) -c init_network.c

activation.o: activation.c common.h
	$(CC) -c activation.c

.PHONY:clean
clean:
	rm test

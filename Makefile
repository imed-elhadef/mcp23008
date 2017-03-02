# Copyright (C) Imed Elhadef 2017
# No rights reserved
# You may treat this program as if it was in the public domain
#
#

CC=gcc
CFLAGS=-I.
DEPS = mcp23008.h
OBJ = demo.o  mcp23008.o i2c_bus.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

demo: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

clean :
	rm *.o demo

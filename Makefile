CC      = gcc
CFLAGS  = -g
RM      = rm -f

default: all

all: pIDpName 
pIDpName: pIDpName.c
	$(CC) $(CFLAGS) -o pIDpName pIDpName.c

clean veryclean:
	$(RM) pIDpName

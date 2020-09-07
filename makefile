TARGET = textRPG
VPATH = sources
OBJS = main.o
CPPFLAGS = -std=c++2a

all: ${TARGET}

${TARGET}: ${OBJS}
	c++ -o $@ ${OBJS}

main.o:

.PHONY: do clean menu

do: 
	@./${TARGET}

clean: 
	rm ${OBJS}

help:
	@./helpSort
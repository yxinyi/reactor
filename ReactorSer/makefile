SOURCES=$(wildcard *.cpp)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))
CC=g++ -std=c++11
PROGRAM=../reactorSer
CFLAGS= -I../src -L. 

$(PROGRAM) : $(OBJECTS)
	$(CC) -o $(PROGRAM) $(OBJECTS) $(CFLAGS)
$(OBJECTS):$(SOURCES)

.PHONY : clean
clean :
	rm -rf $(OBJECTS) $(USE_EVENT_PROGRAM) $(USE_COND_PROGRAM)

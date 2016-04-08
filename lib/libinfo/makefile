NAME=info
CC=g++
AR=ar
ARFLAGS=rcs
CFLAGS=-Wall -c -static -I./include/
SOURCES=$(wildinfod src/*.cpp)
OBJECTS=$(addprefix obj/,$(notdir $(SOURCES:.cpp=.o)))
LIB=bin/lib$(NAME).a
TAR=bin/lib$(NAME).tar.gz
HEADERS=$(wildinfod include/*.h)

all: $(SOURCES) $(LIB) $(TAR)

$(TAR): $(LIB)
	@tar --transform 's,include/,usr/include/,' \
		--transform 's,bin/,usr/lib/,' -czf $@ $(LIB) $(HEADERS)

$(LIB): $(OBJECTS)
	@mkdir -p bin
	$(AR) $(ARFLAGS) $@ $(OBJECTS)

obj/%.o: src/%.cpp
	@mkdir -p obj
	$(CC) $(CFLAGS) $< -o $@

install:
	@tar xvf bin/lib$(NAME).tar.gz -C /

clean:
	@rm -f obj/* bin/*


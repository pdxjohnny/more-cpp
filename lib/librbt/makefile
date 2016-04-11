CC=g++
RBT_SOURCES=$(wildcard src/*.cpp)
CFLAGS=-Wall -c -static -I./src/
LDFLAGS=$(RBT_SOURCES)
# Build the test suite
TEST_SOURCES=$(wildcard test/*.cpp)
TEST_OBJECTS=$(addprefix obj/test/,$(notdir $(TEST_SOURCES:.cpp=.o)))
TEST=bin/rbt-test

all: $(TEST_SOURCES) $(TEST)

$(TEST): $(TEST_OBJECTS)
	@mkdir -p bin
	$(CC) $(LDFLAGS) $(TEST_OBJECTS) -o $@

obj/test/%.o: test/%.cpp
	@mkdir -p obj/test
	$(CC) $(CFLAGS) $< -o $@

clean:
	@rm -rf obj/* bin/*


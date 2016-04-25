NAME=cards
# Libs in use
LIB_NAMES=$(notdir $(wildcard deps/*))
LIB_HEADERS=$(addprefix -I./deps/,$(addsuffix /include/,$(LIB_NAMES)))
LIBS=$(addprefix ./deps/,$(join $(addsuffix /bin/,$(LIB_NAMES)),$(addsuffix .a,$(LIB_NAMES))))
LIB_NAMES_CLEAN=$(addprefix ./clean/,$(LIB_NAMES))
# Compiler settings
CC=g++
CFLAGS=-g -fPIC -Wall -c -I./include/ $(LIB_HEADERS)
LDFLAGS=
# Build the lib
CLI_SOURCES=$(wildcard src/*.cpp)
CLI_OBJECTS=$(addprefix obj/cli/,$(notdir $(CLI_SOURCES:.cpp=.o)))
CLI=bin/$(NAME)
TAR=bin/$(NAME).tar.gz
# Build the tests
LIB_NAMES_TEST=$(addprefix ./test/,$(LIB_NAMES))
TEST_SOURCES=$(wildcard test/*.cpp)
TEST_OBJECTS=$(addprefix obj/test/,$(notdir $(TEST_SOURCES:.cpp=.o)))
TEST=bin/$(NAME)-test

all: $(LIB_NAMES) $(CLI_SOURCES) $(CLI) $(TEST_SOURCES) $(TEST)

$(LIB_NAMES):
	@# Make them all
	@$(foreach dep,$(addprefix ./deps/,$@),$(MAKE) -C $(dep))
	@# Extract them into their own obj directory so that they can be compiled
	@# into the archive for this library. Or else anything using this library
	@# also has to link to all of its dependencies
	@$(foreach dep,$(addprefix ./obj/deps/,$@),mkdir -p $(dep))
	@# Copy the archives in under the obj folder
	@$(foreach dep,$@, \
		cp \
			$(addprefix ./deps/,$(join $(addsuffix /bin/,$(dep)),$(addsuffix .a,$(dep)))) \
			$(addprefix ./obj/deps/,$(addsuffix /, $(dep))) \
	)
	@# Extract the archives rename them to have the archives name and delete
	@# the copy of the archive we copyied in
	@$(foreach dep,$@, \
		cd $(addprefix ./obj/deps/, $(dep)) && \
		$(AR) x $(addsuffix .a, $(dep)) && \
		rm $(addsuffix .a, $(dep)) && \
		for file in `ls`; do mv $$file ../$(dep)_$$file; done && \
		cd .. && \
		rm -rf $(dep) \
	)

$(CLI): $(CLI_OBJECTS)
	@mkdir -p bin
	$(CC) $(CLI_OBJECTS) $(LIBS) $(LDFLAGS) -o $@

tar:
	@tar --transform 's,^/,cards,' --dereference --exclude='*/bin/*' \
		--exclude='*/obj/*' -czf $@ .

obj/cli/%.o: src/%.cpp
	@mkdir -p obj/cli
	$(CC) $(CFLAGS) $< -o $@

# Build tests
$(TEST): $(TEST_OBJECTS) $(LIB)
	@mkdir -p bin
	$(CC) $(TEST_OBJECTS) $(LIBS) $(LIB) $(LDFLAGS) -o $@

obj/test/%.o: test/%.cpp
	@mkdir -p obj/test
	$(CC) $(CFLAGS) $< -o $@

.PHONY: test
test: $(LIB_NAMES_TEST)
	@echo Running tests for $(NAME)
	@$(TEST)

$(LIB_NAMES_TEST):
	@$(foreach dep,$(addprefix ./deps/,$(notdir ,$@)),$(MAKE) -C $(dep) test)

install:
	@tar xvf bin/lib$(NAME).tar.gz -C /

clean: $(LIB_NAMES_CLEAN)
	@rm -rf obj/* bin/*

$(LIB_NAMES_CLEAN):
	@$(foreach dep,$(addprefix ./deps/,$(notdir ,$@)),$(MAKE) -C $(dep) clean)


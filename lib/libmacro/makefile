NAME=macro
# Libs in use
LIB_NAMES=$(notdir $(wildcard deps/*))
LIB_HEADERS=$(addprefix -I./deps/,$(addsuffix /include/,$(LIB_NAMES)))
LIBS=$(addprefix ./deps/,$(join $(addsuffix /bin/,$(LIB_NAMES)),$(addsuffix .a,$(LIB_NAMES))))
LIB_NAMES_CLEAN=$(addprefix ./clean/,$(LIB_NAMES))
# Compiler settings
CC=g++
AR=ar
ARFLAGS=rcs
CFLAGS=-fPIC -Wall -c -I./include/ $(LIB_HEADERS)
# Build the lib
LIB_SOURCES=$(wildcard src/*.cpp)
LIB_OBJECTS=$(addprefix obj/lib/,$(notdir $(LIB_SOURCES:.cpp=.o)))
LIB=bin/lib$(NAME).a
TAR=bin/lib$(NAME).tar.gz
HEADERS=$(wildcard include/*.h)

all: $(LIB_NAMES) $(LIB_SOURCES) $(LIB)

$(LIB_NAMES):
	@$(foreach dep,$(addprefix ./deps/,$@),$(MAKE) -C $(dep))

tar: $(LIB)
	@tar --transform 's,include/,usr/include/,' \
		--transform 's,bin/,usr/lib/,' -czf $(TAR) $(LIB) $(HEADERS)

# Build the lib
$(LIB): $(LIB_OBJECTS) $(LIB_NAMES)
	@mkdir -p bin
	$(AR) $(ARFLAGS) $@ $(LIB_OBJECTS)

obj/lib/%.o: src/%.cpp
	@mkdir -p obj/lib
	$(CC) $(CFLAGS) $< -o $@

.PHONY: test
test:
	@echo No tests for $(NAME)

install:
	@tar xvf bin/lib$(NAME).tar.gz -C /

clean: $(LIB_NAMES_CLEAN)
	@rm -rf obj/* bin/*

$(LIB_NAMES_CLEAN):
	@$(foreach dep,$(addprefix ./deps/,$(notdir ,$@)),$(MAKE) -C $(dep) clean)


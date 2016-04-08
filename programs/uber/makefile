NAME=uber
# Libs in use
LIB_NAMES=libinfo libtransport
LIB_HEADERS=$(addprefix -I./deps/,$(addsuffix /include/,$(LIB_NAMES)))
LIBS=$(addprefix ./deps/,$(join $(addsuffix /bin/,$(LIB_NAMES)),$(addsuffix .a,$(LIB_NAMES))))
LIB_NAMES_CLEAN=$(addprefix ./clean/,$(LIB_NAMES))
# Compiler settings
CC=g++
CFLAGS=-Wall -c -static $(LIB_HEADERS)
LDFLAGS=
SOURCES=$(wildcard src/*.cpp)
OBJECTS=$(addprefix obj/cli/,$(notdir $(SOURCES:.cpp=.o)))
CLI=bin/$(NAME)
TAR=bin/$(NAME).tar.gz

all: $(LIB_NAMES) $(SOURCES) $(CLI)

$(LIB_NAMES):
	@$(foreach dep,$(addprefix ./deps/,$@),$(MAKE) -C $(dep))

$(CLI): $(OBJECTS)
	@mkdir -p bin
	$(CC) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $@

$(TAR):
	@tar --transform 's,^/,uber,' --dereference --exclude='*/bin/*' \
		--exclude='*/obj/*' -czf $@ .

obj/cli/%.o: src/%.cpp
	@mkdir -p obj/cli
	$(CC) $(CFLAGS) $< -o $@

clean: $(LIB_NAMES_CLEAN)
	@rm -rf obj/* bin/*

$(LIB_NAMES_CLEAN):
	@$(foreach dep,$(addprefix ./deps/,$(notdir ,$@)),$(MAKE) -C $(dep) clean)


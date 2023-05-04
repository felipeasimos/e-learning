COMPILER :=clang
SRC :=display.c
TARGET :=display

FLAGS :=-std=c99 -pedantic-errors -Wall -Wextra -fPIC -Werror
DEBUG_FLAGS :=-DDEBUG -O0 -g
RELEASE_FLAGS :=-O3 -DNDEBUG

RUN_COMMAND :=./$(TARGET) figure.ppm

$(TARGET): $(SRC)
	$(COMPILER) $(FLAGS) $^ -o $@

debug: FLAGS+=$(DEBUG_FLAGS)
debug: $(TARGET)
	valgrind --quiet --leak-check=full --exit-on-first-error=yes --error-exitcode=1 --quiet $(RUN_COMMAND)

build: clean
build: FLAGS+=$(RELEASE_FLAGS)
build: $(TARGET)

run: build
	$(RUN_COMMAND)

clean:
	@-rm $(TARGET)

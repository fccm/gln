CC := gcc -g
CC_OPT := -pedantic -Wall \
  -Wstrict-prototypes -Wnested-externs -Wmissing-prototypes \
  -Wno-overlength-strings -Wdeclaration-after-statement

CXXLIBS := -lsfml-graphics -lsfml-system -lsfml-window -lsfml-audio
CLIBS := -lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio
GL_LIB := -lGL
GLU_LIB := -lGLU
GL_LIBS := $(GL_LIB) $(GLU_LIB)
SFML_LIBS := $(CXXLIBS) $(CLIBS)

LIB_SFML_BASEDIR := /tmp/sfml/SFML-1.6

INC_PATH := -I$(LIB_SFML_BASEDIR)/CSFML/include/
CXXLD_PATH := -L$(LIB_SFML_BASEDIR)/lib/
CLD_PATH := -L$(LIB_SFML_BASEDIR)/CSFML/lib/
LD_PATH := $(CXXLD_PATH) $(CLD_PATH)

TEST_FILE := test_simple.c
TEST_RAD := $(shell basename $(TEST_FILE) .c)

.PHONY: all
all: $(TEST_RAD).exe

$(TEST_RAD).o: $(TEST_RAD).c
	$(CC) -c -I../src $(INC_PATH) $<

$(TEST_RAD).exe: $(TEST_RAD).o
	$(CC) -o $@ $(LD_PATH) $(SFML_LIBS) $(GL_LIBS) -L../src -lgln $<

.PHONY: clean
clean:
	$(RM) *.o *.so* *.exe


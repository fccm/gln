CC = gcc -g
CC_OPT = -pedantic -Wall \
  -Wstrict-prototypes -Wnested-externs -Wmissing-prototypes \
  -Wno-overlength-strings -Wdeclaration-after-statement

SRC_FILES = gln.c gln_shaders.c
OBJ = $(patsubst %.c, %.o, $(SRC_FILES))

GL_LIB = -lGL

CFLAGS = -fPIC  -DDO_FORWARD_COMPATIBLE
LIBVER = 0.0

all lib: libgln.so
obj: $(OBJ)

gln_shaders.o: gln_shaders.c gln_shaders_120.h gln_shaders_130.h
	$(CC) $(CC_OPT) -c $(CFLAGS) $<

gln.o: gln.c gln_intern.h gln.h
	$(CC) $(CC_OPT) -c $(CFLAGS) $<

libgln.so.$(LIBVER): $(OBJ)
	$(CC) -shared -Wl,-soname,$@ -lm $(GL_LIB) -o $@ $^

libgln.so: libgln.so.$(LIBVER)
	ln -sf $< $@

clean:
	rm -f *.o *.so*

.PHONY: clean all lib obj

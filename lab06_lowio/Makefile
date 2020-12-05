objects = funcs_var3.o
d_objects = dfuncs_var3.o

all: libstatic.a libshared.so teststatic.out testshared.out clean

teststatic.out: var3.o libstatic.a
	gcc -o $@ var3.o -L. -lstatic -lm

testshared.out: var3.o libshared.so
	gcc -o $@ var3.o -L$(PWD) -lshared -lm -Wl,-rpath,$(PWD)

libshared.so: $(d_objects)
	gcc -shared $^ -o $@

$(d_objects): d%.o: %.c
	gcc -fpic -c $< -o $@

libstatic.a: $(objects)
	ar -r $@ $^

$(objects): %.o: %.c
	gcc -o $@ -c $<

clean:
	rm -rf *.o

.PHONY: all clean

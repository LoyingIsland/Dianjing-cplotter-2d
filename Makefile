CC=g++
IDIR=.
CFLAGS=-I$(IDIR) -O2

DEPS = \
	common.h \
	lodepng.h

LIBS=-lm -lboost_program_options
OBJ=lodepng.o plotter.o djplotter.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

djplotter: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f *.o *~ djplotter
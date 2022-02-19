CC=gcc
CFLAGS=-O2

DEPS = pgm.h effects.h

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

all: pgm_median pgm_effect

pgm_effect: pgm.o effects.o effects_main.o
	$(CC) $(CFLAGS) -o $@ $^
	
pgm_median: pgm.o median_main.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf *.o pgm_effect pgm_median */filtered* */*_binarize* */*_noise* */*_invert* */*_smooth* */*_solarize*

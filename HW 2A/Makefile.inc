
.SUFFIXES: .0 .3 .pg .g .pg3 .pca

CC=gcc

PROGS_PG3 = ${PROGS:=.pg3}
PROGS_PG = ${PROGS:=.pg}
PROGS_G = ${PROGS:=.g}
PROGS_0 = ${PROGS:=.0}
PROGS_3 = ${PROGS:=.3}
PROGS_PCA = ${PROGS:=.pca}
PROGS_ALL = ${PROGS} ${PROGS_PG} ${PROGS_0} ${PROGS_3} ${PROGS_G} ${PROGS_PG3} ${PROGS_PCA}

all: ${PROGS_ALL}

zip: 
	dir=`basename $(PWD)`; cd .. ; zip -r $$dir $$dir

.c.0:
	$(CC) $(CFLAGS) $< -O0 $(LDLIBS) -o $@

.c.3:
	$(CC) $(CFLAGS) $< -O3 $(LDLIBS) -o $@

.c.pg:
	$(CC) $(CFLAGS) $< -pg -g -static $(LDLIBS) -o $@

.c.pg3:
	$(CC) $(CFLAGS) $< -pg -g -O3 -static $(LDLIBS) -o $@

.c.g:
	$(CC) $(CFLAGS) $< -g $(LDLIBS) -o $@

.c.pca:
	$(CC) $(CFLAGS) $< -O3 -march=core2 -mfpmath=sse -ffloat-store -Wl,-s,-O1 -lm  -o $@

clean:
	$(RM) -f $(PROGS_ALL) core.* gmon.out 

cleanall:
	@ for i in */. ; do  cd $$i; ${MAKE} clean; cd .. ; done

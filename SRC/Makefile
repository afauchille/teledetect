
#---------------------------------------------------------
#makefile permettant la compilation du programme principal
#---------------------------------------------------------
.KEEP_STATE:

#definition des variables
CC=gcc
OBJ=../OBJ
EXE=../EXE
CCFLAGS=-Wall -g `pkg-config --cflags gtk+-2.0`
LDFLAGS=`pkg-config --libs gtk+-2.0`

#compilation
OBJ_FILES=compute.o main.o
OBJ_FILES_AUTO=compute.o auto.o

all: ImaProjet.exe

.c.o:
	${CC} ${CCFLAGS} -o $@ -c $<

ImaProjet.exe:${OBJ_FILES}
	${CC} -o ${EXE}/$@ ${OBJ_FILES} ${LDFLAGS}
	mv *.o ${OBJ}

ImaProjet_auto.exe:${OBJ_FILES_AUTO}
	${CC} -o ${EXE}/$@ ${OBJ_FILES_AUTO} ${LDFLAGS}
	mv *.o ${OBJ}

clean:
	\rm -f ${OBJ}/*.o ../*/core ${EXE}/*.exe

install:
	cp *.h ${INC}

.SUFFIXES: .exe .o .c .h

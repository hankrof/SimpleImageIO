CPP = g++
CPPFLAGS = -std=c++14 -g3 -Wall -Werror
OBJ = ../obj
BIN = ../bin
${BIN}/main: ${OBJ}/main.o ${OBJ}/image.o ${OBJ}/bitmap.o ${OBJ}/imageloader.o ${OBJ}/imagewritter.o
	${CPP} ${CPPFLAGS} -o ${BIN}/main ${OBJ}/main.o ${OBJ}/image.o ${OBJ}/bitmap.o ${OBJ}/imageloader.o ${OBJ}/imagewritter.o
${OBJ}/main.o: main.cpp
	${CPP} ${CPPFLAGS} -o ${OBJ}/main.o -c main.cpp
${OBJ}/bitmap.o: bitmap.cpp
	${CPP} ${CPPFLAGS} -o ${OBJ}/bitmap.o -c bitmap.cpp
${OBJ}/image.o: image.cpp
	${CPP} ${CPPFLAGS} -o ${OBJ}/image.o -c image.cpp
${OBJ}/imageloader.o: imageloader.cpp
	${CPP} ${CPPFLAGS} -o ${OBJ}/imageloader.o -c imageloader.cpp
${OBJ}/imagewritter.o: imagewritter.cpp
	${CPP} ${CPPFLAGS} -o ${OBJ}/imagewritter.o -c imagewritter.cpp
clean:
	rm ${BIN}/main ${OBJ}/*.o

CPP = g++
CPPFLAGS = -std=c++14 -g3 
main: main.o image.o bitmap.o imageloader.o imagewritter.o
	${CPP} ${CPPFLAGS} -o main main.o image.o bitmap.o imageloader.o imagewritter.o
main.o: main.cpp
	${CPP} ${CPPFLAGS} -o main.o -c main.cpp
bitmap.o: bitmap.cpp
	${CPP} ${CPPFLAGS} -o bitmap.o -c bitmap.cpp
image.o: image.cpp
	${CPP} ${CPPFLAGS} -o image.o -c image.cpp
imageloader.o: imageloader.cpp
	${CPP} ${CPPFLAGS} -o imageloader.o -c imageloader.cpp
imagewritter.o: imagewritter.cpp
	${CPP} ${CPPFLAGS} -o imagewritter.o -c imagewritter.cpp
clean:
	rm main *.o

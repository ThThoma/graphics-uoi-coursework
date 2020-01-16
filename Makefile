
CC = g++
GCCFLAGS = -fpcc-struct-return
CFLAGS = -g

LDFLAGS = -L/usr/lib
LDLIBS = -lGLU -lGL -lglut

output: vraxaya

vraxaya: interfacetest.o GManager.o GCube.o TextureLoader.o
	$(CC) $(CFLAGS) -o vraxaya interfacetest.o GManager.o GCube.o TextureLoader.o  $(LDLIBS)


interfacetest.o: interfacetest.cpp GManager.h GCube.h
	$(CC) $(CFLAGS) -c interfacetest.cpp $(LDLIBS)

GManager.o: GManager.cpp GManager.h
	$(CC) $(CFLAGS) -c GManager.cpp $(LDLIBS)

GCube.o: GCube.cpp GCube.h
	$(CC) $(CFLAGS) -c GCube.cpp $(LDLIBS)

TextureLoader.o: TextureLoader.cpp TextureLoader.h stb_image.h
	$(CC) $(CFLAGS) -c TextureLoader.cpp $(LDLIBS)


clean: 
	rm *.o vraxaya

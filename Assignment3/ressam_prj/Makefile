CCFLAGS =	-O2 -Wall -I/usr/local/include -I.. -I ../../apclasses  -fmessage-length=0
CC = g++

OBJS =		ressamtopo.o

LIBS = -L/usr/local/lib -lallegro -lallegro_main -lallegro_image -lallegro_primitives -lallegro_font -lallegro_ttf -lallegro_audio -lallegro_acodec -lallegro_dialog



TARGET =	ressamtopo.exe

$(TARGET):	$(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LIBS)


$(OBJS) : ressamtopo.cpp
	$(CC) -c $(CCFLAGS) -o $(OBJS) ressamtopo.cpp

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

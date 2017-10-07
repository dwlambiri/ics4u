CCFLAGS =	-O2 -std=c++11 -Wall -I/usr/local/include -I.. -I ../apclasses  -fmessage-length=0
CC = g++

OBJS =		topography.o

LIBS = -L/usr/local/lib -lallegro -lallegro_main -lallegro_image -lallegro_primitives -lallegro_font -lallegro_ttf -lallegro_audio -lallegro_acodec -lallegro_dialog



TARGET =	topography.exe

$(TARGET):	$(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LIBS)


$(OBJS) : topography.cpp
	$(CC) -c $(CCFLAGS) -o $(OBJS) topography.cpp

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

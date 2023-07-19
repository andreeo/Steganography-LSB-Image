CC = gcc
CFLAFS = -Wall
LDFLAGS =
OBJFILES = main.o steganography.o steganography_util.o
3RDPARTY = 3rdparty/lodepng/lodepng.c
TARGET = stega

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(3RDPARTY) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~
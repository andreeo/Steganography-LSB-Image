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

indent: indent-format clean

indent-format:
	indent *.c \
		-nbad -bap -nbc -bbo -bl -bli0 -bls -ncdb -nce -cp1 -cs -di2 \
		-ndj -nfc1 -nfca -hnl -i2 -ip5 -lp -pcs -nprs -psl -saf -sai \
		-saw -nsc -nsob -nut
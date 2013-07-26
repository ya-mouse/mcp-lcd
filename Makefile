MULTICLET_SDK ?= /home/mouse/Documents/HW/MultiClet/MultiCletSDK

.EXPORT_ALL_VARIABLES:
LCCDIR := $(MULTICLET_SDK)/bin
PATH := ${PATH}:$(LCCDIR)

LCC = mc-lcc
LD = mc-ld

CFLAGS = -Wa--arch=MCp0411100101

OBJ = util.o main.o

OBJ += lcd-ili9320.o

.c.o: $(OBJ)
	$(LCC) -v -target=mcp $(CFLAGS) -I$(MULTICLET_SDK)/include/MCp0411100101 -c $<

all: image.bin

clean:
	rm -f $(OBJ) image.bin image.map

image.bin: $(OBJ)
	$(LD) -o $@ -M -L$(MULTICLET_SDK)/lib/MCp0411100101 -luart $(MULTICLET_SDK)/lib/MCp0411100101/crt0.o $^ > image.map


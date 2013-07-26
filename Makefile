MULTICLET_SDK ?= /home/mouse/Documents/HW/MultiClet/MultiCletSDK

.EXPORT_ALL_VARIABLES:
LCCDIR := $(MULTICLET_SDK)/bin
PATH := ${PATH}:$(LCCDIR)

LCC = mc-lcc
LD = mc-ld

LCCFLAGS  = -v -target=mcp -Wa--arch=MCp0411100101
LCCFLAGS += -I$(MULTICLET_SDK)/include/MCp0411100101

OBJ = util.o main.o

OBJ += lcd-ili9320.o font.o fnt_impact.o img-mc-mono-16.o

.c.o: $(OBJ)
	$(LCC) $(LCCFLAGS) -c $<

all: image.bin

clean:
	rm -f $(OBJ) image.bin image.map

image.bin: $(OBJ)
	$(LD) -o $@ -M -L$(MULTICLET_SDK)/lib/MCp0411100101 -luart $(MULTICLET_SDK)/lib/MCp0411100101/crt0.o $^ > image.map


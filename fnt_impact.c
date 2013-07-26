#include <HDL51001_ccf.h>

#include "font.h"
#include "lcd.h"

static const uint32_t image_data_Impact36_0x22[] = {
    0x1200, 0x927d, 0xf07d, 0xf07d, 0xf07d, 0xf07d, 0xf07d, 0xf07d, 0xf038, 0xe038, 0xe036, 0x0000
};
static const tImage Impact36_0x22 = { image_data_Impact36_0x22, 13, 45};

static const uint32_t image_data_Impact36_0x27[] = {
    0x0900, 0x077c, 0x0238, 0x1b00
};
static const tImage Impact36_0x27 = { image_data_Impact36_0x27, 7, 45};

static const uint32_t image_data_Impact36_0x2d[] = {
    0x2e00, 0x8a7f, 0xc07f, 0xc07f, 0xc07f, 0xc07f, 0xc022, 0x0000
};
static const tImage Impact36_0x2d = { image_data_Impact36_0x2d, 11, 45};

static const uint32_t image_data_Impact36_0x30[] = {
    0x1b00, 0xd303, 0xf000, 0x0ffc, 0x001f, 0xfe00, 0x1fff, 0x003f, 0x1f80, 0x3f1f, 0x803f, 0x1f80, 0x3f1f, 0x803f, 0x1f80, 0x3f1f, 0x803f, 0x1f80, 0x3f1f, 0x803f, 0x1f80, 0x3f1f, 0x803f, 0x1f80, 0x3f1f, 0x803f, 0x1f80, 0x3f1f, 0x803f, 0x1f80, 0x3f1f, 0x803f, 0x1f80, 0x3f1f, 0x803f, 0x1f80, 0x3f1f, 0x801f, 0xff00, 0x1fff, 0x000f, 0xfe00, 0x03f8, 0x1900
};
static const tImage Impact36_0x30 = { image_data_Impact36_0x30, 19, 45};

static const uint32_t image_data_Impact36_0x31[] = {
    0x1300, 0xb7f0, 0x03f0, 0x07f0, 0x1ff0, 0xfff0, 0xfff0, 0xfff0, 0x07f0, 0x03f0, 0x03f0, 0x03f0, 0x03f0, 0x03f0, 0x03f0, 0x03f0, 0x03f0, 0x03f0, 0x03f0, 0x03f0, 0x03f0, 0x03f0, 0x03f0, 0x03f0, 0x03f0, 0x03f0, 0x03f0, 0x03f0, 0x03f0, 0x1000
};
static const tImage Impact36_0x31 = { image_data_Impact36_0x31, 14, 45};

static const uint32_t image_data_Impact36_0x32[] = {
    0x1b00, 0x8c03, 0xf000, 0x0ff8, 0x001f, 0xfc00, 0x1ffe, 0x0002, 0x3f8f, 0x003e, 0x3f00, 0x3e3f, 0x003e, 0x3f00, 0x3e3f, 0x003e, 0x3f02, 0x0081, 0x7f02, 0x0081, 0x7e02, 0x0081, 0xfe02, 0x00ab, 0xfe00, 0x01fc, 0x0001, 0xfc00, 0x03f8, 0x0003, 0xf800, 0x07f0, 0x0007, 0xf000, 0x0fe0, 0x000f, 0xc000, 0x1fc0, 0x001f, 0x8000, 0x3ffe, 0x003f, 0xfe00, 0x3ffe, 0x003f, 0xfe19, 0x0000
};
static const tImage Impact36_0x32 = { image_data_Impact36_0x32, 18, 45};

static const uint32_t image_data_Impact36_0x33[] = {
    0x1b00, 0xac07, 0xf800, 0x0ffe, 0x001f, 0xff00, 0x3fff, 0x003f, 0x9f80, 0x3f9f, 0x803f, 0x9f80, 0x3f9f, 0x803f, 0x9f80, 0x001f, 0x8000, 0x3f00, 0x01ff, 0x0001, 0xfc00, 0x01ff, 0x0001, 0xff02, 0x00a5, 0x3f80, 0x001f, 0x803f, 0x9f80, 0x3f9f, 0x803f, 0x9f80, 0x3f9f, 0x803f, 0x9f80, 0x3f9f, 0x803f, 0x9f80, 0x1fff, 0x001f, 0xff00, 0x0ffe, 0x0003, 0xf819, 0x0000
};
static const tImage Impact36_0x33 = { image_data_Impact36_0x33, 19, 45};

static const uint32_t image_data_Impact36_0x34[] = {
    0x1b00, 0xa101, 0xff00, 0x01ff, 0x0003, 0xff00, 0x03ff, 0x0007, 0xff00, 0x07ff, 0x000f, 0xbf00, 0x0fbf, 0x000f, 0xbf00, 0x1f3f, 0x001f, 0x3f00, 0x023f, 0x9000, 0x3e3f, 0x007e, 0x3f00, 0x7e3f, 0x007c, 0x3f00, 0xfc3f, 0x0002, 0xff81, 0xc002, 0xff81, 0xc002, 0xff81, 0xc002, 0xff81, 0xc002, 0xff81, 0xc002, 0xff83, 0xc000, 0x3f02, 0x0081, 0x3f02, 0x0081, 0x3f02, 0x0081, 0x3f02, 0x0081, 0x3f19, 0x0000
};
static const tImage Impact36_0x34 = { image_data_Impact36_0x34, 18, 45};

static const uint32_t image_data_Impact36_0x35[] = {
    0x1b00, 0x8d3f, 0xff80, 0x3fff, 0x803f, 0xff80, 0x3fff, 0x803f, 0x0200, 0x813f, 0x0200, 0x813f, 0x0200, 0xbe3f, 0x3c00, 0x3fff, 0x003f, 0xff00, 0x3fff, 0x803f, 0x1f80, 0x3f1f, 0x803f, 0x1f80, 0x001f, 0x8000, 0x1f80, 0x001f, 0x803f, 0x1f80, 0x3f1f, 0x803f, 0x1f80, 0x3f1f, 0x803f, 0x1f80, 0x3f1f, 0x803f, 0x1f80, 0x1fff, 0x001f, 0xff00, 0x0ffe, 0x0003, 0xf819, 0x0000
};
static const tImage Impact36_0x35 = { image_data_Impact36_0x35, 19, 45};

static const uint32_t image_data_Impact36_0x36[] = {
    0x1b00, 0x9601, 0xfc00, 0x07ff, 0x000f, 0xff80, 0x1fff, 0x803f, 0x0fc0, 0x3f0f, 0xc03f, 0x0fc0, 0x3f02, 0x0081, 0x3f02, 0x00b8, 0x3f3e, 0x003f, 0xff00, 0x3fff, 0x803f, 0xffc0, 0x3f9f, 0xc03f, 0x0fc0, 0x3f0f, 0xc03f, 0x0fc0, 0x3f0f, 0xc03f, 0x0fc0, 0x3f0f, 0xc03f, 0x0fc0, 0x3f0f, 0xc03f, 0x0fc0, 0x3f9f, 0xc01f, 0xff80, 0x0fff, 0x8007, 0xff00, 0x01fc, 0x1900
};
static const tImage Impact36_0x36 = { image_data_Impact36_0x36, 19, 45};

static const uint32_t image_data_Impact36_0x37[] = {
    0x1200, 0xb7ff, 0xfcff, 0xfcff, 0xfcff, 0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xf801, 0xf801, 0xf801, 0xf803, 0xf003, 0xf003, 0xf003, 0xf007, 0xe007, 0xe007, 0xe007, 0xc00f, 0xc00f, 0xc00f, 0xc01f, 0x801f, 0x801f, 0x801f, 0x803f, 0x003f, 0x1100
};
static const tImage Impact36_0x37 = { image_data_Impact36_0x37, 14, 45};

static const uint32_t image_data_Impact36_0x38[] = {
    0x1b00, 0x9e03, 0xf800, 0x0ffe, 0x001f, 0xff00, 0x1fff, 0x003f, 0x1f80, 0x3f1f, 0x803f, 0x1f80, 0x3f1f, 0x803f, 0x1f80, 0x3f1f, 0x8002, 0x1fb3, 0x801f, 0xff00, 0x0ffc, 0x001f, 0xff00, 0x1fff, 0x003f, 0x1f80, 0x3f1f, 0x803f, 0x1f80, 0x3f1f, 0x803f, 0x1f80, 0x3f1f, 0x803f, 0x1f80, 0x3f1f, 0x803f, 0x1f80, 0x1fff, 0x001f, 0xff00, 0x0ffe, 0x0003, 0xf819, 0x0000
};
static const tImage Impact36_0x38 = { image_data_Impact36_0x38, 19, 45};

static const uint32_t image_data_Impact36_0x39[] = {
    0x1b00, 0xd303, 0xf800, 0x0ffe, 0x001f, 0xff00, 0x1fff, 0x803f, 0x9fc0, 0x3f0f, 0xc03f, 0x0fc0, 0x3f0f, 0xc03f, 0x0fc0, 0x3f0f, 0xc03f, 0x0fc0, 0x3f0f, 0xc03f, 0x0fc0, 0x3f0f, 0xc03f, 0x9fc0, 0x3fff, 0xc01f, 0xffc0, 0x0fff, 0xc007, 0xcfc0, 0x000f, 0xc000, 0x0fc0, 0x3f0f, 0xc03f, 0x0fc0, 0x3f0f, 0xc01f, 0xff80, 0x1fff, 0x000f, 0xfe00, 0x03f8, 0x1900
};
static const tImage Impact36_0x39 = { image_data_Impact36_0x39, 19, 45};

static const uint32_t image_data_Impact36_0xc2b0[] = {
    0x1200, 0x880f, 0x801f, 0xc03f, 0xe078, 0xf006, 0x7088, 0x78f0, 0x3fe0, 0x1fc0, 0x0f80, 0x3200
};
static const tImage Impact36_0xc2b0 = { image_data_Impact36_0xc2b0, 12, 45};


static const tChar Impact36_array[] = {

  // character: '"'
  {0x22, &Impact36_0x22},
  // character: '''
  {0x27, &Impact36_0x27},
  // character: '-'
  {0x2d, &Impact36_0x2d},
  // character: '0'
  {0x30, &Impact36_0x30},
  // character: '1'
  {0x31, &Impact36_0x31},
  // character: '2'
  {0x32, &Impact36_0x32},
  // character: '3'
  {0x33, &Impact36_0x33},
  // character: '4'
  {0x34, &Impact36_0x34},
  // character: '5'
  {0x35, &Impact36_0x35},
  // character: '6'
  {0x36, &Impact36_0x36},
  // character: '7'
  {0x37, &Impact36_0x37},
  // character: '8'
  {0x38, &Impact36_0x38},
  // character: '9'
  {0x39, &Impact36_0x39},
  // character: '°'
  {0xc2b0, &Impact36_0xc2b0}
};


const tFont Impact36 = { 14, Impact36_array };

#include "MicroBit.h"

MicroBit uBit;

static const int BRIGHT=255;

// stuff we should put in a lib
uint8_t* newInvaderBitmap() {
  // cf. https://lancaster-university.github.io/microbit-docs/data-types/image/#storing-images-in-flash-memory

  // why doesn't c++ like me returning a pointer to this ?
 // uint8_t *inv = new uint8_t[50];

  uint8_t* inv = new uint8_t[50] {
    //0xff, 0xff, 10, 0, 5, 0, // the magic
    0, 1, 0, 1, 0, 0, 0, 0, 0, 0, // first line of bitmap
    1, 1, 1, 1, 1, 0, 1, 0, 1, 0,
    1, 1, 1, 1, 1, 0, 1, 1, 1, 0,
    0, 1, 1, 1, 0, 0, 0, 1, 0, 0,
    0, 0, 1, 0, 0, 0, 0, 0, 0, 0
  };

  return inv;
}

// stuff specific to driving this device but abstracted from event handling

void clearDisplay() {
  uBit.display.clear();
}

void drawInvader() {
  uint8_t* b = newInvaderBitmap();

  // TODO: figure out why this is 10x5
  MicroBitImage inv(10, 5, b);
  uBit.display.print(inv);
  delete [] b;
}

// event handling and setup

void onButtonB(MicroBitEvent) {
  drawInvader();
}

void onButtonA(MicroBitEvent) {
  clearDisplay();
}


int main() {
  uBit.init();

  uBit.display.setBrightness(255);
  uBit.display.print("i");

  uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_CLICK, onButtonA);
  uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_BUTTON_EVT_CLICK, onButtonB);

  release_fiber();
}

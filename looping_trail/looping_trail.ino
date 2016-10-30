#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN            6
#define NUMPIXELS      60
#define DELAY          30
#define TRAIL_LENGTH   12

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int trail_indices[TRAIL_LENGTH];
uint32_t trail_colors[TRAIL_LENGTH];
int r = 120;
int g = 30;
int b = 30;

void setup() {
  setup_trail_colors();
  pixels.begin();
  pixels.show();
}

void loop() {
  for (int i = 0; i < NUMPIXELS; i++) {
    set_trail_indices(i, &trail_indices[0]);

    pixels.clear();
    for (int j = 0; j < TRAIL_LENGTH; j++) {
      pixels.setPixelColor(trail_indices[j], trail_colors[j]);
    }
    pixels.show();
    
    delay(DELAY);
  }
}

// set_trail_indices fills `arr` with the indices of 
// the pixels in the trail, looping over the end
void set_trail_indices(int first_index, int *arr) {
  for (int i = 0; i < TRAIL_LENGTH; i++) {
    int index = first_index - i;
    if (index < 0) {
      index = NUMPIXELS + index;
    }
    arr[i] = index;
  }
}

// setup_trail_colors fills the global `trail_colors` to 
// start with the global r,g,b, and fade to black over
// `TRAIL_LENGTH` pixels
void setup_trail_colors() {
  int r_step = r / TRAIL_LENGTH;
  int g_step = g / TRAIL_LENGTH;
  int b_step = b / TRAIL_LENGTH;

  for (int i = 0; i < TRAIL_LENGTH; i++) {
    trail_colors[i] = pixels.Color(r, g, b);
    r = r - r_step;
    g = g - g_step;
    b = b - b_step;
  }
}

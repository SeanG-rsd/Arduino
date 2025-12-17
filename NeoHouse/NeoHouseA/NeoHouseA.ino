#include "neo_hoa.h"

#define DATA_PIN      7  	// this is the data pin connected to the LED strip.  If using WS2801 you also need a clock pin
#define NUM_LIGHTS  200	// change this for the number of LEDs in the strip

// Create an instance of the Adafruit_NeoPixel class called "leds".
// RGB color order, 800 KHz
Adafruit_NeoPixel all_leds = Adafruit_NeoPixel( NUM_LIGHTS, DATA_PIN, NEO_RGB + NEO_KHZ800 );

HOA hoa = HOA();

// void update_houses(Adafruit_NeoPixel* leds, House* houses, int count)
// {
//     leds->clear();
//     int last_house = min(count, FIRST_HOUSE + COUNT_HOUSE);

//     for(int ii=FIRST_HOUSE; ii < last_house; ii++)
//     {
//         houses[ii].update(leds);
//     }

//     leds->show();
// }

void update_hoa(Adafruit_NeoPixel* leds) {
    leds->clear();

    hoa.update(leds);

    leds->show();
}

void update_leds(Adafruit_NeoPixel* leds)
{
    leds->clear();
    static int index = 0;

    index = (index + 1) % NUM_LIGHTS;

#define HOUSE_COLOR CRGB(255, 145, 25)

    leds->setPixelColor(index, HOUSE_COLOR);
    
    leds->show();

    delay(100);
}


void setup_houses(Adafruit_NeoPixel* leds)
{
    leds->begin();
    update_hoa(leds);
}

void setup()
{
    Serial.begin(57600);  // print for debug

    randomSeed(analogRead(A0));

    setup_houses(&all_leds);
}

void loop()
{
    update_hoa(&all_leds);
    //update_leds(&all_leds);
}

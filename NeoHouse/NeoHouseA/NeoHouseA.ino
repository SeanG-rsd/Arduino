#include "neo_hoa.h"

#define DATA_PIN      7  	// this is the data pin connected to the LED strip.  If using WS2801 you also need a clock pin
#define NUM_LIGHTS  200	// change this for the number of LEDs in the strip

#define NUM_HOUSES 26
#define FIRST_HOUSE 0
#define COUNT_HOUSE 26

#define POLICE_HOUSE 22

// Create an instance of the Adafruit_NeoPixel class called "leds".
// RGB color order, 800 KHz
Adafruit_NeoPixel all_leds = Adafruit_NeoPixel( NUM_LIGHTS, DATA_PIN, NEO_RGB + NEO_KHZ800 );

House all_houses[NUM_HOUSES] = { 
    House(  8, 2),
    House( 13, 2),
    House( 19, 2),
    House( 24, 2),
      
    House( 34, 2),  
    House( 39, 2),
    House( 44, 2),  
    House( 50, 2),
    
    House( 64, 1), // lighthoues
    //House( 67, 2),
    House( 71, 2), // winery
    House( 77, 2), // toystore

    House( 88, 2),
    House( 95, 2),
    House(100, 2),

    House(108, 2),
    House(113, 2),
    House(119, 2),
    
    House(130, 2),
    House(138, 2),
    House(144, 2), // gift shop
    
    House(154, 2),
    House(159, 2),
    House(164, 2),
    House(171, 2),

    House(183, 2),
    House(197, 3)
};

HOA hoa = HOA(all_houses, NUM_HOUSES, POLICE_HOUSE);

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

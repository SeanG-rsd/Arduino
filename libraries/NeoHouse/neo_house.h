#pragma once

#include <Adafruit_NeoPixel.h>
#include "nu_range.h"
#include "nu_color.h"
#include "nu_timer.h"

#define HOUSE_COLOR CRGB(255, 145, 25)

#define PARTY_TIME   8000  // 10s of house party time
#define PARTY_RATE    200  // how frequently to change lights during the party
#define PARTY_PROB     20  // probability of starting a party
#define PARTY_COOL  30000  // 30s of house party cooldown (before considering a new party)

#define NUM_PARTY_COLORS 10
static uint32_t PartyColors[NUM_PARTY_COLORS] = 
{
    COLOR_RED,
    COLOR_GREEN,
    COLOR_BLUE,
    COLOR_AQUA,
    COLOR_YELLOW,
    COLOR_ORANGE,
    COLOR_GREEN_DARK,
    COLOR_GREEN_SPRING,
    COLOR_BLUE_ROYAL,
    COLOR_PINK_HOT
};

class House : public NuRange
{
public:
    House(int _start=0, int _count=0, uint32_t _color=HOUSE_COLOR)
        : NuRange(_start, _count)
        , m_color(_color)
        , m_partyMode(false)
    { 
        m_partyTimer.Reset(random(PARTY_COOL));
    }

    void update(Adafruit_NeoPixel* leds)
    {
        if (!m_partyMode)
        {
            // default - just light the houses
            house_lights(leds);

            if (m_partyTimer.IsExpired())
            {
                // roll the dice to see if we should start a party
                auto partyTime = random(100) < PARTY_PROB;
                if (partyTime)
                {
                    m_partyTimer.Reset(random(PARTY_TIME>>1,PARTY_TIME));
                    m_partyMode = true;
                }
                else 
                {
                    m_partyTimer.Reset(random(PARTY_COOL));
                }
            }

            return;
        }

        // Otherwise, we're in 'party-mode'
        if (m_partyTimer.IsExpired())
        {
            // party is over.
            m_partyTimer.Reset(random(PARTY_COOL));
            m_partyMode = false;
        }

        house_party(leds);
    }

private:
    void house_lights(Adafruit_NeoPixel* leds)
    {
        for(int jj=0; jj < m_count; jj++)
        {
            leds->setPixelColor(m_start + jj, m_color);
        }
    }

    void house_party(Adafruit_NeoPixel* leds)
    {
        if (m_partyDelay.IsExpired())
        {
            m_partyDelay.Reset(PARTY_RATE);

            for(int jj=0; jj < m_count; jj++)
            {
                auto c = PartyColors[random(NUM_PARTY_COLORS)];
                leds->setPixelColor(m_start + jj, c);
            }
        }
    }

    uint32_t m_last_color;
    uint32_t m_color;
    bool     m_partyMode;
    NuTimer  m_partyTimer;  
    NuTimer  m_partyDelay;  // delay between 
};


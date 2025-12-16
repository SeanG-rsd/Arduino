#pragma once

#include <Adafruit_NeoPixel.h>
#include "nu_range.h"
#include "nu_color.h"
#include "nu_timer.h"

#define HOUSE_COLOR CRGB(255, 145, 25)

#define PARTY_TIME 8000  // 10s of house party time
#define PARTY_RATE 200   // how frequently to change lights during the party
#define PARTY_PROB 20    // probability of starting a party
#define PARTY_COOL 30000 // 30s of house party cooldown (before considering a new party)

#define POLICE_RATE 400

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
        COLOR_PINK_HOT};

static uint32_t PoliceColors[2] = 
    {
        COLOR_RED,
        COLOR_BLUE
    };

class House : public NuRange
{
public:
    House(int _start = 0, int _count = 0, uint32_t _color = HOUSE_COLOR)
        : NuRange(_start, _count), m_color(_color), m_partyMode(false)
    {
        m_partyTimer.Reset(random(PARTY_COOL));
    }

    void update(Adafruit_NeoPixel *leds)
    {
        if (m_partyMode)
        {
            house_party(leds);
            return;
        }

        if (m_policeMode) {
            police(leds);
        }
        
        // default - just light the houses
        house_lights(leds);
    }

    void setParty(bool partyMode)
    {
        m_partyMode = partyMode;
    }

    void setPolice(bool police)
    {
        m_lastPolice = 0;
        m_policeMode = police;
    }

private:
    void house_lights(Adafruit_NeoPixel *leds)
    {
        for (int jj = 0; jj < m_count; jj++)
        {
            leds->setPixelColor(m_start + jj, m_color);
        }
    }

    void house_party(Adafruit_NeoPixel *leds)
    {
        if (m_partyDelay.IsExpired())
        {
            m_partyDelay.Reset(PARTY_RATE);

            for (int jj = 0; jj < m_count; jj++)
            {
                auto c = PartyColors[random(NUM_PARTY_COLORS)];
                leds->setPixelColor(m_start + jj, c);
            }
        }
    }

    void police(Adafruit_NeoPixel *leds)
    {
        if (m_partyDelay.IsExpired()) 
        {
            m_partyDelay.Reset(POLICE_RATE);

            for (int jj = 0; jj < m_count; jj++)
            {
                auto c = PoliceColors[(++m_lastPolice) % 2];
                leds->setPixelColor(m_start + jj, c);
            }
        }
    }

    uint32_t m_last_color;
    uint32_t m_color;
    int m_lastPolice;
    bool m_partyMode;
    bool m_policeMode;
    NuTimer m_partyTimer;
    NuTimer m_partyDelay; // delay between
};

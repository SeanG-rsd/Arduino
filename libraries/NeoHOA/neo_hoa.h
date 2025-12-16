#pragma once

#include "neo_house.h"

// #define HOUSE_COLOR CRGB(255, 145, 25)

#define PARTY_TIME 8000  // 10s of house party time
#define PARTY_RATE 200   // how frequently to change lights during the party
#define PARTY_PROB 100   // probability of starting a party
#define PARTY_COOL 10000 // 30s of house party cooldown (before considering a new party)

#define NUM_HOUSES 26
#define FIRST_HOUSE 0
#define COUNT_HOUSE 26
#define POLICE_HOUSE 22

class HOA
{
public:
    HOA()
        : m_allHouses{
              House(8, 2),
              House(13, 2),
              House(19, 2),
              House(24, 2),

              House(34, 2),
              House(39, 2),
              House(44, 2),
              House(50, 2),

              House(64, 1), // lighthoues
              // House( 67, 2),
              House(71, 2), // winery
              House(77, 2), // toystore

              House(88, 2),
              House(95, 2),
              House(100, 2),

              House(108, 2),
              House(113, 2),
              House(119, 2),

              House(130, 2),
              House(138, 2),
              House(144, 2), // gift shop

              House(154, 2),
              House(159, 2),
              House(164, 2), // police department
              House(171, 2),

              House(183, 2),
              House(197, 3)}
    {
        m_allHouses[POLICE_HOUSE].setPolice(true);

        m_partyTimer.Reset(random(PARTY_COOL));
    }

    void update(Adafruit_NeoPixel *leds)
    {
        if (m_partyTimer.IsExpired())
        {
            if (!m_partyTime)
            {
                auto partyTime = random(100) < PARTY_PROB;
                if (partyTime)
                {
                    m_partyTimer.Reset(random(PARTY_TIME >> 1, PARTY_TIME));
                    m_partyTime = true;
                    
                    int partyHouse = POLICE_HOUSE;
                    while (partyHouse == POLICE_HOUSE) {
                        partyHouse = random(NUM_HOUSES);
                    }

                    m_partyHouse = partyHouse;
                    m_allHouses[partyHouse].setParty(true);
                }
                else
                {
                    m_partyTimer.Reset(random(PARTY_COOL));
                }
            }
            else
            {
                m_partyTime = false;
                m_allHouses[m_partyHouse].setParty(false);
                m_partyTimer.Reset(random(PARTY_COOL));
            }
        }

        for (int i = 0; i < NUM_HOUSES; i++)
        {
            m_allHouses[i].update(leds);
        }
    }

private:
    House m_allHouses[NUM_HOUSES];
    bool m_partyTime;
    NuTimer m_partyTimer;
    int m_partyHouse;
};
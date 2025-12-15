
 #pragma once

class NuTimer
{
public:
    NuTimer(unsigned int duration = 0) 
    { 
        Reset(duration);
    }

    void Reset()
    {
        m_startTime = millis();
    }

    void Reset(unsigned int duration) 
    {
        m_duration = duration;
        Reset();
    }

    bool IsExpired()
    {
        auto runTime = millis();

        if (runTime > (m_startTime + m_duration))
        {
            return true;
        }

        return false;
    }

private:
    unsigned int m_duration;     // how long this timer lasts
    unsigned int m_startTime;    // current value
}; 
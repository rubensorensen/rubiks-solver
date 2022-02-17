#include "../include/timer.hpp"

void Timer::Start()
{
    m_Start   = { std::chrono::high_resolution_clock::now() };
    m_Running = { true };
}

void Timer::Stop()
{
    m_End     = { std::chrono::high_resolution_clock::now() };
    m_Running = { false };
}

double Timer::Milliseconds()
{
    std::chrono::time_point<std::chrono::high_resolution_clock> end;
    if (m_Running)
    {
        end = { std::chrono::high_resolution_clock::now() };
    }
    else
    {
        end = { m_End };
    }
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - m_Start).count();
}

double Timer::Seconds()
{
    return Milliseconds() / 1000.0f;
}
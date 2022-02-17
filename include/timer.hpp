#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>

class Timer
{
  public:

    Timer()  = default;
    ~Timer() = default;
    void Start();
    void Stop();
    double Milliseconds();
    double Seconds();

  private:

    std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_End;
    bool m_Running{ false };
};

#endif  // TIMER_HPP
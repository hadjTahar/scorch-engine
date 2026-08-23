#ifndef PETRISTOCHASTICGENERATOR_H
#define PETRISTOCHASTICGENERATOR_H
#include <random>
#include <chrono>
#include <iostream>

namespace ptn {

class PetriStochasticGenerator
{
public:
    PetriStochasticGenerator(float rate_per_second)
        : m_ratePerSecond(rate_per_second),
        m_randomEngine(
              static_cast<unsigned int>( std::chrono::high_resolution_clock::now().time_since_epoch().count() ))
    {
        if (rate_per_second < 0) {
            std::cerr << "Warning: Negative rate_per_second is not meaningful. Setting to 0." << std::endl;
            m_ratePerSecond = 0.0f;
        }
    }

    int generate (float delta) {

        float random_value = m_distribution(m_randomEngine);
        float prob_no_event = std::exp(-m_ratePerSecond * delta);
        if (random_value > prob_no_event) {
            return 1;
        } else {
            return 0;
        }
    }


private:
    float m_ratePerSecond; // The average rate of events per second
    std::mt19937 m_randomEngine; // Mersenne Twister pseudo-random number generator
    std::uniform_real_distribution<float> m_distribution{0.0f, 1.0f}; // Distribution

};

}
#endif // PETRISTOCHASTICGENERATOR_H

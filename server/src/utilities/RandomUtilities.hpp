#pragma once
#include <random>

/**
 * @class RandomUtilities
 * @brief Provides static utility functions for generating random values.
 *
 * This class includes methods for generating random numbers within specified ranges,
 * useful for various randomized aspects of the game such as enemy positioning and timing.
 */
class RandomUtilities {
   public:
    /**
     * @brief Generates a random floating-point number between 0 and maxHeight.
     *
     * This function is used to get a random Y-coordinate within the game boundaries,
     * ensuring that entities such as enemies are spawned within the visible area.
     * 
     * @param maxHeight The maximum height (Y-coordinate) that can be generated.
     * @return float A random float value between 0 and maxHeight.
     */
    static float getRandomY(float maxHeight) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0, maxHeight);
        return static_cast<float>(dis(gen));
    }

    /**
     * @brief Generates a random integer representing spawn time in seconds.
     *
     * This function is used to determine the spawn time for enemies, making the
     * gameplay more dynamic and unpredictable.
     * 
     * @param minSeconds The minimum number of seconds for the spawn time.
     * @param maxSeconds The maximum number of seconds for the spawn time.
     * @return int A random integer between minSeconds and maxSeconds.
     */
    static int getRandomSpawnTime(int minSeconds, int maxSeconds) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(minSeconds, maxSeconds);
        return dis(gen);
    }
};

#include "string_lib.hpp"


ObfuscatedString::ObfuscatedString()
{

}

ObfuscatedString::~ObfuscatedString()
{

}

/**
 * @brief       Constexpr implemenatation of ctoi
 * 
 *              All credit goes to Mikhail Klimenko and his article "Constexpr pseudorandom numbers"
 *              https://mklimenko.github.io/english/2018/06/04/constexpr-random/
 *
 * @param[in]   str     String, that shoild be converted to ineger
 * @param[in]   offset  String offset
 *
 * @return      Converted integer
 */
constexpr unsigned int ObfuscatedString::constexpr_ctoi(const char* str, int offset)
{
    return static_cast<std::uint32_t>(str[offset] - '0') * 10 + static_cast<std::uint32_t>(str[offset + 1] - '0');
}

/**
 * @brief       Constexpr implemenatation of creating seed from __TIME__ and __DATE__
 * 
 *              All credit goes to Mikhail Klimenko and his article "Constexpr pseudorandom numbers"
 *              https://mklimenko.github.io/english/2018/06/04/constexpr-random/
 *
 * @return      Seed for pseudorandom generator
 */
constexpr unsigned int ObfuscatedString::constexpr_seed()
{
    auto compile_time = __TIME__;
    auto compile_date = __DATE__;
    return constexpr_ctoi(compile_time, 0) * 60 * 60 + constexpr_ctoi(compile_time, 3) * 60 + constexpr_ctoi(compile_time, 6) + constexpr_ctoi(compile_date, 5) * 24 * 60 * 60;
}

/**
 * @brief       Constexpr uniform distribuion
 *              
 *              Previous value is passed by refeerence due to the lack of static values
 *              
 *              All credit goes to Mikhail Klimenko and his article "Constexpr pseudorandom numbers"
 *              https://mklimenko.github.io/english/2018/06/04/constexpr-random/
 *
 * @param[in]   previous    Previous value
 *
 * @return      Uniformely distributed value in the range of [0, 714025]
 */
constexpr std::uint32_t ObfuscatedString::uniform_distribution(std::uint32_t &previous)
{
    previous = ((lce_a * previous + lce_c) % lce_m);
    return previous;
}

/**
 * @brief       Constexpr normalzed uniform distribuion
 * 
 *              Previous value is passed by refeerence due to the lack of static values
 *              
 *              All credit goes to Mikhail Klimenko and his article "Constexpr pseudorandom numbers"
 *              https://mklimenko.github.io/english/2018/06/04/constexpr-random/
 *
 * @param       previous    Previous value
 *
 * @return      Uniformely distributed value in the range of [0.0, 1.0]
 */
constexpr double ObfuscatedString::uniform_distribution_n(std::uint32_t &previous)
{
    auto distribution = uniform_distribution(previous);
    return static_cast<double>(distribution) / lce_m;
}

/**
 * @brief       Constexpr uniform distribuion as an array
 *              
 *              All credit goes to Mikhail Klimenko and his article "Constexpr pseudorandom numbers"
 *              https://mklimenko.github.io/english/2018/06/04/constexpr-random/
 *
 * @param[in]   min   Minimum distribution value
 * @param[in]   max   Maximum distribution value
 *
 * @tparam      T     Typename of min/max value
 * @tparam      SIZE  Size of normalized uniform distribution
 *
 * @return      std::array of uniformely distributed values in the range of [min, max] 
 */
template <typename T, std::size_t SIZE>
    constexpr std::array<T, SIZE> ObfuscatedString::uniform_distribution(T min, T max)
    {
        std::array<T, SIZE> distribution{};
        auto previous = constexpr_seed();
        for (auto &element : distribution) 
        {
            element = static_cast<T>(uniform_distribution_n(previous) * (max - min) + min);
        }
        
        return distribution;
    }

/**
 * @brief       Constexpr normal distribuion as an array
 *              
 *              Normal distribution is being approximated by the Irwin-Hall distribution
 *
 *              All credit goes to Mikhail Klimenko and his article "Constexpr pseudorandom numbers"
 *              https://mklimenko.github.io/english/2018/06/04/constexpr-random/
 *
 * @param[in]  mean         Irwin-Hall mean
 * @param[in]  sigma        Irwin-Hall sigma
 *
 * @tparam     T            Typename of min/max value
 * @tparam     SIZE         Size of normalized uniform distribution
 * @tparam     IRWIN_NUM    Irwin distribution numbers
 *
 * @return     { description_of_the_return_value }
 */
template <typename T, std::size_t SIZE, std::size_t IRWIN_NUM>
    constexpr std::array<T, SIZE> ObfuscatedString::normal_distribution()
    {
        std::array<T, SIZE> distribution{};
        auto previous = constexpr_seed();
        for (auto &element : distribution) 
        {
            double value = 0;
            for (std::size_t i = 0; i < IRWIN_NUM; ++i)
            {
                value += uniform_distribution_n(previous);
            }

            element = value / std::sqrt(IRWIN_NUM / 12.0f) - IRWIN_NUM / 2.0f;
        }

        return distribution;
    }


/**
 * @brief      Generation of random line with length of n by using uniform distribution
 *
 * @tparam     N     Length of generated line
 *
 * @return     Pseuorandom line with the lenght of N
 */
template<typename T, std::size_t N>
    constexpr const std::unique_ptr<T[]> ObfuscatedString::cgi_r()
    {
        std::unique_ptr<T[]> key = std::make_unique<T[]>(N);

        constexpr auto distribution = uniform_distribution<int, N>(0, 255);

        for (std::size_t i = 0; i < N; ++i) 
        {
            key[i] = distribution.at(i);
        }

        return key;
    }

template const std::unique_ptr<char[]> ObfuscatedString::cgi_r<char, 64>();
template std::array<int, 64> ObfuscatedString::uniform_distribution<int, 64>(int, int);
template std::array<int, 64> ObfuscatedString::normal_distribution<int, 64, 12>();

#undef __CGUI_OBF_KEY__
#undef __CGUI_OBF__
#undef __CGUI_OBF_S__

#define __CGUI_OBF_KEY__ ObfuscatedString::cgi_r<char, 64>()
#define __CGUI_OBF__(data) __CGUI_OBF_GENERIC__(data, __CGUI_OBF_KEY__)
#define __CGUI_OBF_S__(data) __CGUI_OBF_GENERIC__(data, ObfuscatedString::cgi_r<char, 64>())


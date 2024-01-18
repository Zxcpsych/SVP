// bmr_calculator.cpp
#include "bmr_calculator.h"

double BMR::calculateBMR_MifflinSanJeor(int weight, int height, int age, char gender)
{
    double bmr = 0.0;

    if (gender == 'M')
    {
        bmr = 10 * weight + 6.25 * height - 5 * age + 5;
    }
    else if (gender == 'F')
    {
        bmr = 10 * weight + 6.25 * height - 5 * age - 161;
    }

    return bmr;
}

double BMR::calculateBMR_HarrisBenedict(int weight, int height, int age, char gender)
{
    double bmr = 0.0;

    if (gender == 'M')
    {
        bmr = 66 + 13.75 * weight + 5 * height - 6.75 * age;
    }
    else if (gender == 'F')
    {
        bmr = 655 + 9.56 * weight + 1.85 * height - 4.68 * age;
    }

    return bmr;
}

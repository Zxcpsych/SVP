///bmr_calculator.h

#ifndef BMR_CALCULATOR_H
#define BMR_CALCULATOR_H

namespace BMR
{
double calculateBMR_MifflinSanJeor(int weight, int height, int age, char gender);
double calculateBMR_HarrisBenedict(int weight, int height, int age, char gender);
}

#endif // BMR_CALCULATOR_H

//Lucy Joyce 03/12/25

#ifndef CUSTOMFUNCTIONS2_H
#define CUSTOMFUNCTIONS2_H

#include "FiniteFunctions.h"
#include <cmath>
#include <vector>
#include <utility>
#include <string>
#include <random>
#include <filesystem>

namespace fs = std::filesystem;
std::string OpenFile(const std::string& folder, FiniteFunction& F, int Nbins);



//Define Normal class
class Normal : public FiniteFunction{
public:
    //Constructor
    Normal(double mu, double sigma, std::string name);
    //Override the function called from FiniteFunction
    double callFunction(double x) override;
    //Override the integral from FiniteFunction
    double integrate(int Ndiv) override;
    //Override the information printed from FiniteFunction
    void printInfo();
    //Override the random number generator from FiniteFunctions
    double randomNumber();

private:
    //Define the parameters
    double m_mu;
    double m_sigma;
    std::mt19937 gen;
    double xi;
};



//Define Cauchy-Lorentz class
class CL : public FiniteFunction{
public:
    //Constructor
    CL(double gamma, double x0, std::string name);
    //Override the function called from FiniteFunction
    double callFunction(double x) override;
    //Override the integral from FiniteFunction
    double integrate(int Ndiv) override;
    //Override the information printed from FiniteFunction
    void printInfo();
    //Override the random number generator from FiniteFunctions
    double randomNumber();

private:
    //Define the parameters
    double m_gamma;
    double m_x0;
    std::mt19937 gen;
    double xi;
};



//Define Crystal Ball class
class CB : public FiniteFunction{
public:
    //Constructor
    CB(double mu, double sigma, double n, double alpha, std::string name);
    //Override the function called from FiniteFunction
    double callFunction(double x) override;
    //Override the integral from FiniteFunction
    double integrate(int Ndiv) override;
    //Calculate the values of the constants used in the integral & in the function definition
    void computeConstants();
    //Override the information printed from FiniteFunction
    void printInfo();
    //Override the random number generator from FiniteFunctions
    double randomNumber();

private:
    //Define the parameters
    double m_mu;
    double m_sigma;
    double m_n;
    double m_alpha;
    std::mt19937 gen;
    double xi;

    double m_A;
    double m_B;
    double m_C;
    double m_D;
    double m_N;
};


#endif // CUSTOMFUNCTIONS2_H
#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <random>
#include <filesystem>
#include "FiniteFunctions.h"
#include "CustomFunctions2.h"

int main() {
    //Construct the function for each new class
    Normal normal(3, 1.6, "Normal");
    CL cl(1.5, 3, "CauchyLorentz");
    CB cb(3, 1.5, 1.8, 2.4, "CrystalBall");

    // Array of pointers to FiniteFunctions class
    FiniteFunction* functions[] = { &normal, &cl, &cb };

    //Loop through each new class
    for (auto f : functions) {
        //Print the range, integral, parameters, and function name
        f->printInfo();

        //Open and plot mystery data
        std::string baseName = OpenFile("Outputs/data", *f, 49);
        f->setName(baseName + "_" + f->getName() + "_plot");

        //Set number of samples for Metropolis-Hastings algorithm
        const int Nsamples=10000;
        //Set vector to store the sampled data
        std::vector<double> samples;

        //Metropolis-Hastings algorithm loop which stores the accepted values
        for (int i=0; i<Nsamples; i++){
            double xi=f->randomNumber();
            samples.push_back(xi);
        }

        //Plot the sampled data on the same plot as the mystery data and the function
        f->plotData(samples, 50, false);
        //Plot the function on the same plot as the mystery data
        f->plotFunction();

        //Print a dashed line between the terminal output for each function
        std::cout << "----------------------------------------\n";
    }
    return 0;
}

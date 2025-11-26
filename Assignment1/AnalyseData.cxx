//Lucy Joyce 20/11/2025

//To compile type'g++ AnalyseData.cxx CustomFunctions.cxx CustomFunctions.h -o AnalyseData' into the terminal.
//To run the code type './AnalyseData' into the terminal.

#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "CustomFunctions.h"

int main(){

    //Open the input2D_float.txt file
    std::string inputfile="../Exercises/Lab1and2/input2D_float.txt";
    std::ifstream data_file;
    data_file.open(inputfile);

    //Has the file opened successfully
    if (!data_file.is_open()){
        std::cout << "Error opening file:" << inputfile << std::endl;
        return -1;
    }
    else{
        std::cout << "File:" << inputfile << " opened successfully!" << std::endl;
    }

    //Set up vectors to store read the data in the file to
    std::vector<std::string> x_values;
    std::vector<std::string> y_values;
    std::string line;
    std::vector<float> xx_values;
    std::vector<float> yy_values;

    //Skip header in file
    std::getline(data_file, line);

    //Set initial number of rows to 0
    int rows=0;

    //Read the data (as strings) to vectors
    float xx, yy;
    while(std::getline(data_file,line)){
        std::stringstream ss(line);
        std::string x,y;
        if (std::getline(ss, x, ',') && std::getline(ss, y, ',')) {
            x_values.push_back(x);
            y_values.push_back(y);
        
            //Change the data type from strings to floats
            xx=stof(x);
            yy=stof(y);

            //Read the data (as floats) to different vectors
            xx_values.push_back(xx);
            yy_values.push_back(yy);
        }

        //Counts number of rows in the file
        rows++;
    }

    //Open and read the error2D_float.txt file in the same way as above
    std::string inputfile2="../Exercises/Lab1and2/error2D_float.txt";
    std::ifstream data_file2;
    data_file2.open(inputfile2);
    std::vector<std::string> x_error;
    std::vector<std::string> y_error;
    std::string line2;
    std::vector<float> xx_error;
    std::vector<float> yy_error;
    std::getline(data_file2, line2);
    float xx_err, yy_err;
    while(std::getline(data_file2,line2)){
        std::stringstream ss(line2);
        std::string x_err,y_err;
        if (std::getline(ss, x_err, ',') && std::getline(ss, y_err, ',')) {
            x_error.push_back(x_err);
            y_error.push_back(y_err);
            xx_err=stof(x_err);
            yy_err=stof(y_err);
            xx_error.push_back(xx_err);
            yy_error.push_back(yy_err);
        }
    }
    
    //Print x or y values to the terminal (from the respective vector) based on user input
    PrintData(xx_values,yy_values);

    //Calculate, print to the terminal, and save the vector magnitudes
    auto mags=PrintMag(xx_values, yy_values);
    PrintResult(mags, "Vector Magnitudes");
    SaveResult("vectorMags.txt",mags);

    //Calculate, print to the terminal, and save the gradient and intercept
    std::pair<float,float> result = LinearFitPrint(xx_values, yy_values);
    PrintResult(result, "linear fit (slope, intercept)");
    float p = result.first;
    float q = result.second;
    SaveResult("StraightLine.txt",result);

    //Calculate, print to the terminal, andsave the Chi-Squared value
    float chi = ChiSquared(xx_values, yy_values, p, q, yy_error);
    PrintResult(chi, "chi-squared value");
    SaveResult("ChiSquared.txt",chi);

    //Calculate, print to the terminal, and save the rounded x^y values
    auto rounded = Recursive(xx_values, yy_values);
    PrintResult(rounded, "rounded x^y values");
    SaveResult("Rounded.txt",rounded);
}
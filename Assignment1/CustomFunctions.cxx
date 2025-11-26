#include "CustomFunctions.h"
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string>

//Prints data from vectors to the terminal
void PrintData(const std::vector<float>& x, const std::vector<float>& y){
    int variable, rows;
    std::cout << "Would you like to print x or y values? Enter 0 for x and 1 for y: ";
    std::cin >> variable;
    std::cout << "Enter an integer number of lines you would like to print: ";
    std::cin >> rows;

    const std::vector<float>& data = (variable == 0) ? x : y;
    if (rows > data.size()) {
        std::cout << "Warning: requested more lines than available. Printing first 5 lines instead." << std::endl;
        rows = std::min(5, (int)data.size());
    }

    for (int i = 0; i < rows; ++i) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
}

//Calculates vector magnitudes
std::vector<float> PrintMag(const std::vector<float>& x, const std::vector<float>& y){
    size_t N = x.size();
    std::vector<float> magnitudes(N);
    for (size_t i = 0; i < N; ++i) {
        magnitudes[i] = std::sqrt(x[i] * x[i] + y[i] * y[i]);
    }
    return magnitudes;
}

//Calculates gradient and intercept using least squares
std::pair<float, float> LinearFitPrint(const std::vector<float> &x, const std::vector<float> &y){
    size_t N = x.size();
    float sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0;
    for (size_t i = 0; i < N; ++i) {
        sum_x += x[i];
        sum_y += y[i];
        sum_xy += x[i] * y[i];
        sum_x2 += x[i] * x[i];
    }
    float denominator = N * sum_x2 - sum_x * sum_x;
    float p = (N * sum_xy - sum_x * sum_y) / denominator;
    float q=(sum_x2*sum_y-sum_xy*sum_x)/denominator;
    return {p, q};
}

//Power function
float Power(float x, int y){
    if (y == 0) return 1.0f;
    if (y < 0) return 1.0f / Power(x, -y);
    return x * Power(x, y - 1);
}

//Calculates rounded x^y values
std::vector<int> Recursive(const std::vector<float> &x, const std::vector<float> &y){
    size_t N=x.size();
    std::vector<int> Rounded(N);
    for (size_t i = 0; i < N; ++i){
        int rounded=static_cast<int>(std::round(y[i]));
        Rounded[i] = Power(x[i], rounded); 
    }
    return Rounded;
}

//Calculates Chi-Squared
float ChiSquared(const std::vector<float> &x, const std::vector<float> &y, float p, float q, const std::vector<float> &sigma){
    size_t N = x.size();
    float chi=0;
    std::vector<float> Y_Exp={};
    for (size_t i = 0; i < N; ++i){
        float y_exp=p*x[i]+q;
        Y_Exp.push_back(y_exp);
        chi +=(pow(y[i]-Y_Exp[i],2))/(pow(sigma[i],2));
    }
    return chi;
}

//Prints float
void PrintResult(float value, const std::string& label) {
    int ans;
    std::cout << "Print " << label << "? Enter 1 for yes, 0 for no: ";
    std::cin >> ans;
    if (ans == 1) {
        std::cout << label << " = " << value << std::endl;
    }
}

//Prints vector<float>
void PrintResult(const std::vector<float>& values, const std::string& label) {
    int ans;
    std::cout << "Print " << label << "? Enter 1 for yes, 0 for no: ";
    std::cin >> ans;
    if (ans == 1) {
        for (const auto& val : values) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}

//Prints vector<int>
void PrintResult(const std::vector<int>& values, const std::string& label) {
    int ans;
    std::cout << "Print " << label << "? Enter 1 for yes, 0 for no: ";
    std::cin >> ans;
    if (ans == 1) {
        for (const auto& val : values) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}

//Prints pair<float,float>
void PrintResult(const std::pair<float, float>& values, const std::string& label) {
    int ans;
    std::cout << "Print " << label << "? Enter 1 for yes, 0 for no: ";
    std::cin >> ans;
    if (ans == 1) {
        std::cout << label << ": (" << values.first << ", " << values.second << ")" << std::endl;
    }
}

//Saves vector<float>
void SaveResult(const std::string& filename, const std::vector<float>& values){
    std::ofstream outfile(filename);
    for (const auto& val : values) {
        outfile << val << " ";
    }
    outfile << std::endl;
    outfile.close();
}

//Saves pair<float,float> to a new file
void SaveResult(const std::string& filename, const std::pair<float, float>& values){
    std::ofstream outfile(filename);
    outfile << "y="<< values.first << "x+" << values.second << std::endl;
    outfile.close();
}

//Saves vector<int> to a new file
void SaveResult(const std::string& filename, const std::vector<int>& values){
    std::ofstream outfile(filename);
    for (const auto& val : values) {
        outfile << val << " ";
    }
    outfile << std::endl;
    outfile.close();
}

//Saves float to a new file
void SaveResult(const std::string& filename, float value){
    std::ofstream outfile(filename);
    outfile << value << std::endl;
    outfile.close();
}

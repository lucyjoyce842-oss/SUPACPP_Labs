#ifndef CUSTOMFUNCTIONS_H
#define CUSTOMFUNCTIONS_H

#include <vector>
#include <utility>
#include <string>

void PrintData(const std::vector<float>& x, const std::vector<float>& y);
std::vector<float> PrintMag(const std::vector<float>& x, const std::vector<float>& y);
std::pair<float, float> LinearFitPrint(const std::vector<float> &x, const std::vector<float> &y);
float ChiSquared(const std::vector<float> &x, const std::vector<float> &y, float p, float q, const std::vector<float> &sigma);
float Power(float x, int y);
std::vector<int> Recursive(const std::vector<float> &x, const std::vector<float> &y);

void PrintResult(float value, const std::string& label);
void PrintResult(const std::vector<float>& values, const std::string& label);
void PrintResult(const std::vector<int>& values, const std::string& label);
void PrintResult(const std::pair<float, float>& values, const std::string& label);

void SaveResult(const std::string& filename, const std::vector<float>& values);
void SaveResult(const std::string& filename, const std::pair<float, float>& values);
void SaveResult(const std::string& filename, const std::vector<int>& values);
void SaveResult(const std::string& filename, float value);

#endif // CUSTOMFUNCTIONS_H

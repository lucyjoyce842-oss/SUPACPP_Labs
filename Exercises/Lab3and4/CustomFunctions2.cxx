//Lucy Joyce 03/12/25

#include "CustomFunctions2.h"
#include "FiniteFunctions.h"
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <filesystem>

namespace fs = std::filesystem;

//Constructor for Normal function class
Normal::Normal(double mu, double sigma, std::string name)
    : FiniteFunction(-10, 10, name), m_mu(mu), m_sigma(sigma) { //, gen(std::random_device{}()) 
}
//Calls the Normal function
double Normal::callFunction(double x) {
        double coef=1.0/(m_sigma*std::sqrt(2.0*M_PI));
        double exponent=-0.5*std::pow((x-m_mu)/m_sigma,2);
        return coef*std::exp(exponent);
}
//Integrates the Normal function with RMax & RMin limits
double Normal::integrate(int Ndiv){
    double a=(m_RMin-m_mu)/(m_sigma*std::sqrt(2));
    double b=(m_RMax-m_mu)/(m_sigma*std::sqrt(2));
    return 0.5*(std::erf(b)-std::erf(a));
}
//Prints the function name, parameters, range, and integral
void Normal::printInfo() {
    FiniteFunction::printInfo();
    std::cout << "Mean: " << m_mu << ", StdDev: " << m_sigma << std::endl;
}
//Metropolis-Hastings algorithm
double Normal::randomNumber(){
    std::normal_distribution<double> distNorm(xi, 1.0);
    double y=distNorm(gen);
    double A=std::min(1.0,callFunction(y)/callFunction(xi));
    std::uniform_real_distribution<double> distT(0,1);
    double T=distT(gen);
    if (T<A) xi=y;
    if (xi < m_RMin) xi = m_RMin;
    if (xi > m_RMax) xi = m_RMax;    
    return xi;
}



//Constructor for the Cauchy-Lorentz function class
CL::CL(double gamma, double x0, std::string name)
    : FiniteFunction(-10, 10, name), m_gamma(gamma), m_x0(x0), gen(std::random_device{}()) {
}
//Calls the Cauchy-Lorentz function
double CL::callFunction(double x) {
        double coef=M_PI*m_gamma;
        double bracket=1.0+pow((x-m_x0)/m_gamma,2);
        return 1.0/(coef*bracket);
}
//Integrates the Cauchy-Lorentz function with RMax & RMin limts
double CL::integrate(int Ndiv){
    double coef=1.0/M_PI;
    double a=atan((m_RMax-m_x0)/m_gamma);
    double b=atan((m_RMin-m_x0)/m_gamma);
    return coef*(a-b);
}
//Prints the function name, parameters, range, and integral
void CL::printInfo() {
    FiniteFunction::printInfo();
    std::cout << "Gamma: " << m_gamma << ", x0: " << m_x0 << std::endl;
}
//Metropolis-Hastings algorithm
double CL::randomNumber(){
    std::normal_distribution<double> distNorm(xi, 1.0);
    double y=distNorm(gen);
    double A=std::min(1.0,callFunction(y)/callFunction(xi));
    std::uniform_real_distribution<double> distT(0,1);
    double T=distT(gen);
    if (T<A) xi=y;
    if (xi < m_RMin) xi = m_RMin;
    if (xi > m_RMax) xi = m_RMax;    
    return xi;
}



//Constructor for the Crystal Ball function class
CB::CB(double mu, double sigma, double n, double alpha, std::string name)
    : FiniteFunction(-10, 10, name), m_mu(mu), m_sigma(sigma), m_n(n), m_alpha(alpha), gen(std::random_device{}()) {
        computeConstants();
    }
//Computes the constants needed for the Crystal Ball integral
void CB::computeConstants(){
    m_A=pow(m_n/fabs(m_alpha),m_n)*exp(-(m_alpha*m_alpha)/2);
    m_B=(m_n/fabs(m_alpha))-fabs(m_alpha);
    m_C=(m_n/fabs(m_alpha))*(1.0/(m_n-1.0))*exp(-(m_alpha*m_alpha)/2);
    m_D=sqrt(M_PI/2)*(1.0+erf(fabs(m_alpha)/sqrt(2)));
    m_N=1.0/(m_sigma*(m_C+m_D));
}
//Calls the Crystal Ball function
double CB::callFunction(double x) {
    if ((x-m_mu)/m_sigma > -m_alpha){
        return m_N*exp(-((x-m_mu)*(x-m_mu))/(2*m_sigma*m_sigma));
    }
    else{
        return m_N*m_A*pow((m_B-((x-m_mu)/m_sigma)),-m_n);
    }
}
//Integrates the Crystal Ball function with RMax & RMin limits
double CB::integrate(int Ndiv){
    double t1=(m_RMin-m_mu)/m_sigma;
    double t2=(m_RMax-m_mu)/m_sigma;
    if (t1<=-m_alpha && t2<=-m_alpha){  
        return ((m_N*m_A*m_sigma)/(1.0-m_n))*(pow(m_B-t2,-m_n+1.0)-pow(m_B-t1,-m_n+1.0));
    }
    else if (t1>-m_alpha && t2>-m_alpha){
        return m_N*m_sigma*sqrt(M_PI/2)*(erf(t2/sqrt(2))-erf(t1/sqrt(2)));
    }
    else if (t1 <= -m_alpha && t2 > -m_alpha){
        return ((m_N*m_A*m_sigma)/(1.0-m_n))*(pow(m_B-(-m_alpha),-m_n+1.0)-pow(m_B-t1,-m_n+1.0))+m_N*m_sigma*sqrt(M_PI/2)*(erf(t2/sqrt(2))-erf(-m_alpha/sqrt(2)));
    }
    return 0.0;
}
//Prints the function name, parameters, range, and integral
void CB::printInfo() {
    FiniteFunction::printInfo();
    std::cout << "Mu: " << m_mu << ", Sigma: " << m_sigma
              << ", n: " << m_n << ", Alpha: " << m_alpha << std::endl;
}
//Metropolis-Hastings algorithm
double CB::randomNumber(){
    std::normal_distribution<double> distNorm(xi, 1.0);
    double y=distNorm(gen);
    double A=std::min(1.0,callFunction(y)/callFunction(xi));
    std::uniform_real_distribution<double> distT(0,1);
    double T=distT(gen);
    if (T<A) xi=y;
    if (xi < m_RMin) xi = m_RMin;
    if (xi > m_RMax) xi = m_RMax;    
    return xi;
}



//Finds & opens the newest file for plotting & returns file name
std::string OpenFile(const std::string& folder, FiniteFunction& F, int Nbins){
    fs::path latest;
    std::filesystem::file_time_type latest_time;
    bool first = true;
    for (const auto& entry : fs::directory_iterator(folder)){
        if (entry.is_regular_file()) {
            auto ftime = fs::last_write_time(entry);
            if (first || ftime > latest_time) {
                first = false;
                latest_time = ftime;
                latest = entry.path();
            }
        }
    }
    std::string File = latest.string();
    std::string inputfile = File;
    std::ifstream data_file(inputfile);
    std::vector<double> values;
    std::string line;
    while(std::getline(data_file,line)){
    double val = std::stod(line);
    // Clamp values to function range
    if (val < F.rangeMin()) val = F.rangeMin();
    if (val > F.rangeMax()) val = F.rangeMax();        
        values.push_back(val);
    }
    F.plotData(values, Nbins, true);
    return latest.stem().string();
}
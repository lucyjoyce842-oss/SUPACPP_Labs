#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <filesystem>
#include "FiniteFunctions.h"
#include "CustomFunctions2.h"

//make the title of each plot the mysterydataxxxx_plot
//print mysterydataxxxx to terminal
// is there a way to replace the mysterydataxxxx file in outputs each time rather than saving loads of them? maybe do this.

int main(){
    FiniteFunction f(-10,10,"myplot");

    OpenFile("Outputs/data",f,49);
    f.integral(10000);
    f.plotFunction();
    //return 0;

    //std::cout<< filename <<std::endl;

    //Open the randomly generated data file
    //std::string inputfile= "Outputs/data/MysteryData23120.txt";
    //std::ifstream data_file;
    //data_file.open(inputfile);

    //std::string line;
    //while(std::getline(data_file,line)){
        //std::cout<< line <<std::endl;
    //}

    //std::vector<float> values;
    //std::string line;
    
    //while(std::getline(data_file,line)){
        //float val=std::stof(line);
        //values.push_back(val);
//}



//for (size_t i = 0; i < values.size(); i++) {
    //std::cout << values[i] << std::endl;
//}


}
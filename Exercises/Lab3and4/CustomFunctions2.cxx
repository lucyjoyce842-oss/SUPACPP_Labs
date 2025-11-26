#include "CustomFunctions2.h"
#include "FiniteFunctions.h"
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;
void OpenFile(const std::string& folder, FiniteFunction& F, int Nbins){
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
        values.push_back(std::stod(line));
        //float val=std::stof(line);
        //values.push_back(val);
    }
    F.plotData(values, Nbins, true);
    return;
    //for (size_t i = 0; i < values.size(); i++) {
        //std::cout << values[i] << std::endl;
    //}
    //std::cout << std::endl;
}
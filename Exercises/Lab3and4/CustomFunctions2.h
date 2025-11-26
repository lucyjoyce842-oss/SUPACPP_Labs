#ifndef CUSTOMFUNCTIONS2_H
#define CUSTOMFUNCTIONS2_H

#include "FiniteFunctions.h"
#include <vector>
#include <utility>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;
void OpenFile(const std::string& folder, FiniteFunction& F, int Nbins);

#endif // CUSTOMFUNCTIONS2_H
#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "reader.h"
#include "log_duration.h"

using Base = std::vector<std::vector<double>>;
using NamesKKS = std::map<std::string, std::string>;

class ReadRsa{
  public:
    ReadRsa(std::vector<std::string>& kks, Base& base);

    void AddKKS(std::vector<std::string>&  vec);
    void AddBase(std::vector<double>&  vec);
    std::vector<std::string>& GetKKS();
    Base& GetBase();
  private:
    std::vector<std::string> KKS_;
    Base base_;
};


ReadRsa MakeBase(const std::string& file_name, ostream& out);

NamesKKS MakeNamesKKS(int blok_number);

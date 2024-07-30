#pragma once
#include <map>
#include <string>
#include <fstream>
#include <string_view>
#include <vector>
#include <iostream>
#include <list>


using SUZ_Cells = std::map<std::string, std::vector<std::string>>;
using Cell_TVS = std::map<std::string, int>;

class CSV{
public:
    CSV(std::ifstream& input);
    void MakeBase(std::ifstream& input);
    void MakeTvsCells();
    std::string GetCellSuz(const std::string& suz_number, int company_number) const;
    int GetTVSNumber(const std::string& suz_cell) const;
    const std::list<std::string>& GetSuzList();
private:
    SUZ_Cells suz_cells_;
    Cell_TVS tvs_to_cell_;
    std::list<std::string> suz_list_;
};

#include "reader_csv.h"



CSV::CSV(std::ifstream& input){
    MakeBase(input);
    MakeTvsCells();
}
void CSV::MakeBase(std::ifstream& input){
    std::string str;
    std::string_view s;
    int pos = 0;
    std::string suz_number;
    std::string buf;
    while(std::getline(input, str)){
        s = str;
        pos = s.find(',');
        suz_number = s.substr(0, pos);
        suz_list_.push_front(suz_number);
        while(pos != s.npos){
            s.remove_prefix(pos+1);
            pos = s.find(',');
            buf = s.substr(0, pos);
            suz_cells_[suz_number].push_back(buf);
        }

    }
}

void CSV::MakeTvsCells(){
    std::ifstream input("input_data/tvs_cells.csv");
    std::string str;
    std::string_view s;
    int tvs_number;
    std::string cell;
    while(std::getline(input, str)){
        s = str;
        int pos = s.find(',');
        tvs_number = std::stoi(std::string(s.substr(0, pos)));
        s.remove_prefix(pos+1);
        cell = s;
        tvs_to_cell_[cell] = tvs_number ;
    }

}

std::string CSV::GetCellSuz(const std::string& suz_number, int company_number) const{
    return suz_cells_.at(suz_number).at(company_number);
}

int CSV::GetTVSNumber(const std::string& suz_cell) const{
    return tvs_to_cell_.at(suz_cell);
}

const std::list<std::string>& CSV::GetSuzList(){
    return suz_list_;
}

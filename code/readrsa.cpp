#include "readrsa.h"

ReadRsa::ReadRsa(std::vector<std::string>& kks, Base& base){
    KKS_ = std::move(kks);
    base_ = std::move(base);
}

void ReadRsa::AddBase(std::vector<double>&  vec){

}

void ReadRsa::AddKKS(std::vector<std::string>&  vec){
    KKS_.swap(vec);
}

std::vector<std::string>& ReadRsa::GetKKS(){
    return KKS_;
}
Base& ReadRsa::GetBase(){
    return base_;
}

ReadRsa  MakeBase(const std::string& file_name, ostream& out){
    LOG_DURATION dur("MAKE_BASE FROM RSA"s);
    std::ifstream file(file_name);
    std::vector<std::string> kks;
    std::string str;
    for(int i =0; i<4; i++){
        std::getline(file, str);
        out<<str<<endl;
    }
    std::getline(file, str);
    kks = ReadlineS(str);
    Base baza(kks.size());
    for(vector<double>& vec:baza){
        vec.reserve(5000);
    }
    while(std::getline(file, str)){
        vector<double> res = ReadlineNum(str);
        for(size_t i = 0; i<res.size(); i++){
            baza[i].push_back(res[i]);
        }
    }
    ReadRsa Rrsa(kks, baza);
    return Rrsa;
}

NamesKKS MakeNamesKKS(int blok_number){
    std::string blok_file;
    (blok_number == 1)
            ? blok_file = "input_files/Tsuz_names.txt"s
            : blok_file = "input_files/Tsuz_names2.txt"s;
    std::fstream file("input_files/Tsuz_names.txt");
    std::string str;
    for(int i=0; i<5; i++){
        std::getline(file, str);
    }
    NamesKKS result;
    while(std::getline(file, str)){
        std::string_view sv = str;
        int pos = sv.find(' ');
        sv.remove_suffix(sv.size() - pos);
        std::string KKS = std::string(sv);
        sv = str;
        pos = sv.find('|');
        sv.remove_prefix(pos+1);
        pos = sv.find('|');
        sv.remove_suffix(sv.size() - pos);
        result[KKS] =  std::string(sv);
    }

    return result;

}

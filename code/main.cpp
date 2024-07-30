#include <iostream>
#include <fstream>
#include <numeric>

#include "readrsa.h"
#include "catalog.h"
#include "log_duration.h"
#include "reader_csv.h"

using namespace std;



int main()
{
    std::cout<<"Suz_counter"s<<std::endl;
    std::string s;
    int block_number;
    std::cout<<"Enter block number = ";
    cin>>block_number;
    std::cout<<"Enter_step_HOUR_or_Minutes= ";
    std::cin>>s;
    Step step;
        if(s == "HOUR"s){
            step = Step::Hour;
        } else {
            step = Step::Minutes;
        }
    int company_number;
    std::cout<<"Company number = ";
    cin>>company_number;

    std::ifstream file_in("input_data/cells.csv");
    CSV csv_file(file_in);
    NamesKKS names = MakeNamesKKS(block_number);
    LOG_DURATION main("Total_time");
    std::ofstream file("answer/out.txt");
    file<<"Created by Baskakov Ivan"<<endl;

    Suzes suzes(csv_file);


    for(int i=0; i<company_number; i++){
        std::string n = std::to_string(i);
        std::string namefile = "input_data/Tsuz"s + n + ".txt"s;
        ReadRsa Rrsa = MakeBase(namefile, file);
        Catalog catalog = MakeCatlog(Rrsa, step);
        suzes.AddCompany(catalog);
    }
    std::ofstream csvfile("answer/Teff_SUZ_total.csv");
    suzes.PrintSuzCsv(csvfile, company_number);

    file<<'\n'<<'\n' << "Good Job" << endl;
    return 0;
}

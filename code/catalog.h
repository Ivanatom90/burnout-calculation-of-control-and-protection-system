#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <fstream>
#include <future>
#include <iomanip>
#include <string_view>
#include <algorithm>

#include "reader_csv.h"
#include "readrsa.h"

enum Step{Hour, Minutes};


class Cell{
public:
    Cell(std::string kks, std::vector<double>& numbers);
    Cell(std::string kks, std::vector<double>& numbers, std::vector<double>& power);
    void MakeTeff(const std::vector<double>& power, Step);
    void MakeTvsNum();
    std::string GetKKS() const;
    double GetTeff() const;
    int GetTVSNumber() const;
private:
    std::string KKS_;
    int tvs_number_;
    std::vector<double> level_;
    double Teff_;
   // static std::vector<double> power_;

};

class Catalog{
public:
    Catalog(Cell& Cell);
    Catalog(std::vector<Cell>& vCell);
    void AddCell(Cell& Cell);
    const std::vector<Cell>& GetCatalog() const;
    double GetTefSuz(int tvs_number) const;
    void PrintCatalog(std::ostream& out, const NamesKKS& names);
    void PrintCatalogCSV(std::ostream& out, const NamesKKS& names);
    void DeleteN();
private:
    std::vector<Cell> cataloge_;
};


Catalog MakeCatlog(ReadRsa& rrsa, Step);

struct Suz{
  std::string suz_number;
  double Teff = 0.0;
};

class Suzes{
public:
    Suzes(CSV& csv);
    void AddCompany(const Catalog& catalog);
    void PrintSuzCsv(std::ofstream& out, const int company_number) const;
private:
    std::list<Suz> suzes_;
    CSV& csv_;
    int company_ = 0;

    void MakeSuzVec();
};


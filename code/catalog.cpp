#include "catalog.h"
#include <numeric>
#include "log_duration.h"


Cell::Cell(std::string kks, std::vector<double>& numbers): KKS_(kks){
    level_.swap(numbers);
    MakeTvsNum();
}

Cell::Cell(std::string kks, std::vector<double>& numbers, std::vector<double>& power){
    Cell(kks, numbers);
    MakeTvsNum();
};

void Cell::MakeTeff(const std::vector<double>& power, Step step){
    std::vector<double> tsuz;
    tsuz.resize(power.size());
    int i = 0;
    std::transform(level_.begin(), level_.end(), tsuz.begin(), [&i, &power, &step](double Cell){
        if(Cell<100){
            if(step == Step::Minutes){
                return power[i++]/(100*60);
            } else if(step == Step::Hour){
                return power[i++]/(100);
            }
        }
        i++;
        return 0.0;
    });

    Teff_ = std::accumulate(tsuz.begin(), tsuz.end(), 0.0);
}

std::string Cell::GetKKS() const{
    return KKS_;
}
double Cell::GetTeff() const{
    return Teff_;
}

void Cell::MakeTvsNum(){
    std::string_view s = KKS_;
    s.remove_prefix(9);
    s.remove_suffix(4);
    tvs_number_ = std::stoi(std::string(s));
}


int Cell::GetTVSNumber() const{
    return tvs_number_;
}


Catalog::Catalog(Cell& Cell){
    AddCell(Cell);
}

Catalog::Catalog(std::vector<Cell>& vsuz){
    cataloge_.swap(vsuz);
}


void Catalog::AddCell(Cell& Cell){
    cataloge_.push_back(std::move(Cell));
}

Catalog MakeCatlog(ReadRsa& rrsa, Step step){
    std::vector<Cell> result;
    result.reserve(rrsa.GetKKS().size());
        for(size_t i =0; i < rrsa.GetKKS().size()-1; i++){
            Cell Cell(rrsa.GetKKS()[i], rrsa.GetBase()[i]);
            Cell.MakeTeff(rrsa.GetBase().back(), step);
            result.push_back(std::move(Cell));
        }
    Catalog cat(result);
    return cat;
}

void Catalog::PrintCatalog(std::ostream &out, const NamesKKS& names){
    out<<"Created by Baskakov Ivan"s<<'\n'<<std::endl;
    for(const Cell& Cell:cataloge_){
        out<<Cell.GetKKS()<<setw(15)<<Cell.GetTeff()<<"     eff_hours        "<<names.at(Cell.GetKKS())<<std::endl;
    }
}

void Catalog::PrintCatalogCSV(std::ostream& out, const NamesKKS& names){
    out<<"Created by Baskakov Ivan"s<<'\n'<<std::endl;
    out<<"KKS"<<','<<"eff_hours"<<','<<"Name"<<std::endl;
    for(const Cell& Cell:cataloge_){
        out<<Cell.GetKKS()<<','<<Cell.GetTeff()<<','<<names.at(Cell.GetKKS())<<std::endl;
    }
}

void Catalog::DeleteN(){
    for(int i=4; i != 0; i--){
          cataloge_.pop_back();
    }
}

double Catalog::GetTefSuz(int tvs_number) const{
    auto teff = find_if(cataloge_.begin(), cataloge_.end(), [&tvs_number](const Cell& cell){
        return cell.GetTVSNumber() == tvs_number;
    });
    return teff->GetTeff();
}

Suzes::Suzes(CSV& csv): csv_(csv), company_(0){
    MakeSuzVec();
}

void Suzes::MakeSuzVec(){
    for(const std::string& suz:csv_.GetSuzList()){
        suzes_.push_front({suz, 0.00});
    }
}

void Suzes::AddCompany(const Catalog& catalog){
    for(Suz& suz:suzes_){
        std::string tvs_cell = csv_.GetCellSuz(suz.suz_number, company_);
        int tvs_num = csv_.GetTVSNumber(tvs_cell);
        suz.Teff += catalog.GetTefSuz(tvs_num);
    }
    company_++;
}

void Suzes::PrintSuzCsv(std::ofstream& out, const int company_number) const{
    out<<"Created by Baskakov Ivan"<<endl;
    out<<"№ SUZ"<<','<<"Eff_hours"<<endl;
    for(const Suz& suz:suzes_){
        out<<suz.suz_number<<','<<suz.Teff<<endl;
    }
    out<<'\n'<<"Company number ="<<','<<company_number<<endl;
}

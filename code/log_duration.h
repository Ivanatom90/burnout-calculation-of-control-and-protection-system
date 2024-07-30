#pragma once
#include <chrono>
#include <iostream>


class LOG_DURATION{
public:
    LOG_DURATION(std::string p): point(p), now_(std::chrono::system_clock::now()){
        std::cout<<"Start "<<p<<std::endl;
    }
    ~LOG_DURATION(){
        using seconds = std::chrono::duration<double>;
        using millisec = std::chrono::duration<double, std::ratio_multiply<seconds::period, std::milli>>;
        auto time = std::chrono::system_clock::now() -now_;
        std::cout<<millisec(time).count()<<"      milliseconds"<<std::endl;
        std::cout<<"END "<<point<<std::endl<<std::endl;

    }
private:
    std::string point;
    std::chrono::system_clock::time_point now_;
};

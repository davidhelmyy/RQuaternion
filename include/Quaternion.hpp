


#ifndef RQUATERNION_QUATERNION_HPP
#define RQUATERNION_QUATERNION_HPP

#include <iostream>
#include <vector>
#include <Rcpp.h>



class Quaternion {

public:

    Quaternion() = default;

    Quaternion(double a, double b, double c, double d) {
        data.resize(4);
        data[0] = a;
        data[1] = b;
        data[2] = c;
        data[3] = d;
    }


    Quaternion(std::vector<double> aVec) {
        this->data = aVec;
    }


    ~Quaternion() = default;


    std::vector<double>
    GetData() {
        return this->data;
    }

    void
    PrintData(){
        for(auto &x:data){
            Rcpp::Rcout<<x<<std::endl;
        }
    }

    void
    SetData(std::vector<double> data){
        data.resize(4);
        this->data=data;
    }


private:
    std::vector<double> data;
};

#endif //RQUATERNION_QUATERNION_HPP

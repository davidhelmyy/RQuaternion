
#ifndef RQUATERNION_HELPERS_HPP
#define RQUATERNION_HELPERS_HPP

#include <math.h>
#include <vector>
#include <iostream>


void
Validate(std::vector<double> aVector){
    if(aVector.size()!=4){
        throw std::range_error("Incorrect input");
    }
}

void
Validate(std::vector<double> aVectorA,std::vector<double> aVectorB){

    if (aVectorA.size() != aVectorB.size() || aVectorA.size() != 4) {
        throw std::range_error("Incorrect input");
    }
}

double
Dot(std::vector<double> Lhs, std::vector<double> Rhs) {

    return Lhs[0] * Rhs[0] + Lhs[1] * Rhs[1] + Lhs[2] * Rhs[2] +
           Lhs[3] * Rhs[3];
}

double
Norm(std::vector<double> Rotation) {
    return sqrt(Rotation[0] * Rotation[0] +
                Rotation[1] * Rotation[1] +
                Rotation[2] * Rotation[2] +
                Rotation[3] * Rotation[3]);
}

std::vector<double>
Normalized(std::vector<double> Rotation)
{
    std::vector<double> temp;
    auto norm=Norm(Rotation);
    for (auto &x:Rotation ){
        temp.push_back(x/norm);
    }
    return temp;
}

double
Angle(std::vector<double> A, std::vector<double> B) {
    Validate(A,B);
    double dot = Dot(A, B);
    return acos(fmin(fabs(dot), 1)) * 2;
}



#endif //RQUATERNION_HELPERS_HPP

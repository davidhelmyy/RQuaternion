
#include "include/Operations.hpp"


using namespace Rcpp;

RCPP_EXPOSED_CLASS(Quaternion)


RCPP_MODULE(Quaternion) {
    class_<Quaternion>("Quaternion")
        .constructor<double, double, double, double>()
        .constructor<std::vector<double>>()
        .property("data", &Quaternion::GetData, &Quaternion::SetData)
        .method("PrintData", &Quaternion::PrintData)
        .method("GetData", &Quaternion::GetData);

    function("CreateIdentity", &Identity);
    function("Identity", &Identity_1);
    function("Conjugate", &Conjugate);
    function("FromEuler", &FromEuler);
    function("Inverse", &Inverse);
    function("LerpUnclamped", &LerpUnclamped);
    function("Lerp", &Lerp);
    function("SlerpUnclamped", &SlerpUnclamped);
    function("Slerp", &Slerp);
    function("RotateTowards", &RotateTowards);

}
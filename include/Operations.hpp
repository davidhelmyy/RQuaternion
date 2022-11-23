
#ifndef RQUATERNION_OPERATIONS_HPP
#define RQUATERNION_OPERATIONS_HPP

#include "Quaternion.hpp"
#include "Helpers.hpp"
#include <math.h>


Quaternion *
Identity() {
    Quaternion *temp=new Quaternion(0,0,0,1);
    return temp;
}


void
Identity_1(Quaternion *A) {
    auto temp = A->GetData();
    temp.resize(4);
    temp[0] = 0;
    temp[1] = 0;
    temp[2] = 0;
    temp[3] = 1;
}


Quaternion *
Conjugate(Quaternion *Rotation) {
    auto temp = Rotation->GetData();
    Validate(temp);
    return new Quaternion(-(temp[0]), -(temp[1]), -(temp[2]),
                          temp[3]);
}


Quaternion *
FromEuler(double x, double y, double z) {
    double cx = cos(x * 0.5);
    double cy = cos(y * 0.5);
    double cz = cos(z * 0.5);
    double sx = sin(x * 0.5);
    double sy = sin(y * 0.5);
    double sz = sin(z * 0.5);
    Quaternion *temp_quat = new Quaternion();
    auto temp = temp_quat->GetData();
    temp[0] = cx * sy * sz + cy * cz * sx;
    temp[1] = cx * cz * sy - cy * sx * sz;
    temp[2] = cx * cy * sz - cz * sx * sy;
    temp[3] = sx * sy * sz + cx * cy * cz;
    return temp_quat;
}


Quaternion *
Inverse(Quaternion *Rotation) {
    auto temp = Rotation->GetData();
    Validate(temp);
    double n = Norm(temp);
    auto temp_conj = Conjugate(Rotation);
    for (auto &x: temp_conj->GetData()) {
        x = x / (n * n);
    }
    return temp_conj;
}


Quaternion *
LerpUnclamped(Quaternion *AQuat, Quaternion *BQuat, double t) {
    auto temp_a = AQuat->GetData();
    auto temp_b = BQuat->GetData();
    Validate(temp_a, temp_b);
    std::vector<double> quaternion;
    quaternion.resize(4);
    if (Dot(temp_a, temp_b) >= 0) {
        for (auto i = 0; i < 4; i++) {
            quaternion[i] = temp_a[i] * (1 - t) + temp_b[i] * t;
        }

    } else {
        for (auto i = 0; i < 4; i++) {
            quaternion[i] = temp_a[i] * (1 - t) - temp_b[i] * t;
        }
    }
    return new Quaternion(Normalized(quaternion));
}


Quaternion *
Lerp(Quaternion *AQuat, Quaternion *BQuat, double t) {
    auto a = AQuat->GetData();
    auto b = BQuat->GetData();
    Validate(a, b);
    if (t < 0) return new Quaternion(Normalized(a));
    else if (t > 1) return new Quaternion(Normalized(b));
    return LerpUnclamped(AQuat, BQuat, t);
}


Quaternion *
SlerpUnclamped(Quaternion *AQuat, Quaternion *BQuat, double t) {
    auto a = AQuat->GetData();
    auto b = BQuat->GetData();
    Validate(a, b);
    double n1;
    double n2;
    double n3 = Dot(a, b);
    bool flag = false;
    if (n3 < 0) {
        flag = true;
        n3 = -n3;
    }
    if (n3 > 0.999999) {
        n2 = 1 - t;
        n1 = flag ? -t : t;
    } else {
        double n4 = acos(n3);
        double n5 = 1 / sin(n4);
        n2 = sin((1 - t) * n4) * n5;
        n1 = flag ? -sin(t * n4) * n5 : sin(t * n4) * n5;
    }
    std::vector<double> quaternion;
    quaternion.resize(4);
    quaternion[0] = (n2 * a[0]) + (n1 * b[0]);
    quaternion[1] = (n2 * a[1]) + (n1 * b[1]);
    quaternion[2] = (n2 * a[2]) + (n1 * b[2]);
    quaternion[3] = (n2 * a[3]) + (n1 * b[3]);
    return new Quaternion(Normalized(quaternion));
}


Quaternion *
Slerp(Quaternion *AQuat, Quaternion *BQuat, double t) {
    auto a = AQuat->GetData();
    auto b = BQuat->GetData();
    Validate(a, b);
    if (t < 0) return new Quaternion(Normalized(a));
    else if (t > 1) return new Quaternion(Normalized(b));
    return SlerpUnclamped(AQuat, BQuat, t);
}


Quaternion *
RotateTowards(Quaternion *AQuat, Quaternion *BQuat,
              double maxRadiansDelta) {
    auto from = AQuat->GetData();
    auto to = BQuat->GetData();
    Validate(from, to);
    double angle = Angle(from, to);
    if (angle == 0)
        return new Quaternion(to);
    maxRadiansDelta = fmax(maxRadiansDelta, angle - M_PI);
    double t = fmin(1, maxRadiansDelta / angle);
    return SlerpUnclamped(AQuat, BQuat, t);
}

#endif //RQUATERNION_OPERATIONS_HPP

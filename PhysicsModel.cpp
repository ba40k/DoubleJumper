//
// Created by radamir on 15.04.25.
//

#include "PhysicsModel.h"
#include "cmath"
PhysicsModel::PhysicsModel(long double gravitation) {
    this->gravitation = gravitation;
}
long double PhysicsModel::calculateDistace(int time, long double speed) {
    return speed*time + gravitation * time * time / 2.0;
}
long double PhysicsModel::calculateSpeed(int time, long double speed, long double direction) {
    return speed + direction * gravitation * time;
}
long double PhysicsModel::getGravitation() const {
    return gravitation;
}
int PhysicsModel::getByModulo(int x, int mod) {
    return (x + (abs(x)/mod+1)*(mod))%mod;
}

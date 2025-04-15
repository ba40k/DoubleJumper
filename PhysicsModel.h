//
// Created by radamir on 15.04.25.
//

#ifndef PHYSICSMODEL_H
#define PHYSICSMODEL_H



class PhysicsModel {
    long double gravitation;
    public:
    PhysicsModel(long double gravitation);
    long double getGravitation() const;
    long double calculateDistace(int time, long double speed);
    long double calculateSpeed(int time, long double speed, long double direction);
};



#endif //PHYSICSMODEL_H

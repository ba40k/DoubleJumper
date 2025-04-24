//
// Created by radamir on 24.04.25.
//

#ifndef BROWNPLATFORM_H
#define BROWNPLATFORM_H

#include "AbstractPlatform.h"

class BrownPlatform : public AbstractPlatform{
    private:
    bool broken = false;
    bool animationEnded = false;
    int animationCounter = 0;
    public:
    BrownPlatform(int coordinateX, int coordinateY, QString &imagePath);
    QLabel* getQLabel(QWidget *parent = nullptr)  override;
    void setBroken() override;
    bool isBroken();
    bool isAnimationEnded();
};



#endif //BROWNPLATFORM_H

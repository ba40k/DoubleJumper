//
// Created by radamir on 24.04.25.
//

#ifndef BROWNPLATFORM_H
#define BROWNPLATFORM_H

#include "AbstractPlatform.h"

class BrownPlatform : public AbstractPlatform{
    private:
    bool broken = false;
    public:
    BrownPlatform(int coordinateX, int coordinateY, QString &imagePath);
    QLabel* getQLabel(QWidget *parent = nullptr) const override;
    void setBroken() override;
    bool isBroken();
};



#endif //BROWNPLATFORM_H

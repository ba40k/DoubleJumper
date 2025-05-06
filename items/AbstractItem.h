//
// Created by radamir on 29.04.25.
//

#ifndef ABSTRACTITEM_H
#define ABSTRACTITEM_H
#include <QLabel>
#include "../DoubleJumper.h"
#include "../platforms/AbstractPlatform.h"

class AbstractItem {
    protected:
    bool soundsOn = true;
    int width;
    int height;
    int coordinateX;
    int shiftY;
    AbstractPlatform* platform; // хранится платформа и координата относительно платформы
    int onTileCoordinateX;
    int onTileCoordinateY;
    QString prefixPath = "requirments/Sprites/Doodle Jump/";
    QString imagePath = "game-tiles@2x.png";
    QString prefixSoundPath = "requirments/Doodle Jump SFX/";
    public:
    AbstractItem(int coordinateX ,int width, int height, AbstractPlatform* platform,bool soundsOn);
    virtual void activate(DoubleJumper &activator) = 0;
    virtual  QLabel* getQLabel(QWidget *parent = nullptr)  = 0;
    virtual int getCoordinateX();
    virtual int getCoordinateY();
    int getHeight();
    int getWidth();
    AbstractPlatform* getPlatform();
    virtual ~AbstractItem() = default;

};



#endif //ABSTRACTITEM_H

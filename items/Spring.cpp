//
// Created by radamir on 29.04.25.
//

#include "Spring.h"
#include <iostream>
Spring::Spring(int coordinateX, AbstractPlatform* platform) : AbstractItem(coordinateX,35,21,platform) {
    onTileCoordinateX =  nonActivatedOnTileCoordinateX;
    onTileCoordinateY =  nonActivatedOnTileCoordinateY;
    shiftY = 3;
}
QLabel *Spring::getQLabel(QWidget *parent) {
    QLabel *label = new QLabel(parent);
    label->setScaledContents(true);
    label->setGeometry(getCoordinateX(),getCoordinateY(),width, height);
    label->setPixmap(QPixmap(prefixPath + imagePath).copy(onTileCoordinateX,onTileCoordinateY,width,height));
    return label;
}
void Spring::setActivated() {
    activated = true;
    width = ActivatedWidth;
    height = ActivatedHeight;
    onTileCoordinateX = ActivatedOnTileCoordinateX;
    onTileCoordinateY = ActivatedOnTileCoordinateY;
}
void Spring::activate(DoubleJumper &activator) {
   // std::cout<<1;
    setActivated();
    activator.setSpeed(speedBuff);
}



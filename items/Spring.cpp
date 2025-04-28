//
// Created by radamir on 29.04.25.
//

#include "Spring.h"

Spring::Spring(int coordinateX, AbstractPlatform* platform) : AbstractItem( coordinateX,nonActivatedWidth,nonActivatedHeight,platform) {
    onTileCoordinateX =  nonActivatedOnTileCoordinateX;
    onTileCoordinateY =  nonActivatedOnTileCoordinateY;
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
    setActivated();
    activator.setSpeed(activator.getSpeed() +  speedBuff);
}



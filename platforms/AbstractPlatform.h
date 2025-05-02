//
// Created by radamir on 16.04.25.
//

#ifndef ABSTRACTPLATFORM_H
#define ABSTRACTPLATFORM_H
#include <QLabel>


class AbstractPlatform {
    protected:
    QString soundPrefixPath = "requirments/Doodle Jump SFX/";
    int WIDTH = 120;
    int HEIGHT = 32;
    int coordinateX;
    int coordinateY;
    QString prefixPath;
    QString imagePath;
    public:
    void setY(int y);
    AbstractPlatform(const int coordinateX, const int coordinateY) ;
    AbstractPlatform(const int coordinateX, const int coordinateY, const int width) ;
    AbstractPlatform(const int coordinateX, const int coordinateY, const int width, const int height) ;
    int getX() const;
    int getY() const;

    int getWidth() const;
    int getHeight() const;
    virtual  QLabel* getQLabel(QWidget *parent = nullptr)  = 0;
    virtual ~AbstractPlatform() = default;
};



#endif //ABSTRACTPLATFORM_H

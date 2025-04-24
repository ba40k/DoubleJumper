//
// Created by radamir on 16.04.25.
//

#ifndef ABSTRACTPLATFORM_H
#define ABSTRACTPLATFORM_H
#include <QLabel>


class AbstractPlatform {
    protected:
    const int WIDTH = 120;
    const int HEIGHT = 32;
    int coordinateX;
    int coordinateY;
    QString prefixPath;
    QString imagePath;
    public:
    void setY(int y);
    virtual void setBroken();
    AbstractPlatform(const int coordinateX, const int coordinateY) ;
    AbstractPlatform(const int coordinateX, const int coordinateY, const int width) ;
    AbstractPlatform(const int coordinateX, const int coordinateY, const int width, const int height) ;

    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;
    virtual  QLabel* getQLabel(QWidget *parent = nullptr) const = 0;
    virtual ~AbstractPlatform() = default;
};



#endif //ABSTRACTPLATFORM_H

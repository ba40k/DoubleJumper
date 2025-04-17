//
// Created by radamir on 16.04.25.
//

#ifndef ABSTRACTPLATFORM_H
#define ABSTRACTPLATFORM_H



class AbstractPlatform {
    protected:
    const int WIDTH = 120;
    const int HEIGHT = 32;
    int coordinateX;
    int coordinateY;
    public:
    AbstractPlatform(const int coordinateX, const int coordinateY) ;
    virtual ~AbstractPlatform() = default;
};



#endif //ABSTRACTPLATFORM_H

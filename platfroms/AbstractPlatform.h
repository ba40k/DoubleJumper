//
// Created by radamir on 16.04.25.
//

#ifndef ABSTRACTPLATFORM_H
#define ABSTRACTPLATFORM_H



class AbstractPlatform {
    protected:
    const int width = 120;
    const int height = 32;
    int coordinateX;
    int coordinateY;
    public:
    AbstractPlatform(const int coordinateX, const int coordinateY) ;
    virtual ~AbstractPlatform() = 0;
};



#endif //ABSTRACTPLATFORM_H

#ifndef POINT_H
#define POINT_H

#include<iostream>
using namespace std;

class Point{
    public:
        float x,y;
        bool highlighted;
        Point():x(0), y(0), highlighted(false){}
        Point(float _x, float _y , bool _hightlighted=false){
            x = _x; y = _y; highlighted = _hightlighted;
        }
        void printPoint(){
            std::cout << x <<" " << y << std::endl;
        }
};

#endif // POINT_H
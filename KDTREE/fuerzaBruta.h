#ifndef FUERZABRUTA_H
#define FUERZABRUTA_H

#include"nodeKDTree.h"
#include<cmath>
#include<algorithm>
//La estructura de la fuerza bruta seŕa representado en  un vector de la stl

/*
point[0] = x
point[1] = y
point[2] = z
*/
class Point{
    public:
        std::vector<TYPE_POINT> point;
        double distance;
    public:
        Point(std::vector<TYPE_POINT> &p){
            for(size_t e = 0 ; e < K ; e++){
                point.push_back(p[e]);
            }
            distance = 0;
        }
        ~Point(){}
};

bool comparison(Point &a,Point &b){
    return (a.distance < b.distance);
}

class FuerzaBrutaKNN{
    private:
        std::vector<Point> points;
    public:
        FuerzaBrutaKNN(){}
        ~FuerzaBrutaKNN(){}


    void insert(Point &point){
        this->points.push_back(point);
    }

    vector<Point> KNN_search(Point &pointTest, int k){
        auto n = points.size();
        //calculate distance of all point 
        //with pointTest
        for(auto it = points.begin() ;it != points.end() ; it++){
            (*it).distance = sqrt(
                              ((*it).point[0]-pointTest.point[0])*((*it).point[0]-pointTest.point[0]) +
                              ((*it).point[1]-pointTest.point[1])*((*it).point[1]-pointTest.point[1]) +
                              ((*it).point[2]-pointTest.point[2])*((*it).point[2]-pointTest.point[2])
                            );
        }
        //sort the points by "distance"
        //merge sort of c++
        sort(points.begin(), points.end(),comparison);
        vector<Point> vec;
        for(size_t e = 0 ; e <k; e++){
            vec.push_back(points[e]);
        }
        return vec;
    }
    void print(){
        for(auto it = points.begin() ;it != points.end() ; it++){
            cout <<"("<< (*it).point[0] <<" - " << (*it).point[1] <<" - " << (*it).point[2] << ")" <<endl; 
        }
    }
};


#endif //FUERZABRUTA_H

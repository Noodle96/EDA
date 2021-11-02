#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "point.h"

class Rectangle{
    public:
        float x,y,w,h;
        Rectangle(float x,float y,float w,float h): x(x),y(y),w(w),h(h){}
        bool contains(const Point &p)const{
            return p.x >=x-w && p.x <= x + w &&
                    p.y >= y-h && p.y <= y + h ;
        }

        bool intersects(const Rectangle &other)const{
            return !(x-w > other.x + other.w || 
                        x+w < other.x - other.w ||
                        y-h > other.y + other.h ||
                        y+h < other.y - other.h
                    );
        }

        void draw(RenderTarget &t){
            static Vertex vertices[5];
            vertices[0] = Vertex(Vector2f(x-w,y-h), Color::Magenta);
            vertices[1] = Vertex(Vector2f(x+w,y-h), Color::Magenta);
            vertices[2] = Vertex(Vector2f(x+w,y+h), Color::Magenta);
            vertices[3] = Vertex(Vector2f(x-w,y+h), Color::Magenta);
            vertices[4] = Vertex(Vector2f(x-w,y-h), Color::Magenta);
            t.draw(vertices,5,LineStrip);
        }
};

#endif //RECTANGLE_H
#ifndef QUADTREE_H
#define QUADTREE_H

#include "rectangle.h"
#define SCREEN_W 600
#define SCREEN_H 600
#define LEVELMAX 4
#define CAPACITY 1

class QuadTree{
    private:
        QuadTree *topLeft;
        QuadTree *TopRight;
        QuadTree *bottomLeft;
        QuadTree *bottomRight;
        Rectangle boundaries;
        bool divided;
        size_t capacity;
        size_t level;
        vector<Point *>children;
        
        void subdivide(){
            cout << "Subdivide-----------------------------------------------------------" << endl;
            static Vector2f halfSize;
            halfSize.x = boundaries.w / 2.0f;
            halfSize.y = boundaries.h / 2.0f;

            topLeft = new QuadTree(
                        Rectangle(boundaries.x - halfSize.x,
                                    boundaries.y -halfSize.y,
                                    halfSize.x,halfSize.y),
                        capacity, level +1
            );
            TopRight = new QuadTree(
                        Rectangle(boundaries.x  + halfSize.x,
                                    boundaries.y - halfSize.y,
                                    halfSize.x, halfSize.y),
                        capacity,level +1
            );
            bottomLeft = new QuadTree(
                        Rectangle(boundaries.x - halfSize.x,
                                    boundaries.y + halfSize.y,
                                    halfSize.x, halfSize.y),
                        capacity, level +1
            );
            bottomRight = new QuadTree(
                            Rectangle(boundaries.x + halfSize.x,
                                        boundaries.y + halfSize.y,
                                        halfSize.x,halfSize.y),
                            capacity, level +1 
            );
            divided = true;
        }

    public:
        QuadTree(const Rectangle &boundaries, size_t capacity,
                size_t level):
            topLeft(nullptr),
            TopRight(nullptr),
            bottomLeft(nullptr),
            bottomRight(nullptr),
            boundaries(boundaries),
            divided(false),
            capacity(capacity),
            level(level){
                //cout << "milevel: " << level << endl;
                if(level >= LEVELMAX){
                     this->capacity = 0;
                     cout << "Asigning capacity = zero" <<endl;
                }
                 //cout << "milevel: " << level << endl;
                 //cout << "micapacity: " << capacity << endl;
                 //cout << "Inside if" <<endl;
        }
        
        ~QuadTree(){
            if(divided){
                //delete topLeft;
                //delete TopRight;
                //delete bottomLeft;
                //delete bottomRight;
            }
        }

        bool insert(Point *p){
            if(!boundaries.contains(*p)) return false;
            if(!divided){
                children.push_back(p);
                //cout << "BOOLENANO: "<< capacity << "- is: " << (capacity != 0) << endl;
                if(children.size() > capacity && (capacity != 0)){
                    //cout << "CAPACITY: " <<capacity << endl;
                    //cout << "SUBDIVIDE IN " << endl;
                    //p->printPoint();
                    subdivide();
                    auto it = children.begin();
                    while(it != children.end()){
                        //cout << "Level: " << level << endl;
                        (*it)->printPoint();
                        if(topLeft->insert(*it));
                        else if(TopRight->insert(*it));
                        else if(bottomLeft->insert(*it));
                        else if(bottomRight->insert(*it));
                        it = children.erase(it);
                    }

                }
                return true;
            }
            else{
                if(topLeft->insert(p)) return true;
                else if(TopRight->insert(p)) return true;
                else if(bottomLeft->insert(p)) return true;
                else if(bottomRight->insert(p)) return true;
                return false;
            }
        }

        void query(const Rectangle &area, vector<Point*> &found)const{    
            if(!area.intersects(boundaries)) return;
            if(divided){
                topLeft->query(area,found);
                TopRight->query(area,found);
                bottomLeft->query(area,found);
                bottomRight->query(area,found);
            }else{
                for(size_t e = 0 ; e < children.size(); e++){
                    if(area.contains(*children[e])){
                        found.push_back(children[e]);
                    }
                }
            }
        }

        void draw(RenderTarget &t){ //draw Cruz
            if(divided){
                static Vertex vertices[4];
                vertices[0] = Vertex(Vector2f(boundaries.x,
                                    boundaries.y-boundaries.h),
                                   Color::Blue);
                vertices[1] = Vertex(Vector2f(boundaries.x,
                                    boundaries.y+boundaries.h),
                                   Color::Blue);
                vertices[2] = Vertex(Vector2f(boundaries.x - boundaries.w,
                                    boundaries.y),
                                   Color::Blue);
                vertices[3] = Vertex(Vector2f(boundaries.x + boundaries.w,
                                    boundaries.y),
                                   Color::Blue);
                t.draw(vertices,4,Lines);
                topLeft->draw(t);
                TopRight->draw(t);
                bottomLeft->draw(t);
                bottomRight->draw(t);

            }
        }

};

#endif // QUADTREE_H
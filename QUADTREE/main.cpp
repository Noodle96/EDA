
#include"point.h"
#include<vector>
#include <SFML/Graphics.hpp>
// g++ main.cpp  -lsfml-graphics -lsfml-window -lsfml-system

using namespace sf;
#include "quadTree.h"

int main()
{
	sf::RenderWindow window(
		sf::VideoMode(SCREEN_W, SCREEN_H),
		"Quad Tree");
	//sf::CircleShape shape(200);
    QuadTree quadtree(Rectangle(SCREEN_W/2, SCREEN_H/2,
                                SCREEN_W/2, SCREEN_W/2 ),
                      CAPACITY,0
    );


    Point *po;
    vector<Point *> points;
    vector<Point *> found;
    CircleShape shape;
    shape.setRadius(3);
    shape.setOrigin(3,3);
    Rectangle area(200,200,100,100); //Initial Position
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed) window.close();
            else if(event.type == sf::Event::MouseButtonPressed &&
                    event.mouseButton.button == Mouse::Left){
                        po = new Point(Mouse::getPosition(window).x,
                                Mouse::getPosition(window).y);
                        //po->printPoint();
                        points.push_back(po);
                        quadtree.insert(po) ;
                    }
            //TO MOVE BOUNDARIE QUERY
            else if(event.type == sf::Event::MouseMoved){
                if(Mouse::isButtonPressed(Mouse::Right)){
                    area.x = Mouse::getPosition(window).x;
                    area.y = Mouse::getPosition(window).y;
                }
            }
        }

        //50 PUNTOS ALEATORIOS
        //num=1+rand()%(101-1);
        //srand(time(NULL));
        //for(size_t e = 0 ; e<10; e++){
            //po = new Point( rand()%(SCREEN_W),
            //                    rand()%(SCREEN_W));
            //points.push_back(po);
            //quadtree.insert(po) ;
        //}
        for(size_t e = 0 ; e < points.size(); e++){
            points[e]->highlighted = false;
        }
        found = vector<Point *>();
        //found = points;
        
        quadtree.query(area,found);
        for(size_t e = 0 ; e <found.size();e++){
            found[e]->highlighted = true;
        }
		window.clear();
		//window.draw(shape);
        for(Point *p : points){
            shape.setPosition(p->x,p->y);
            shape.setFillColor(p->highlighted?Color::Green:Color::White);
            window.draw(shape);
        }

        quadtree.draw(window);
        area.draw(window);
		window.display();
	}
	return 0;
}
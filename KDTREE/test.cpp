#include<iostream>
#include<iomanip>
using namespace std;

#include"nodeKDTree.h"

int main(){
	TYPE_POINT list[] = {};
	NodeKDTREE nodeInitial(list);
	TYPE_POINT *get = nodeInitial.getPoint();
	for(auto e = 0 ; e <K; e++){
		//cout << get[e] << " ";
		get[e] =get[e]*10;
	}cout << endl;

	/*
	for(auto e = 0 ; e <K; e++){
		cout << get[e] << " ";
		//get[e] =get[e]*10;
	}cout << endl;*/
	TYPE_POINT *get2 = nodeInitial.getPoint();
	for(auto e = 0 ; e <K; e++){
		cout << get2[e] << " ";
		//get[e] =get[e]*10;
	}cout << endl;

    cout << "%%%%%%%%%\n";
    for(auto e = 0 ; e < 10 ; e++){
        cout << "In " << e << endl;
        cout << e % K << endl;
    }
	cout << "IOMANIP" << endl;
	float a = 12.123456789;
	std::cout << std::fixed << std::setprecision(3);
	cout << a << endl;
	return 0;
}
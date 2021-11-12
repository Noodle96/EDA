#include<iostream>
#include<iomanip>
#include<algorithm>
using namespace std;

#include"nodeKDTree.h"

int main(){
	//TYPE_POINT list[] = {};
	/*
	std::vector<TYPE_POINT> list;
	NodeKDTREE nodeInitial(list);
	std::vector<TYPE_POINT>get = nodeInitial.getPoint();
	for(auto e = 0 ; e <K; e++){
		//cout << get[e] << " ";
		get[e] =get[e]*10;
	}cout << endl;
	*/
	/*
	for(auto e = 0 ; e <K; e++){
		cout << get[e] << " ";
		//get[e] =get[e]*10;
	}cout << endl;*/
	/*
	std::vector<TYPE_POINT> get2 = nodeInitial.getPoint();
	for(auto e = 0 ; e <K; e++){
		cout << get2[e] << " ";
		//get[e] =get[e]*10;
	}cout << endl;
	*/
    cout << "%%%%%%%%%\n";
    for(auto e = 0 ; e < 10 ; e++){
        cout << "In " << e << endl;
        cout << e % K << endl;
    }
	cout << "IOMANIP" << endl;
	float a = 12.123456789;
	std::cout << std::fixed << std::setprecision(3);
	cout << a << endl;


	cout << "Testing sort vector" << endl;
	std::vector<int> vecS;
	vecS.push_back(10);vecS.push_back(2);vecS.push_back(5);
	for(auto it = vecS.begin() ; it!= vecS.end(); it++){
		cout << *it << " " ;
	}cout << endl;
	std::sort(vecS.begin(), vecS.end());
	for(auto it = vecS.begin() ; it!= vecS.end(); it++){
		cout << *it << " " ;
	}cout << endl;
	return 0;
}
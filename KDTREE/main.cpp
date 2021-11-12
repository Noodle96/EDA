#include"kdTree.h"

void splitLine(std::string line,std::vector<TYPE_POINT> &vectorF){
	std::string temp = "";
	float g;
	for(auto it = line.begin() ; it != line.end(); it++){
		if(*it != ',') temp+=*it;
		else{
			g = std::stof(temp);
			vectorF.push_back(g);
			temp = "";
		}
	}
	g = std::stof(temp);
	vectorF.push_back(g);
	//cout << "printing vector" << endl;
	//for(size_t e = 0 ; e < vectorF.size(); e++){
	//	cout << vectorF[e] << " ";
	//}cout << endl;

}
int main(){

	KdTree *kdtree = new KdTree();
	/*
	TYPE_POINT a[] = {2,8,7};
	TYPE_POINT b[] = {1,4,5};
	TYPE_POINT c[] = {10,16,18};
	TYPE_POINT d[] = {7,10,15};
	TYPE_POINT e[] = {6,20,3};
	TYPE_POINT f[] = {100,15,8}; */

	//READING A FILE testX.csv ANF INSERT IN KDTREE
	std::string line;
	std::vector<TYPE_POINT> vectorTemp;
  	ifstream myfile ("testX.csv");
  	if (myfile.is_open()) {
    	while( getline (myfile,line) ){
     		//cout << line << '\n';
			 if(!line.empty()){
				splitLine(line,vectorTemp);
				kdtree->insert(kdtree->root,vectorTemp,0);
				vectorTemp.clear();
			 }

    	}
    myfile.close();
  	}

	/*
	std::vector<TYPE_POINT> vectorTest;
	splitLine("1.7217,0.020054,0.20361",vectorTest);
	for(auto it = vectorTest.begin() ; it != vectorTest.end(); it++){
		cout << *it<<" ";
	}cout << endl;
	*/


	
	/*
	kdtree->insert(kdtree->root,a,0);
	kdtree->insert(kdtree->root,b,0);
	kdtree->insert(kdtree->root,c,0);
	kdtree->insert(kdtree->root,d,0);
	kdtree->insert(kdtree->root,e,0);
	kdtree->insert(kdtree->root,f,0);
	*/

	kdtree->draw();
	
	return 0;
}

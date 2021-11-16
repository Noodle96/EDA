#include"kdTree.h"
#include"fuerzaBruta.h"

#include<fstream>
#include<chrono>
#include<algorithm>
#define KDTREE 0.1
#define BRUTEFORCE 0.5

using namespace std::chrono;

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
	int CONT_KDTREE = 0;
	std::string line;
	std::vector<TYPE_POINT> vectorTemp;
  	ifstream myfile ("testX.csv");
	std::chrono::time_point<std::chrono::high_resolution_clock> start;
	std::chrono::time_point<std::chrono::high_resolution_clock> stop;
	std::chrono::microseconds duration(0);
	fstream fileToTableComparationInsertKdtree;
    fileToTableComparationInsertKdtree.open("fileToTableComparationInsertKdtree.csv",ios::out);

  	if (myfile.is_open()) {
    	while( getline (myfile,line) ){
     		//cout << line << '\n';
			 if(!line.empty()){
				CONT_KDTREE ++;
				splitLine(line,vectorTemp);

				//////////////////////////////////////////////////////////////////
				// medicion del tiempo
        		start = std::chrono::high_resolution_clock::now(); //INICIO
				kdtree->insert(kdtree->root,vectorTemp,0);
    		    stop = std::chrono::high_resolution_clock::now(); // FINAL
				//////////////////////////////////////////////////////////////////
				vectorTemp.clear();
				duration += duration_cast<microseconds>(stop - start);


				//insert in the file "name..." to generate the rect to function insert In Kdtree
				if(CONT_KDTREE % 1160 == 0){
					//cout << "Points: " <<CONT_KDTREE << "time: " << duration.count() << endl;
					fileToTableComparationInsertKdtree << CONT_KDTREE<<","<<duration.count() << endl;
				}
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


	/*
		generate .dot file. then run with
		dot -Tpng kdtree.dot -o kdtree.png
		output: the png with the tree of point 
		of "testX.csv" file.
	*/
	kdtree->draw();
	//1.64,0.092,0.45
	std::vector<TYPE_POINT> target; target.push_back(1.64);target.push_back(0.092);target.push_back(0.45);

	// medicion del tiempo KNN in kdtree
	auto start_ = std::chrono::high_resolution_clock::now(); //INICIO
	NodeKDTREE *knnKDT =   kdtree->nearestNeighbor(kdtree->root,target,0);
	auto stop_ = std::chrono::high_resolution_clock::now(); // FINAL
	auto duration_ = duration_cast<microseconds>(stop_ - start_);
	//cout << "Time knn in kdtree  "<<duration.count() << endl;
	fstream fileKNNKdtreeBruteForceTime;
	fileKNNKdtreeBruteForceTime.open("kdtree_time_knn_VS_bruteForce_time_knn.csv",ios::app);
	fileKNNKdtreeBruteForceTime << KDTREE << "," <<duration_.count() << endl;
	
	fstream fileKNN;
    fileKNN.open("kdtree_knn.csv",ios::app);
	knnKDT->printPoint(fileKNN);
	fileKNN.close();
	delete kdtree;





	/*	TESTING WITH THE FORCE BRUTE
		DATA STRUCT : VECTOR STL
	*/

	FuerzaBrutaKNN *fb = new FuerzaBrutaKNN();

	std::string LINE;
	std::vector<TYPE_POINT> vectorTemporal;
  	ifstream file ("testX.csv");
	std::chrono::time_point<std::chrono::high_resolution_clock> startFB;
	std::chrono::time_point<std::chrono::high_resolution_clock> stopFB;
	std::chrono::microseconds durationFB(0);
	fstream fileToTableComparationInserBruteForce;
    fileToTableComparationInserBruteForce.open("fileToTableComparationInsertBruteForce.csv",ios::out);
	int CONT_FORCEBRUTE = 0;

  	if (file.is_open()) {
    	while( getline (file,LINE) ){
			 if(!LINE.empty()){
				CONT_FORCEBRUTE ++;
				splitLine(LINE,vectorTemporal);
				Point ptemp(vectorTemporal);

				//////////////////////////////////////////////////////////////////
				// medicion del tiempo
        		startFB = std::chrono::high_resolution_clock::now(); //INICIO
				fb->insert(ptemp);
    		    stopFB = std::chrono::high_resolution_clock::now(); // FINAL
				//////////////////////////////////////////////////////////////////
				vectorTemporal.clear();
				durationFB += duration_cast<microseconds>(stopFB - startFB);

				//insert in the file "name..." to generate the rect to function insert In BruteForce
				if(CONT_FORCEBRUTE % 1160 == 0){
					//cout << "Points: " <<CONT_KDTREE << "time: " << duration.count() << endl;
					fileToTableComparationInserBruteForce << CONT_FORCEBRUTE<<","<<durationFB.count() << endl;
				}
			}
    	}
    file.close();
  	}
	//1.64,0.092,0.45
	std::vector<TYPE_POINT> pointTest;
	pointTest.push_back(1.64); pointTest.push_back(0.092); pointTest.push_back(0.45);
	Point pointTesting(pointTest);

	auto start__ = std::chrono::high_resolution_clock::now(); //INICIO
	auto knn = fb->KNN_search(pointTesting,2);
	auto stop__ = std::chrono::high_resolution_clock::now(); //INICIO
	auto duration__ = duration_cast<microseconds>(stop__ - start__);
	fileKNNKdtreeBruteForceTime << BRUTEFORCE << "," << duration__.count() << endl;
	fileKNNKdtreeBruteForceTime.close();


	//for(auto it = knn.begin() ; it!= knn.end(); it++){
	//	for(auto et = (*it).point.begin() ; et != (*it).point.end(); et++){
	//		cout << "{" << *et <<", ";
	//	}cout << "}";
	//}
	//cout << "printing" << endl;
	//fb->print();

	delete fb;

	
	return 0;
}

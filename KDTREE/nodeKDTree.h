#ifndef NODEKDTREE_h
#define NODEKDTREE_h

#include<iostream>
#include<fstream>
#include<sstream>
#include<queue>
using namespace std;

using TYPE_POINT = float;
#define K 3

/*
    This class represent the node of kdtree
*/
class NodeKDTREE{
    public:
        //TYPE_POINT m_point[K];
        std::vector<TYPE_POINT> m_point;
        NodeKDTREE *m_pLeft;
        NodeKDTREE *m_pRight; 
    public:
    NodeKDTREE(std::vector<TYPE_POINT> list){ //non-empty list - TYPE_POINT *list
        for(size_t e = 0 ;e < K ; e++)
            //this->m_point[e] = list[e];
            this->m_point.push_back(list[e]);

        m_pLeft = NULL;
        m_pRight = NULL;
    }
    ~NodeKDTREE(){}

    std::string pointToString(){
        string num_str="\"(";
        for(size_t e = 0 ; e < K; e++){
            //str += to_string(m_point[e]);
            std::stringstream sstream;
            sstream << m_point[e];
            num_str += sstream.str();
            if(e != K-1) num_str += " , ";
        }
        num_str += ")\"";
        return num_str;
    }

};

#endif // NODEKDTREE_h
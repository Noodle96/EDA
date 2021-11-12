#ifndef KDTREE_H
#define KDTREE_H

#include"nodeKDTree.h"

class KdTree{
    public:
        NodeKDTREE *root;
    public:
        KdTree(){}
        ~KdTree(){}

        bool insert(NodeKDTREE *&node, std::vector<TYPE_POINT> point, int depth){
            if(node == NULL){
                //cout << "first if" << endl;
                node = new NodeKDTREE(point);
                return true;
            }
            // calculate current dimension to compare
            unsigned short currentDimension = depth % K;
            if(point[currentDimension] < (node->m_point[currentDimension]))
                insert(node->m_pLeft,point,depth + 1);
            else
                insert(node->m_pRight,point,depth + 1);
        }

        void draw(){
            std::fstream file;
            file.open("kdtree.dot", std::ios::out);
            file << "digraph ll {" << std::endl;
            file <<"\tnode [shape=Mrecord];"<<endl;

            queue<NodeKDTREE*> *treeQueue = new queue<NodeKDTREE*>();
            NodeKDTREE *nodeTemp;
            treeQueue->push(root);
            
            while(!treeQueue->empty()){
                nodeTemp = treeQueue->front(); treeQueue->pop();
                //print point
                //for(size_t e = 0 ; e < K; e++){
                    //cout << nodeTemp->m_point[e]<< ", ";
                //}cout << endl;
                file << "\t"<<nodeTemp->pointToString() << endl;
                if(nodeTemp->m_pLeft){
                    file << "\t" << nodeTemp->pointToString() << " -> " <<nodeTemp->m_pLeft->pointToString()<<endl;
                    treeQueue->push(nodeTemp->m_pLeft);
                }
                if(nodeTemp->m_pRight){
                    file << "\t" << nodeTemp->pointToString() << " -> " <<nodeTemp->m_pRight->pointToString()<<endl;
                    treeQueue->push(nodeTemp->m_pRight);
                }
            }

            file << "}\n";
        }

        bool arePointsSame(std::vector<TYPE_POINT> &point1, std::vector<TYPE_POINT> &point2){
            for(size_t e = 0 ; e <K; e++){
                if(point1[e] != point2[e]) return false;
            }
            return true;
        }

        bool search(NodeKDTREE *node,std::vector<TYPE_POINT> &point, int depth){
            //casos base
            if(node == NULL) return false;
            if(arePointsSame(point,node->m_point)) return true;

            //calculano la actual dimension
            unsigned short currentDimension = depth % K;
            if(point[currentDimension] < node->m_point[currentDimension])
                return search(node->m_pLeft,point,depth+1);
            return search(node->m_pLeft,point,depth+1);
        }
};




#endif //KDTREE_H

#ifndef KDTREE_H
#define KDTREE_H

#include"nodeKDTree.h"
#include<cmath>

TYPE_POINT distance(std::vector<TYPE_POINT> &point1,std::vector<TYPE_POINT> &point2){
    return sqrt(
        (point1[0]-point2[0])*(point1[0]- point2[0]) +
        (point1[1]-point2[1])*(point1[1]- point2[1]) +
        (point1[2]-point2[2])*(point1[2]- point2[2])
    );
}



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


        //util function to nearestNeighbor
        // Determines whether n0 or n1 is closer to the target.
        NodeKDTREE *closest(NodeKDTREE *n0, NodeKDTREE *n1, std::vector<TYPE_POINT> &target){
            if(n0 == NULL) return n1;
            if(n1 == NULL) return n0;
            TYPE_POINT d1 = distance(n0->m_point,target);
            TYPE_POINT d2 = distance(n1->m_point,target);
            if(d1<d2) return n0;
            else return n1;
        }


        //vecinos mas cercanos (KNN)
        NodeKDTREE *nearestNeighbor(NodeKDTREE *node,std::vector<TYPE_POINT> &target, int depth){
            if(node == NULL) return NULL;
            NodeKDTREE *nextBranch = NULL;
            NodeKDTREE *otherBranch =  NULL;
            if(target[depth%K] < node->m_point[depth%K]){
                nextBranch = node->m_pLeft;
                otherBranch = node->m_pRight;
            }else{
                nextBranch = node->m_pRight;
                otherBranch = node->m_pLeft;
            }
            // recurse down
            NodeKDTREE *temp = nearestNeighbor(nextBranch,target,depth+1);
            NodeKDTREE *best = closest(temp,node,target);

            long radiusSquared = distance(target,best->m_point); //r
            long dist = target[depth%K] - node->m_point[depth%K]; //rp

            if(radiusSquared >= dist*dist){ //other side
                temp = nearestNeighbor(otherBranch,target,depth+1);
                best = closest(temp,best,target);
            }
            return best;
        }

};




#endif //KDTREE_H

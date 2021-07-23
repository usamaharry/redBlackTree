#include<iostream>
#include"node.h"

using namespace std;



class Tree {
protected:
	Node* rootNode;

public:

	virtual void insert(int data) = 0;


	virtual void inOrderLNR() = 0;
	virtual void inOrderRNL() = 0;

	virtual void preOrderNLR() = 0;
	virtual void preOderNRL() = 0;

	virtual void postOrderLRN() = 0;
	virtual void postOrderRLN() = 0;

	virtual bool search(int val) = 0;

	virtual bool remove(int val) = 0;

	virtual void printParent(int val) = 0;

	virtual void deleteDuplicated() = 0;

	virtual void destroyTree() = 0;
	
};
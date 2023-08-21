#include "BinaryDecisionTree.hpp"

#include <iostream>

BinaryDecisionTree::BinaryDecisionTree() {
}

BinaryDecisionTree::BinaryDecisionTree(BinaryDataset *dataset) { 
	// intialize root node
	BinaryNode *root_node = new BinaryNode();
	this->root = root_node;

	// recursively call private method growTree with root node
	this->growTree(dataset,this->root);
}

BinaryDecisionTree::~BinaryDecisionTree() { 
	// recursively call private method deleteSubtree with root node
	this->deleteSubtree(this->root);

	// reset root node
	this->root = nullptr;
}

void BinaryDecisionTree::print() {
	this->print(this->getRoot(), 1);
}

void BinaryDecisionTree::print(BinaryNode *node_in, int level) {

  BinaryNode* currentNode = node_in;
  BinaryNode* currentYNode = node_in->getNodeY();
  BinaryNode* currentNNode = node_in->getNodeN();
  int indentlevel = level;

  if (currentNode != 0){

    //Print the current node
    std::cout<<currentNode->getDecisionDim()<<"  "<<currentNode->getDecisionCriterion()<<"  "
    <<currentNode->getImpurity()<<"  "<<currentNode->getLabel()<<"\n";//std::endl;

    if (currentYNode != 0){
      //Print out the Yes node
      for (int i=0; i<indentlevel; i++){
        std::cout<<'\t';
      }
      print(currentYNode, indentlevel+1);
      //Print out the No node
      for (int i=0; i<indentlevel; i++){
        std::cout<<'\t';
      }
      print(currentNNode, indentlevel+1);
    }

  }

}

BinaryNode * BinaryDecisionTree::getRoot() {
	return this->root;
}

int BinaryDecisionTree::classify(double *ft_in) {
	// get the current node and it's children nodes
	BinaryNode *currNode = this->root;
	BinaryNode *leftNode = currNode->getNodeY();
	BinaryNode *rightNode = currNode->getNodeN();

	// while the current node isn't a leaf
	while (!currNode->isLeaf()) {
		// if the split criterion of the double array at the split dimension
		// is smaller than the current node
		if (ft_in[currNode->getDecisionDim()] <
				currNode->getDecisionCriterion()) {

			// go down left subtree and update node details
			currNode = leftNode;
			leftNode = currNode->getNodeY();
			rightNode = currNode->getNodeN();

			// if the split criterion of the double array at the split dimension
			// is larger or equal than the current node
		} else {

			// go down right subtree and update node details
			currNode = rightNode;
			leftNode = currNode->getNodeY();
			rightNode = currNode->getNodeN();
		}
	}

	// return classification of observation via label of leaf node
	return currNode->getLabel();
}

void BinaryDecisionTree::growTree(BinaryDataset *dataset_in, BinaryNode *node_in) {
	// initialize empty datasets and nodes
	BinaryDataset *dataset_Y = new BinaryDataset();
	BinaryDataset *dataset_N = new BinaryDataset();
	BinaryNode *nodeY_new = new BinaryNode();
	BinaryNode *nodeN_new = new BinaryNode();

	// initialize optimal split observation and dimension indexes
	unsigned int optimal_dim, optimal_ixobs;
	unsigned int *out_dim = &optimal_dim;
	unsigned int *out_ix = &optimal_ixobs;

	// set the impurity entropy and majority label of current node
	node_in->setImpurity(dataset_in->calcImpurityEntropy());
	node_in->setLabel(dataset_in->getMajorityLabel());

	// while the dataset is not pure, not a leaf node
	if(dataset_in->calcImpurityEntropy() != 0.0) {

		// set the children node of the current node
		node_in->setNodeY(nodeY_new);
		node_in->setNodeN(nodeN_new);

		// find the optimal split indexes of current dataset and split at these indexes
		dataset_in->findOptimalSplit(out_dim,out_ix);
		dataset_in->split(optimal_dim,optimal_ixobs,dataset_Y,dataset_N);

		// set the split dimension and criterion of current node
		node_in->setDecisionDim(optimal_dim);
		node_in->setDecisionCriterion(dataset_in->getCriterion(optimal_ixobs,optimal_dim));

		// call growTree recursively on each of the children nodes until pure dataset/leaf node is reached
		this->growTree(dataset_Y,node_in->getNodeY());
		this->growTree(dataset_N,node_in->getNodeN());

	}

	// delete heap variables
	delete dataset_Y;
	delete dataset_N;
}

void BinaryDecisionTree::deleteSubtree(BinaryNode *node_in) {
	// return if the dataset is already empty
	if(node_in == nullptr) {
		return;
	}

	// recursively call deleteSubtree on each of child node until leaf node is reached
	if (node_in->getNodeY() != nullptr) {
		deleteSubtree(node_in->getNodeY());
	}
	if (node_in->getNodeN() != nullptr) {
		deleteSubtree(node_in->getNodeN());
	}

	// delete the initial node
	delete(node_in);
}

unsigned int BinaryDecisionTree::size() { 
	// recursively call private method leafCount with root node
	return leafCount(this->root);
}

unsigned int BinaryDecisionTree::leafCount(BinaryNode *node_in) {
	// return if the dataset is already empty
	if (node_in == nullptr) {
		return 0;
	}

	// if input node is already a leaf node, return 1
	if ((node_in->getNodeY() == nullptr) &&
			(node_in->getNodeN() == nullptr)) {
		return 1;
		// else, recursively call leafCount on each subtree of input node and add them
		// to get total leaf count
	} else {
		return leafCount(node_in->getNodeY())+leafCount(node_in->getNodeN());
	}
}

void BinaryDecisionTree::setRoot(BinaryNode *node_in) {
	this->root = node_in;
}

bool BinaryDecisionTree::isEmpty() {
	// return false if the tree is empty (root is not nullptr), true if else
	if (this->root != nullptr) {
		return false;
	}
	return true;
}



#include "BinaryNode.hpp"
#include <iostream>

BinaryNode::BinaryNode() {
}

BinaryNode::~BinaryNode() {
}

bool BinaryNode::isLeaf() {
	// returns true if the node in question has no children nodes
	if (this->nodeY == nullptr && this->nodeN == nullptr) {
		return true;
	}
	// returns false if the node has children nodes
	return false;
}

// Getters and setters
BinaryNode * BinaryNode::getNodeY() {
	return this->nodeY;
}

BinaryNode * BinaryNode::getNodeN() {
	return this->nodeN;
}

void BinaryNode::setNodeY(BinaryNode *node_in) {
	this->nodeY = node_in;
}

void BinaryNode::setNodeN(BinaryNode *node_in) {
	this->nodeN = node_in;
}

void BinaryNode::setDecisionDim(unsigned int dim_in) {
	// set feature dimension of this node for valid dimension
	if (dim_in < 10) {
		this->decisionDimension = dim_in;
	}
}

unsigned int BinaryNode::getDecisionDim() {
	return this->decisionDimension;
}

void BinaryNode::setDecisionCriterion(double criterion_in) {
	this->decisionCriterion = criterion_in;
}

double BinaryNode::getDecisionCriterion() {
	return this->decisionCriterion;
}

void BinaryNode::setLabel(int label_in) {
	// set decision label of this node for valid label
	if (label_in == 1 || label_in == -1) {
		this->majorityLabel = label_in;

		// set decision label of -1 for label inputs lesser than valid
	} else if (label_in < 1) {
		this->majorityLabel = -1;

		// set decision label of 1 for label inputs greater than valid
	} else if (label_in > 1) {
		this->majorityLabel = 1;
	}
}

int BinaryNode::getLabel() {
	return this->majorityLabel;
}

void BinaryNode::setImpurity(double impurity_in) {
	// set impurity of this node for valid impurity
	if (impurity_in >= 0.0 && impurity_in <= 1.0) {
		this->impurityEntropy = impurity_in;

	} else if (impurity_in < 0.0) {
		// set impurity of 0.0 for impurity inputs less than valid
		this->impurityEntropy = 0.0;

	} else if (impurity_in > 1.0) {
		// set impurity of 1.0 for impurity inputs greater than valid
		this->impurityEntropy = 1.0;
	}
}

double BinaryNode::getImpurity() {
	return this->impurityEntropy;
}

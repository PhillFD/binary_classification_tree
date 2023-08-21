#ifndef BINARYDECISIONTREE_HPP_
#define BINARYDECISIONTREE_HPP_

#include "BinaryNode.hpp"
#include "BinaryDataset.hpp"

class BinaryDecisionTree {
public:
	// Constructors and destructors
	BinaryDecisionTree();
	BinaryDecisionTree(BinaryDataset *);
	virtual ~BinaryDecisionTree();

	// Getters and setters
	BinaryNode * getRoot();
	void setRoot(BinaryNode *);

	// Other methods
	int classify(double *);
	void print();
	unsigned int size();
	bool isEmpty();
private:
	BinaryNode *root = nullptr;
	// Private methods
	void print(BinaryNode *, int);
	void growTree(BinaryDataset *, BinaryNode *);
	void deleteSubtree(BinaryNode *);
	unsigned int leafCount(BinaryNode *);
};

#endif /* BINARYDECISIONTREE_HPP_ */

#ifndef BINARYNODE_HPP_
#define BINARYNODE_HPP_

class BinaryNode {
public:
	// Constructors and destructors
	BinaryNode();
	virtual ~BinaryNode();
	bool isLeaf();

	// Setters and getters
	BinaryNode * getNodeY();
	BinaryNode * getNodeN();
	void setNodeY(BinaryNode *);
	void setNodeN(BinaryNode *);
	void setDecisionDim(unsigned int);
	unsigned int getDecisionDim();
	void setDecisionCriterion(double);
	double getDecisionCriterion();
	void setLabel(int);
	int getLabel();
	void setImpurity(double);
	double getImpurity();
private:
	BinaryNode *nodeY = nullptr;
	BinaryNode *nodeN = nullptr;
	int majorityLabel = -1;
	unsigned int decisionDimension = 0;
	double decisionCriterion = 0.0;
	double impurityEntropy = 0.0;
};

#endif /* BINARYNODE_HPP_ */

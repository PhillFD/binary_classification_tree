#ifndef BINARYDATASET_HPP_
#define BINARYDATASET_HPP_

#define MAX_OBSERVATIONS 500
#define MAX_NUM_FEATURES 10

class BinaryDataset {
public:
	// Constructors and deconstructors
	BinaryDataset();
	BinaryDataset(const char *, unsigned int);

	virtual ~BinaryDataset();

	// Getters and setters
	void setNumFeatures(unsigned int);
	unsigned int getNumFeatures();
	void getObservation(unsigned int, double *);
	void setObservation(unsigned int, double *);
	void setLabel(unsigned int, int);
	int getLabel(unsigned int);
	unsigned int getNumObservations();
	void setNumObservations(unsigned int);
	double getCriterion(unsigned int, unsigned int);

	// Other methods
	void print(bool);
	void split(unsigned int, unsigned int, BinaryDataset *, BinaryDataset *);
	void splitLOO(unsigned int, BinaryDataset *, BinaryDataset *);
	void findOptimalSplit(unsigned int *, unsigned int *);
	double calcImpurityEntropy();
	double calcImpurityDrop(BinaryDataset *, BinaryDataset *);
	int getMajorityLabel();
	bool isEmpty();
	void appendObservation(double *, int);
	void zero();
private:
	double dataset[MAX_OBSERVATIONS][MAX_NUM_FEATURES+1] = {0.0};
	unsigned int numFeatures = 0;
	unsigned int numObservations = 0;
	unsigned int posOneCount = 0;
	unsigned int negOneCount = 0;
	// Private methods
	void countMajorityLabel();
	bool isObservationEmpty(unsigned int);
};

#endif /* BINARYDATASET_HPP_ */

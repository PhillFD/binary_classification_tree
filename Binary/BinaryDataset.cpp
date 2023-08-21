#include "BinaryDataset.hpp"
#include <iostream>
#include <fstream>
#include <cmath>

BinaryDataset::BinaryDataset() {
}

BinaryDataset::BinaryDataset(const char *filename_in, unsigned int num_features) {
	// initializing variables
	this->numFeatures = num_features;
	double feature;
	std::fstream fs_filename_in(filename_in, std::ios_base::in);

	// display error message if file is not opened properly
	if (!fs_filename_in) {
		std::cerr << "Error: file could not be opened" << std::endl;
		exit(1);
	} else {
		// while loop reads in the data double by double,
		while (fs_filename_in >> feature) {

			// loops through all the features in one line (observation)
			// breaks when all features are read, and exits loop to read next observation
			for (unsigned int i = 0; i < numFeatures; i++) {
				// assigns the double to the ith feature of the observation
				dataset[numObservations][i] = feature;
				// gets the next double
				fs_filename_in >> feature;
			}
			// assigns the label for the observation to the last column
			dataset[numObservations][numFeatures] = feature;
			// increments the number of total observations
			numObservations++;
		}
	}
	// close opened file
	fs_filename_in.close();
}

BinaryDataset::~BinaryDataset() { 
}

bool BinaryDataset::isEmpty() {
	// return true if dataset is empty, else false
	return this->numObservations == 0;
}

void BinaryDataset::countMajorityLabel() {
	// initialize instance fields
	this->posOneCount = 0;
	this->negOneCount = 0;

	// count the number of positive and negative labels
	for (unsigned int i = 0; i < this->numObservations; i++) {

		// update fields fields with count
		if (this->dataset[i][this->numFeatures] == 1) {
			this->posOneCount++;
		} else {
			this->negOneCount++;
		}
	}
}

int BinaryDataset::getMajorityLabel() { 
	// get number of positive and negative labels
	this->countMajorityLabel();

	// return the label with the highest count
	if (this->posOneCount > this->negOneCount) {
		return 1;

	} else if (this->negOneCount > this->posOneCount){
		return -1;

		// return 1 if both labels have an equal count
	} else {
		return 1;
	}
}

double BinaryDataset::calcImpurityEntropy() {
	// initializing calculation variables and count label numbers
	this->countMajorityLabel();
	double n = posOneCount + negOneCount;
	double n1 = posOneCount;
	double n2 = negOneCount;

	// if one of the labels counts are 0 or the dataset is empty, impurity entropy is pure
	if ((n1 == 0 || n2 == 0) ||
			(this->isEmpty())) {
		return 0.0;
	}

	// calculating impurity entropy of dataset
	return -n1/n * log2(n1/n) - n2/n * log2(n2/n);;
}

void BinaryDataset::print(bool printAll) {
	// print 500x11 2d array of observations
	if (printAll) {
		for (unsigned int i = 0; i < MAX_OBSERVATIONS; i++) {
			for (unsigned int j = 0; j <= MAX_NUM_FEATURES; j++) {
				std::cout << this->dataset[i][j] << ";   ";
			}
			std::cout << std::endl;
		}
		// print just the 2d array of observations
	} else {
		for (unsigned int i = 0; i < this->numObservations; i++) {
			for (unsigned int j = 0; j <= this->numFeatures; j++) {
				std::cout << this->dataset[i][j] << ";   ";
			}
			std::cout << std::endl;
		}
	}
}

void BinaryDataset::zero() {
	// set every single observation in 2d array to 0 and reset total number of observations
	for (unsigned int i = 0; i < this->numObservations; i++) {
		for (unsigned int j = 0; j <= this->numFeatures; j++) {
			this->dataset[i][j] = 0.0;
		}
	}
	// reset total number of observations
	this->numObservations = 0;
}

void BinaryDataset::split(unsigned int iidim, unsigned int iiobs, BinaryDataset *subset1, BinaryDataset *subset2) {
	// initialize observation with feature number of dataset
	double observation[this->numFeatures];

	// get each observation in the dataset
	for (unsigned int i = 0; i < this->numObservations; i++) {
		this->getObservation(i, observation);

		// compare observation with observation at inputted observation and dimension indexes
		// if it is smaller
		if (this->dataset[i][iidim] < this->dataset[iiobs][iidim]) {
			// set feature number of first subset and append the observation
			subset1->setNumFeatures(this->numFeatures);
			subset1->appendObservation(observation, this->getLabel(i));

			// if it is larger
		} else {
			// set feature number of second subset and append the observation
			subset2->setNumFeatures(this->numFeatures);
			subset2->appendObservation(observation, this->getLabel(i));
		}
	}
}

bool BinaryDataset::isObservationEmpty(unsigned int ix) {
	// if the observation has no label at the index, return true as it's empty, else false
	if (dataset[ix][this->numFeatures] == 0.0) {
		return true;
	}
	return false;
}

void BinaryDataset::appendObservation(double *ft_in, int label_in) {
	// if the next observation is empty
	if (isObservationEmpty(this->numObservations)) {

		// set the observation with features and label
		this->setObservation(this->numObservations, ft_in);
		this->setLabel(this->numObservations, label_in);

		// increment total observation number
		this->numObservations++;
	}
}

void BinaryDataset::splitLOO(unsigned int ii, BinaryDataset *dataset1, BinaryDataset *dataset2) {
	// initialize observation with feature number of dataset
	double observation[this->numFeatures];

	// get each observation in the dataset
	for (unsigned int i = 0; i < this->numObservations; i++) {
		this->getObservation(i, observation);

		// compare current observation index with inputted index
		// if it isn't the same
		if (i != ii) {
			// set feature number of first subset and append the observation
			dataset1->setNumFeatures(this->numFeatures);
			dataset1->appendObservation(observation, this->getLabel(i));

			// if it's the same
		} else {
			// set feature number of first subset and append the observation
			dataset2->setNumFeatures(this->numFeatures);
			dataset2->appendObservation(observation, this->getLabel(i));
		}
	}
}

double BinaryDataset::calcImpurityDrop(BinaryDataset *subset1, BinaryDataset *subset2) {
	// initializing calculation variables
	double n = this->getNumObservations();
	double n1 = subset1->getNumObservations();
	double ie = this->calcImpurityEntropy();
	double ie1 = subset1->calcImpurityEntropy();
	double ie2 = subset2->calcImpurityEntropy();

	// calculating impurity drop of dataset
	return ie - n1/n * ie1 - (1 - n1/n) * ie2;;
}

void BinaryDataset::findOptimalSplit(unsigned int *out_dim, unsigned int *out_ii) {
	// initialize variables
	double highestID = -1.0;
	unsigned int optimal_dim;
	unsigned int optimal_ixobs;

	// loop through the 2D array
	for (unsigned int i = 0; i < this->numFeatures; i++) {
		for (unsigned int j = 0; j < this->numObservations; j++) {
			// initialize empty datasets to calculate impurity drop
			BinaryDataset *dataset_holdin = new BinaryDataset();
			BinaryDataset *dataset_holdout = new BinaryDataset();

			// split the dataset into two subsets at current criterion
			this->split(i,j,dataset_holdin,dataset_holdout);

			// calculate the impurity drop of the two datasets
			double currID = this->calcImpurityDrop(dataset_holdin,dataset_holdout);

			// if the current impurity drop is higher than the highest impurity drop
			if (currID > highestID){
				// replace highest impurity drop with current
				highestID = currID;
				// update optimal split dimension and feature indexes
				optimal_dim = i;
				optimal_ixobs = j;
			}

			// delete heap variables
			delete dataset_holdin;
			delete dataset_holdout;
		}
	}

	// return optimal split dimension and feature indexes
	*out_dim = optimal_dim;
	*out_ii = optimal_ixobs;
}

void BinaryDataset::getObservation(unsigned int ix, double *features) {
	// if the index is valid
	if (ix < this->numObservations) {

		// get the observation features at the index into the double array
		for (unsigned int i = 0; i < this->numFeatures; i++) {
			features[i] = this->dataset[ix][i];
		}
	}
}

void BinaryDataset::setObservation(unsigned int ix, double *features) {
	// set the observation features at the index to the double array features
	for (unsigned int i = 0; i < this->numFeatures; i++) {
		this->dataset[ix][i] = features[i];
	}
}

void BinaryDataset::setLabel(unsigned int ix, int label_in) {
	// set decision label of this node for valid label
	if (label_in == 1 || label_in == -1) {
		this->dataset[ix][numFeatures] = label_in;

		// set decision label of -1 for label inputs lesser than valid
	} else if (label_in < 1) {
		this->dataset[ix][numFeatures] = -1;

		// set decision label of 1 for label inputs greater than valid
	} else if (label_in > 1) {
		this->dataset[ix][numFeatures] = 1;
	}
}

int BinaryDataset::getLabel(unsigned int ix) {
	// return label from last column in dataset at index
	return this->dataset[ix][numFeatures];
}

void BinaryDataset::setNumFeatures(unsigned int num_features_in) {
	this->numFeatures = num_features_in;
}

unsigned int BinaryDataset::getNumFeatures(){
	return this->numFeatures;
}

unsigned int BinaryDataset::getNumObservations(){
	return this->numObservations;
}

void BinaryDataset::setNumObservations(unsigned int num_observations_in) {
	this->numObservations = num_observations_in;
}

double BinaryDataset::getCriterion(unsigned int obs_ix, unsigned int dim_ix) {
	// public helper function to return dataset criterion at observation and dimension index
	return this->dataset[obs_ix][dim_ix];
}


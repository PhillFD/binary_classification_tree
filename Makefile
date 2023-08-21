CXX = g++
CXXFLAGS = -Wall -g

all: BinaryClassifier

BinaryClassifier: test.cpp Binary/*.cpp #Binary/*.hpp
	$(CXX) $(CXXFLAGS) -o BinaryClassifier $^

test: BinaryClassifier
	./BinaryClassifier

clean:
	rm -f BinaryClassifier
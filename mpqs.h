#ifndef MPQS_H_
#define MPQS_H_
#include <string>
#include <vector>
using namespace std;

template <class Comparable>
class mpqs {
public:
	mpqs():currentSize(0) {};//default constructor of the class
	mpqs(int fulls):currentSize(0) {//constructor of a class

		fullsize = fulls;
		for (int i = 1; i < fullsize; i++)
		{
			Comparable def;
			heap[i] = def;
		}
	};
	~mpqs() {//destructor of the class
		delete []heap;
		//delete []Locations;
	};
	bool isEmpty() {
		if (currentSize == 0)
			return true;
		else
			return false;
	};

	void insert(const Comparable& labobj, int& value)
	{
		// Note that instead of swapping we move the hole up
		int hole = ++currentSize;
		for (; hole > 1 && labobj > heap[hole / 2]; hole /= 2){
			heap[hole] = heap[hole / 2];
			//Locations[heap[hole].label] = hole/2;
		}
		heap[hole] = labobj;
		//if (labobj >> maxel)
		//		 maxel= heap[hole];
		//for (; hole > 1 && value > Locations[hole / 2]; hole /= 2)
		//	Locations[hole] = Locations[hole/2];
		//Locations[hole] = value;
		for (int i = 1; i < currentSize+1; i++)
		{
			int k=-1;
			k= heap[i].label ;
			if(k!=-1)
				Locations[k] = i;

		}
		//Locations[heap[hole].label] = hole;
	}
	Comparable getMax() {// obtain object that has maximum hight 
		Comparable max;
		for (int k = 1; k <= currentSize; k++)
		{
			if (!(max >> heap[k]))
				max = heap[k];
		}
		return max;
	}

	Comparable remove(int label) { //remove and precolate down the both array
		if (currentSize==0) {
			Comparable firstcord;
			return firstcord;
		}
		else {
			Comparable empty;
			Comparable remitem = heap[label];
			heap[label] = heap[currentSize--];
			Locations[heap[label].label] = label;
			heap[currentSize + 1] = empty;//check later
			percolateDown(label);
			return remitem;
		}
	}
	Comparable* heap = new Comparable[100]; //in the homework its said that we should use array
	int* Locations = new int[100]; //in the homework its said that we should use array
	//vector<int> Locations 
	//vector<int > Locations 
private:
	int  currentSize; // Number of elements in heap
	int fullsize;
	Comparable maxel;// object that has the maximum hight
	//vector <Comparable> heap;

	//int label;
	//Comparable value;

	void percolateDown(int hole)
	{
		int child;
		Comparable tmp = heap[hole]; // tmp is the item that will// be percolated down


		for (; hole * 2 <= currentSize; hole = child)
		{
			child = hole * 2;
			if (child != currentSize && heap[child + 1] < heap[child])
				child++;  // child is the minimum of the children
			if (heap[child] < tmp) {
				heap[hole] = heap[child]; // swap hole and min child
				Locations[heap[hole].label] = hole;
			}
			else
				break;
		}
		heap[hole] = tmp;  // place tmp in its final position
		Locations[heap[hole].label] = hole;
	}
};

#endif // !MPQS_H_

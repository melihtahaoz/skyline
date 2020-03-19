#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "mpqs.h"

using namespace std;

struct recstructures //keeps all buldings as an rectangle object
{
	recstructures(): hight(-1),xcor(-1),label(-1){};//default constructor
	recstructures (int x, int h,int lab):hight(h), xcor(x),label(lab){};//constructor
	int hight,xcor,label;
	bool operator<(const recstructures& rhs) const {return (*this).xcor < rhs.xcor;} //compare xcord of rectanlge objects
	bool operator>(const recstructures& rhs) const { return (*this).xcor > rhs.xcor; }//compare xcord of rectanlge objects
	bool operator >>(const recstructures& rhs) const { return (*this).hight > rhs.hight; }//compare hight of rectanlge objects
	bool operator==(const recstructures& rhs) const { return (*this).xcor == rhs.xcor; }//compare two rectangle to see
};

void shellsort(recstructures*& a, int sizeofarr)//shellsort from lecture slides. Modified for the purpose
{
	int j;
	// Loop over increments
	for (int gap = sizeofarr / 2; gap > 0; gap /= 2) {
		// Loop over elements
		for (int i = gap; i < sizeofarr; i++)
		{
			recstructures tmp= a[i];
			// Loop over elements that are gap apart
			for (j = i; j >= gap && tmp < a[j - gap]; j -= gap)
				a[j] = a[j - gap];
			a[j] = tmp;
		}
	}
}


int main()
{
	string filename = "input.txt";//reading the file
	ifstream inFile;
	inFile.open(filename.c_str());
	string line;
	int count = 0;
	
	if (inFile.is_open()) {
		int sizeofarr=0;
		if (getline(inFile,line))
		{
			istringstream ss(line);
			ss >> sizeofarr;
			count++;
		}
		recstructures* arr = new recstructures[(2*sizeofarr+1)]; //array of sructs 
		int x_entry = 0, x_exit = 0, hight = 0;

		int labels_ofcomp = 1;//give label to all pairof xcordinate and hights
		while (getline(inFile,line))
		{
			istringstream ss(line);
			ss >> x_entry >> hight >> x_exit;
			recstructures ent1(x_entry,hight,labels_ofcomp);//put entry point into the arr
			arr[count] = ent1;
			count++;
			recstructures ent2(x_exit, hight,labels_ofcomp);//put exit point into the arr
			arr[count] = ent2;
			count++;
			labels_ofcomp++;
		}
		shellsort(arr, 2 * sizeofarr+1);//short the array
		for (int i = 0; i < 2 * sizeofarr + 1; i++) {
			for (int k = 0; k < 2 * sizeofarr + 1; k++) {
				if (arr[i].xcor == arr[k].xcor && arr[i].hight < arr[k].hight) {
					swap(arr[i], arr[k]);
				}
			}
		}



		mpqs<recstructures> heapobj(2 * sizeofarr + 1);
		for (int i = 1; i < 2 * sizeofarr + 1; i++)
			heapobj.Locations[i] = -1;
		if (arr[1].xcor>0)//if there is no xcor=0 value in the array print 0, 0
		cout<< 0<< " " << 0 << endl;
		recstructures prevprinted;
		int prevprint_hight=-1;
		for (int k = 1; k < (2 * sizeofarr) + 1; k++)
		{
			int  index1 = heapobj.Locations[arr[k].label];
			if (heapobj.heap[index1].label != arr[k].label) {//if the new building of the object is entry point

				recstructures prevmax = heapobj.getMax();
				heapobj.insert(arr[k], arr[k].label);
				int newmax = heapobj.getMax().hight;
				if (arr[k].xcor == arr[k + 1].xcor && arr[k].hight < arr[k + 1].hight) {
					index1 = heapobj.Locations[arr[k + 1].label];
					continue;
					k++;
				}
				if (!(newmax == prevmax.hight)) {
					//if (k <= 2 * sizeofarr && arr[k].xcor != arr[k + 1].xcor&& arr[k].xcor != arr[k - 1].xcor && arr[k].hight != arr[k - 1].hight&& arr[k].hight != arr[k + 1].hight) {
						if (prevprint_hight != arr[k].hight) {
							cout << arr[k].xcor << " " << arr[k].hight << endl;
							//prevprinted = arr[k];
							prevprint_hight = arr[k].hight;
						}
					//}
					//else if (arr[k].hight != arr[k - 1].hight|| arr[k].hight != arr[k + 1].hight)	{
						if (prevprint_hight != arr[k].hight) {
							cout << arr[k].xcor << " " << arr[k].hight << endl;
							prevprint_hight = arr[k].hight;
						}
					//}
				}

			}
			else {//if the new building of the object is exit point
				recstructures prevmax = heapobj.getMax();
				int idx = heapobj.Locations[arr[k].label]; 
				recstructures removedel = heapobj.remove(idx);
				int curr_hight = heapobj.getMax().hight;
				if (!(curr_hight == prevmax.hight)) {//if the hight did not change after the remove operation
					if (k  <= 2 * sizeofarr  && arr[k].xcor != arr[k + 1].xcor&& arr[k].xcor != arr[k - 1].xcor ) {
						if (heapobj.getMax().hight != -1 && prevprint_hight!= heapobj.getMax().hight) { //if there is an object in the in the heap, its x cordinate and hight will be print 
							cout << arr[k].xcor << " " << heapobj.getMax().hight << endl;
							prevprint_hight = heapobj.getMax().hight;
						}
						else {//if there is no object in the in the heap, x coordinate of lastly deleted element will be printed 
							cout << arr[k].xcor << " " << 0 << endl;
							prevprint_hight = 0;
						}
					}
					else if(k <= 2 * sizeofarr && (arr[k].hight != arr[k + 1].hight && arr[k].hight != arr[k - 1].hight))
					{
						if (heapobj.getMax().hight != -1) { //if there is an object in the in the heap, its x cordinate and hight will be print 
							cout << arr[k].xcor << " " << heapobj.getMax().hight << endl;
							prevprint_hight = heapobj.getMax().hight;
						}
						else {//if there is no object in the in the heap, x coordinate of lastly deleted element will be printed 
							cout << arr[k].xcor << " " << 0 << endl;
							prevprint_hight = 0;
						}
					}
				}
			}
		}
		//check the arr is sorted
		//for (int i = 1; i < (2 *sizeofarr )+1; i++)
		//{
		//	cout << arr[i].xcor << " " << arr[i].hight<<" "<<arr[i].label << endl;
		//}
	}

	return 0;
}

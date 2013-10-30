/*****************************************************************************************************************************
Author    :    Praveen Kumar Pendyala
Created    :    26th Oct.,2013
Project	:	VLSI CAD course project - Greedy Algorithm for Activity scheduling
Github	:	https://github.com/praveendath92/EE-677_project/

*****************************************************************************************************************************/

#include <iostream>
#include <cmath>
using namespace std;

//Add activities here
//You may try copying more inputs in the comment into the array
int startTime[]   = {0, 2, 4, 3};   // 10, 6, 5, 4, 6, 8, 9, 11, 10, 8, 1, 2, 3, 6, 8 -More inputs
int endTime[]     = {2, 3, 6, 5};   // 11, 7, 9, 7, 10, 10, 10, 13, 11, 13, 11, 6, 13, 14, 18 -More inputs

//Size of arrays used
#define size 5
int length = 0;//Length of time arrays
int fActsCount;

//Heap variables
int ptr = 1;
int sheap[size];	//Start times heap
int eheap[size];	//End times heap
//Start time heap is not actually a heap. It's just a mirror of end time heap's corresponding start times


/************ Other functions ****************/
void exchange(int i, int j){
	int etemp = eheap[i];
	eheap[i] = eheap[j];
	eheap[j] = etemp;

	int stemp = sheap[i];
	sheap[i] = sheap[j];
	sheap[j] = stemp;
}

void displayActivities(int s[], int e[], int len){
	for(int i=0; i<len; i++){
		cout<<"("<<s[i]<<","<<e[i]<<")"<<endl;
	}
}


/**************	Heap operations ******************/
void insertHeap(int start, int end){
	//Normal insertion at the end
	if(ptr != size){
		sheap[ptr] = start;
		eheap[ptr] = end;
		ptr++;
	}

	//Checking for the right position
	int chld = ptr-1;
	int prnt = chld/2;
	while(prnt != 0){
		if(eheap[chld] < eheap[prnt]){
			exchange(prnt, chld);
			chld = prnt;
			prnt = chld/2;
		}else{
			break;
		}
	}
}


void printHeap(){
	cout<<"Level order traversal of current heap is: "<<endl;

	int j = 1; //Line number
	for(int i=1; i<ptr; i++){
		//Print element
		cout<<"("<<sheap[i]<<","<<eheap[i]<<")";

		//For a line break
		int k = (int) pow(2.0,j);
		if((i+1)%k == 0){
			cout<<endl;
			j++;			
		}
	}
	cout<<endl<<endl;
}

void popHeap(){
	int prnt = 1;
	int lChild = prnt*2;
	int rChild = prnt*2+1;

	//Root will be deleted. So, place it in heap[0] for later use. heap[0] is unused for any operations.
	sheap[0] = sheap[1];
	eheap[0] = eheap[1];

	//Replace root with bottom most element
	sheap[1] = sheap[ptr-1];
	eheap[1] = eheap[ptr-1];
	ptr--;

	while(lChild < ptr){
		//Case 1: Right child exists
		if(rChild < ptr){
			//Case 1: lChild > rChild
			if(eheap[lChild] > eheap[rChild]){
				//Case 1: p > l > r 
				if(eheap[prnt] > eheap[lChild]){
					exchange(prnt, rChild);
					prnt = rChild;
					lChild = prnt*2;
					rChild = prnt*2 +1;
				} 
				//Case 2: l > p > r
				else if(eheap[prnt] > eheap[rChild]){
					exchange(prnt, rChild);
					prnt = rChild;
					lChild = prnt*2;
					rChild = prnt*2 +1;
				}
				//case 3: l > r > p
				else{
					//Get out of loop
					break;
				}
			}
			//Case 2: lChild < rChild
			else{
				//Case 1: p > r > l 
				if(eheap[prnt] > eheap[rChild]){
					exchange(prnt, lChild);
					prnt = lChild;
					lChild = prnt*2;
					rChild = prnt*2 +1;
				} 
				//Case 2: r > p > l
				else if(eheap[prnt] > eheap[lChild]){
					exchange(prnt, lChild);
					prnt = lChild;
					lChild = prnt*2;
					rChild = prnt*2 +1;
				}
				//case 3: r > l > p
				else{
					//Get out of loop
					break;
				}
			}

		}
		//rChild doesn't exit
		else{
			//lChild < prnt
			if(eheap[lChild] < eheap[prnt]){
				exchange(lChild, prnt);
			}
			//lChild < prnt
			else{
				//Get out of loop
				break;
			}
		}
	}
}

/***************************	Greedy scheduling functions		********************/
void sortByEndTime(){
	cout<<"Pushing values to heap"<<endl;
	for(int i=0; i<length; i++){
		insertHeap(startTime[i], endTime[i]);
	}
	printHeap();

	cout<<endl<<"Popping back values from heap. Values will be now returned in sorted fashion"<<endl;
	for(int i=0; i<length; i++){
		popHeap();	//Popped values will be in heap[0]
		startTime[i] = sheap[0];
		endTime[i] = eheap[0];
	}
}

void greedyActivitiesSelect(int sTimeF[], int eTimeF[]){
	//1st task in sorted list will be in final list
    sTimeF[fActsCount] = startTime[0];
    eTimeF[fActsCount] = endTime[0];
    fActsCount = 1;//Min. 1 activity

	for(int i=1; i<length; i++){
		if(endTime[i] <= startTime[i+1]){
            sTimeF[fActsCount] = startTime[i+1];
            eTimeF[fActsCount] = endTime[i+1];	
            fActsCount = fActsCount+1;		
		}
	}
}


/***************************	Main function	********************/
int main(){

	//Check if the sizes of startTime and endTime arrays match. Else stop here.
	if(sizeof(startTime) != sizeof(endTime))
		return 0;

	length = sizeof(startTime)/sizeof(*startTime);
		
	//Final list
	int sTimeF[length];
	int eTimeF[length];

	cout<<"Idea: "<<endl;
	cout<<"1. Sort activities according to their end time"<<endl;
	cout<<"2. Now compare endTime of ith activity with startTime of (i+1)th activity"<<endl;
	cout<<"3. Form a new array of non- overlapping tasks using above logic"<<endl<<endl;

	cout<<"Time complexity: "<<endl;
	cout<<"1. Using heap sort for sort - O(sort) = N*log(N)"<<endl;
	cout<<"2. startTime and endTime comparision for neighbours - O(comparision) = N"<<endl;
	cout<<"So, total Greedy alogrithm order is N*log(N)"<<endl<<endl;

	cout<<"Activity times (Before sorting)"<<endl;
	displayActivities(startTime,endTime,length);
	cout<<endl;

	cout<<"Sorting according to end time of the activities"<<endl;
	cout<<"using Heap sort for efficent sorting. O(sort) = N*log(N)"<<endl;
	sortByEndTime();

	cout<<endl;
	cout<<"Activity times (After sorting)"<<endl;
	displayActivities(startTime,endTime,length);

	cout<<endl;
	cout<<"Greedy activity selection by comparing startTime(i) and endTime(i-1)"<<endl;
	cout<<"Activity i passes the test if startTime(i) > endTime(i-1)"<<endl;
	greedyActivitiesSelect(sTimeF, eTimeF);

	cout<<""<<endl;
	cout<<"The optimum list of activities after greedy selection are"<<endl;
	displayActivities(sTimeF, eTimeF, fActsCount);


	cout<<"In this case Greedy alogrithm actually works"<<endl;
	cout<<"So, this is the best solution to the problem";

	return 0;
}

//
//  main.cpp
//  210-5.5
//
//  Created by Christopher Lucas on 3/20/15.
//  Copyright (c) 2015 CWL. All rights reserved.
//

#include <iostream>
#include "PriorityQueue.cpp"
#include "Comparator.cpp"
#include "Object.cpp"
using namespace std;

int main(int argc, const char * argv[]) {
	
	typedef int objectIDType;
	typedef int priorityType;
	 
	typedef Object<objectIDType,priorityType> PairObject;
	typedef PriorityQueue<objectIDType, priorityType, ObjectMaxCompare<objectIDType, priorityType>> PairObjectPriorityQueue;
	
	PairObject* priorityQueueList = new PairObject[5];
	
	PairObjectPriorityQueue myPQ = PairObjectPriorityQueue(priorityQueueList,0,5);
	
	myPQ.enqueue(PairObject(0,-7));
	myPQ.enqueue(PairObject(6, 0));
	myPQ.enqueue(PairObject(4, 4));
	myPQ.enqueue(PairObject(3, 3));
	
	myPQ.changeWeight(1,999);
	
	int size = myPQ.size();
	for (int i = 0; i < size; i++) {
		cout << myPQ.dequeue() << endl;
	}
	
	delete [] priorityQueueList;
    return 0;
}

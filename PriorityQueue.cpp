//
//  PriorityQueue.cpp
//  210-5.5
//
//  Created by Christopher Lucas on 3/21/15.
//  Copyright (c) 2015 CWL. All rights reserved.
//

#include "PriorityQueue.h"
#include "Object.h"

template<typename idType, typename priorityType, typename Comp>
PriorityQueue<idType,priorityType,Comp>::PriorityQueue(Object<idType, priorityType>* h, int num, int max) : Heap(heap<Object<idType, priorityType>, Comp>(h, num, max)){}

template<typename idType, typename priorityType, typename Comp>
void PriorityQueue<idType,priorityType,Comp>::enqueue(Object<idType, priorityType> obj){
	Heap.insert(obj);
}

template<typename idType, typename priorityType, typename Comp>
Object<idType, priorityType> PriorityQueue<idType,priorityType,Comp>::dequeue() {
	return Heap.removefirst();
}

template<typename idType, typename priorityType, typename Comp>
void PriorityQueue<idType,priorityType,Comp>::changeWeight(idType ident, priorityType priority){
	
	Object<idType, priorityType>* listOfAllObjects = new Object<idType, priorityType>[Heap.size()];
	
	int size = Heap.size();
	bool changedAny = 0;
	for (int i = 0; i < size; i++) {
		Object<idType, priorityType> obj = Heap.removefirst();
		if (obj.getID()==ident) {
			obj = Object<idType, priorityType>(ident, priority);
			changedAny = 1;
		}
		listOfAllObjects[i] = obj;
	}
	
	if (!changedAny) {
		cout << "No objects matched the specified ID, continuing" <<  endl;
	}
	
	for (int i = 0; i < size; i++) {
		Heap.insert(listOfAllObjects[i]);
	}
	
	delete [] listOfAllObjects;
}

template<typename idType, typename priorityType, typename Comp>
int PriorityQueue<idType, priorityType, Comp>::size(){
	return Heap.size();
}
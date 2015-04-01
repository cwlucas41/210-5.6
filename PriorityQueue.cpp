//
//  PriorityQueue.cpp
//  210-5.5
//
//  Created by Christopher Lucas on 3/21/15.
//  Copyright (c) 2015 CWL. All rights reserved.
//

#ifndef __PriorityQueuecpp__
#define __PriorityQueuecpp__

#include "PriorityQueue.h"
#include "Object.h"

template<typename idType, typename priorityType, typename Comp, typename Object>
PriorityQueue<idType,priorityType,Comp,Object>::PriorityQueue(Object* h, int num, int max) : maxHeap(heap<Object, Comp>(h, num, max)){}

template<typename idType, typename priorityType, typename Comp, typename Object>
void PriorityQueue<idType,priorityType,Comp,Object>::enqueue(Object obj){
	maxHeap.insert(obj);
}

template<typename idType, typename priorityType, typename Comp, typename Object>
Object PriorityQueue<idType,priorityType,Comp,Object>::dequeue() {
	return maxHeap.removefirst();
}

template<typename idType, typename priorityType, typename Comp, typename Object>
void PriorityQueue<idType,priorityType,Comp,Object>::changeWeight(idType ident, priorityType priority){
	
	Object* listOfAllObjects = new Object[maxHeap.size()];
	
	int size = maxHeap.size();
	bool changedAny = 0;
	for (int i = 0; i < size; i++) {
		Object obj = maxHeap.removefirst();
		if (obj.getID()==ident) {
			obj = Object(ident, priority);
			changedAny = 1;
		}
		listOfAllObjects[i] = obj;
	}
	
	if (!changedAny) {
		cout << "No objects matched the specified ID, continuing" <<  endl;
	}
	
	for (int i = 0; i < size; i++) {
		maxHeap.insert(listOfAllObjects[i]);
	}
	
	delete [] listOfAllObjects;
}

template<typename idType, typename priorityType, typename Comp, typename Object>
int PriorityQueue<idType,priorityType,Comp,Object>::size() const{
	return maxHeap.size();
}

#endif
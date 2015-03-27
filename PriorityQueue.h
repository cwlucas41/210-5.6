//
//  PriorityQueue.h
//  210-5.5
//
//  Created by Christopher Lucas on 3/21/15.
//  Copyright (c) 2015 CWL. All rights reserved.
//

#ifndef ___10_5_5__PriorityQueue__
#define ___10_5_5__PriorityQueue__

#include <stdio.h>
#include "Comparator.h"
#include "Object.h"
#include "heap.h"

template<typename idType, typename priorityType, typename Comp>
class PriorityQueue {
private:
	heap<Object<idType,priorityType>, Comp> Heap;
	
public:
	PriorityQueue(Object<idType,priorityType>* h, int num, int max);
	
	//enqueues a new object
	void enqueue(Object<idType, priorityType>);
	
	//removes and returns the object with highest priority
	Object<idType, priorityType> dequeue();
	
	//parameter: instance of Object class
	//changes the weight of all Objects with the same ID as the paramater object to the weight of the paramater object
	void changeWeight(idType,priorityType);
	
	int size();
};


#endif /* defined(___10_5_5__PriorityQueue__) */

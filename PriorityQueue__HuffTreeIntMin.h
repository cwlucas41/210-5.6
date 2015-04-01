//
//  PriorityQueue__HuffTreeInt.h
//  210-5.6
//
//  Created by Christopher Lucas on 3/31/15.
//  Copyright (c) 2015 CWL. All rights reserved.
//

#ifndef ___10_5_6__PriorityQueue__HuffTreeInt__
#define ___10_5_6__PriorityQueue__HuffTreeInt__

#include <stdio.h>
#include "PriorityQueue.cpp"
#include "Object__HuffTreeInt.h"
#include "ObjectMinCompare.cpp"

template<typename T>
class PriorityQueue__HuffTreeIntMin {
private:
	
	PriorityQueue<HuffTree<T>*, int, ObjectMinCompare<Object__HuffTreeInt<T> >, Object__HuffTreeInt<T> > pq;
	
public:
	
	PriorityQueue__HuffTreeIntMin(Object__HuffTreeInt<T>* h, int num, int max);
	void enqueue(Object__HuffTreeInt<T>);
	Object__HuffTreeInt<T> dequeue();
	void changeWeight(Object__HuffTreeInt<T>,int);
	int size() const;
	
};

#endif /* defined(___10_5_6__PriorityQueue__HuffTreeInt__) */

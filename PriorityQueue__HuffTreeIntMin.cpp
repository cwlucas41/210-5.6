//
//  PriorityQueue__HuffTreeInt.cpp
//  210-5.6
//
//  Created by Christopher Lucas on 3/31/15.
//  Copyright (c) 2015 CWL. All rights reserved.
//

#include "PriorityQueue__HuffTreeIntMin.h"
#include "Object__HuffTreeInt.h"
#include "ObjectMinCompare.h"
#include "PriorityQueue.cpp"

template<typename T>
PriorityQueue__HuffTreeIntMin<T>::PriorityQueue__HuffTreeIntMin(Object__HuffTreeInt<T>* h, int num, int max) : pq(PriorityQueue<HuffTree<T>*, int, ObjectMinCompare<Object__HuffTreeInt<T>>, Object__HuffTreeInt<T>>(h, num, max)){}

template<typename T>
void PriorityQueue__HuffTreeIntMin<T>::enqueue(Object__HuffTreeInt<T> object){
	pq.enqueue(object);
}

template<typename T>
Object__HuffTreeInt<T> PriorityQueue__HuffTreeIntMin<T>::dequeue() {
	return pq.dequeue();
}

template<typename T>
void PriorityQueue__HuffTreeIntMin<T>::changeWeight(Object__HuffTreeInt<T> matchID, int newPriority){
	pq.changeWeight(matchID, newPriority);
}

template<typename T>
int PriorityQueue__HuffTreeIntMin<T>::size() const {
	return pq.size();
}
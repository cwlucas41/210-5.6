//
//  Object__HuffTree*Int.cpp
//  210-5.6
//
//  Created by Christopher Lucas on 3/31/15.
//  Copyright (c) 2015 CWL. All rights reserved.
//

#include "Object__HuffTreeInt.h"

template<typename T>
Object__HuffTreeInt<T>::Object__HuffTreeInt(){
	object = Object<HuffTree<T>*, int>();
}

template<typename T>
Object__HuffTreeInt<T>::Object__HuffTreeInt(HuffTree<T>* ID, int p){
	object = Object<HuffTree<T>*, int>(ID, p);
}

template<typename T>
HuffTree<T>* Object__HuffTreeInt<T>::getID() const{
	return object.getID();
}

template<typename T>
int Object__HuffTreeInt<T>::getPriority() const{
	return object.getPriority();
}

template<typename T>
bool Object__HuffTreeInt<T>::operator==(Object__HuffTreeInt other){
	return object.getID() == other.getID();
}

template<typename T>
std::ostream& operator<<(std::ostream& out, Object__HuffTreeInt<T> obj){
	out << "objectID is: " << obj.getID() << std::endl;
	return out;
}
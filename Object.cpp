//
//  object.cpp
//  project 5.5
//
//  Created by Christopher Lucas on 3/20/15.
//  Copyright (c) 2015 CWL. All rights reserved.
//
#ifndef __Object__
#define __Object__

#include "Object.h"

template<typename I, typename P>
Object<I,P>::Object(I Id, P p){
	objectID = Id;
	priority = p;
}

template<typename I, typename P>
Object<I,P>::Object() : objectID() , priority() {}

template<typename I, typename P>
I Object<I,P>::getID() const{
	return objectID;
}

template<typename I, typename P>
P Object<I,P>::getPriority() const{
	return priority;
}

template<typename I, typename P>
bool Object<I,P>::operator==(Object other){
	return getID()==other.getID();
}

template<typename I, typename P>
std::ostream& operator<<(std::ostream& out, Object<I, P> obj){
	out << "objectID is: " << obj.getID();
	return out;
}

#endif
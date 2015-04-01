//
//  Object__HuffTree*Int.h
//  210-5.6
//
//  Created by Christopher Lucas on 3/31/15.
//  Copyright (c) 2015 CWL. All rights reserved.
//

#ifndef ___10_5_6__Object__HuffTree_Int__
#define ___10_5_6__Object__HuffTree_Int__

#include <stdio.h>
#include "hufftree.h"
#include "Object.h"

template<typename T>
class Object__HuffTreeInt {
	
private:
	
	Object<HuffTree<T>*, int> object;
	
public:
	
	Object__HuffTreeInt();
	Object__HuffTreeInt( HuffTree<T>* ID, int p);
	HuffTree<T>* getID() const;
	int getPriority() const;
	
	bool operator==(Object__HuffTreeInt);
	
};

template<typename T>
std::ostream& operator<<(std::ostream&, Object__HuffTreeInt<T> obj);

#endif /* defined(___10_5_6__Object__HuffTree_Int__) */

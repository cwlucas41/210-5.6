//
//  Comparator.h
//  210-5.5
//
//  Created by Christopher Lucas on 3/20/15.
//  Copyright (c) 2015 CWL. All rights reserved.
//

#ifndef ___10_5_5__Comparator__
#define ___10_5_5__Comparator__

#include <stdio.h>
#include "Object.cpp"
using namespace std;

template<typename Object>
class ObjectMinCompare {
public:
	// templated argument is the objectID type, not
	static bool prior(Object a, Object b);
};
#endif /* defined(___10_5_5__Comparator__) */

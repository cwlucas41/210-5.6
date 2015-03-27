//
//  object.h
//  project 5.5
//
//  Created by Christopher Lucas on 3/20/15.
//  Copyright (c) 2015 CWL. All rights reserved.
//

#ifndef __project_5_5__Object__
#define __project_5_5__Object__

#include <iostream>

template<typename I, typename P>
class Object {
private:
	I objectID;
	P priority;
	
public:
	Object();
	Object(I ID, P priority);
	I getID() const;
	P getPriority() const;
	
	bool operator==(Object);
	
};

template<typename I, typename P>
std::ostream& operator<<(std::ostream&, Object<I, P>);

#endif /* defined(__project_5_5__object__) */

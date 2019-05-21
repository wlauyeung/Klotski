#include <iostream>
#include <string>
#include <vector>

#include "stack.h"

Stack::Stack() {

}

Stack::~Stack() {
	for (std::vector<Entity*> v : stackVector) {
		for (Entity* e : v) {
			delete e;
		}
	}
}

std::vector<std::vector<Entity*> >& Stack::getStack() {
	return stackVector;
}
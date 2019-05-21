#ifndef STACK_H
#define STACK_H

#include "src/entities/entity.h"

class Stack
{
public:
	Stack(void);
	~Stack(void);

	std::vector<std::vector<Entity*> >& getStack();

private:
	std::vector<std::vector<Entity*> > stackVector;
};

#endif

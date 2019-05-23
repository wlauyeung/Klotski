#ifndef STACK_H
#define STACK_H

#include "src/entities/entity.h"

template <typename T>
class Stack
{
public:
	Stack(void);
	~Stack(void);

	std::vector<T>* getStack();

private:
	std::vector<T> stack;
};

template<typename T>
Stack<T>::Stack() {

}

template<typename T>
Stack<T>::~Stack() {
	/*for (std::vector<Entity*> v : stackVector) {
		for (Entity* e : v) {
			delete e;
		}
	}*/
}

template<typename T>
std::vector<T>* Stack<T>::getStack() {
	return &stack;
}

#endif

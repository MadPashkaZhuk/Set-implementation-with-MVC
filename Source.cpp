#include <iostream>
#include "Set.h"

int main() {
	Set a(10);
	a.add(8);
	a.Print();
	a.add(8);
	a.Print();
	std::cout << a.cardinality();
}
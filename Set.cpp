#include <iostream>
#include "Set.h"

Set::Set() : m_size(1) {
	m_array = new ConcreteElement[m_size]{};
}

Set::Set(int queueSize) : m_size(queueSize) {
	m_array = new ConcreteElement[m_size]{};
}

Set::Set(const Set& model) {
	m_array = new ConcreteElement[model.m_size];
	m_size = model.m_size;
	auto iter = model.CreateIterator();
	for (iter->First(); !iter->isDone(); iter->Next()) {
		if (iter->CurrentElement() == 1)
			add(iter->getIndex());
		else
			m_array[iter->getIndex()] = 0;
	}
}

Set::Set(Set&& model) {
	m_array = model.m_array;
	m_amountOfElements = model.m_amountOfElements;
	m_size = model.m_size;
	model.m_array = nullptr;
	model.m_amountOfElements = 0;
}

Set::Set(const std::initializer_list<int> list) : Set(list.size()) {
	for (auto& element : list) {
		ConcreteElement current(element);
		add(current);
	}
}
Set::~Set() {
	delete[] m_array;
} 

void Set::add(ConcreteElement newElement) {
	int value = newElement.value;
	if (value >= m_size) {
		ConcreteElement* tempArray = new ConcreteElement[value + 1];
		for (int i = 0; i < m_size; i++) {
			tempArray[i] = m_array[i];
		}
		for (int i = m_size; i < value; i++) {
			tempArray[i] = 0;
		}
		m_size = value + 1;
		delete[] m_array;
		m_array = tempArray;
	}
	m_array[value] = { 1 };
}

void ConcreteVisitor::visit(ConcreteElement& elem) {
	if (elem.value == 1) {
		amount++;
	}
}

int Set::cardinality() {
	ConcreteVisitor a;
	auto it = CreateIterator();
	for (it->First(); !it->isDone(); it->Next()) {
		it->ConcreteElement().accept(a);
	}
	return a.getCardinality();
}

void Set::Print() {
	for (int i = 0; i < m_size; i++) {
		std::cout << m_array[i].value << ' ';
	}
	std::cout << std::endl;
	auto it = CreateIterator();
	for (it->First(); !it->isDone(); it->Next()) {
		if (it->CurrentElement() == 1) {
			std::cout << it->getIndex() << ' ';
		}
	}
	std::cout << std::endl;
}
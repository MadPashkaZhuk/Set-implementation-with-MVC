#ifndef CONTAINER_H
#define CONTAINER_H
#include <iostream>
class ConcreteElement;

class Visitor {
public:
	virtual void visit(ConcreteElement&) = 0;
};

class ConcreteVisitor : public Visitor {
public:
	void visit(ConcreteElement& elem) override;
	int getCardinality() {
		if (amount == 0) {
			throw "Set is empty!";
		}
		return amount;
	}
private:
	int amount = 0;
};

class Element {
	virtual void accept(Visitor&) = 0;
};

class ConcreteElement : public Element {
public:
	ConcreteElement() = default;
	ConcreteElement(int val) : value(val) {}
	void accept(Visitor& v) override {
		v.visit(*this);
	}
	int value;
};

class Set
{
public:
	class Iterator;
	Set();
	Set(int);
	Set(const Set&);
	Set(Set&&);
	Set(const std::initializer_list<int>);
	~Set();
	void add(ConcreteElement);
	int cardinality();
	void Print();
	Iterator* CreateIterator() const {
		return new Iterator(this);
	}
	class Iterator {
	private:
		const Set* iter;
		int index;
	public:
		Iterator(const Set* iter_example) {
			iter = iter_example;
		}
		~Iterator() {
			delete iter;
		}
		void Next() noexcept {
			index++;
		}
		void First() {
			index = 0;
		}
		int CurrentElement() noexcept {
			return iter->m_array[index].value;
		}
		ConcreteElement ConcreteElement() noexcept {
			return iter->m_array[index];
		}
		bool isDone() noexcept {
			return (index == iter->m_size);
		}
		int getIndex() {
			return index;
		}
	};
private:
	ConcreteElement* m_array;
	int m_size;
	int m_amountOfElements = 0;
};
#endif  // Container.h
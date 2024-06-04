#ifndef ADAPTER_H
#define ADAPTER_H
#include "linkedlist.h"

//the Expected interface for a Queue
class Queue{
public:
	Queue(){}
	virtual void enqueue(const int& o)=0;
	virtual void dequeue()=0;
	virtual int front() const =0;
	virtual bool isEmpty() const =0;
	virtual int numItems() const =0;
	virtual ~Queue(){}
};


//class below is not completed... you must structure this as a object adapter
//with appropriate requests and calls inheritance structure etc.
class ObjectAdapter : public Queue{
public:
	ObjectAdapter() : _dlist(new DList()){}
	virtual void enqueue(const int& o){
		_dlist->push_front(o);
	}
	virtual void dequeue(){
		_dlist->pop_back();
	}
	virtual int front() const {
		return _dlist->backData();
	}
	virtual bool isEmpty() const {
		return _dlist->empty();
	}
	virtual int numItems() const {
		return _dlist->size();
	}
	virtual ~ObjectAdapter(){} 
private:
	DList* _dlist;
};



//class below is not completed... you must structure this as a class adapter
//with appropriate requests and calls inheritance structure etc.
class ClassAdapter : public Queue, private DList{
public:
	ClassAdapter() : DList(){}
	virtual void enqueue(const int& o){
		DList::push_front(o);
	}
	virtual void dequeue(){
		DList::pop_back();
	}
	virtual int front() const {
		return DList::backData();
	}
	virtual bool isEmpty() const {
		return DList::empty();
	}
	virtual int numItems() const {
		return DList::size();
	}
	virtual ~ClassAdapter(){}

};
#endif
#pragma once
#ifndef _CIRCULAR_BUFFER_

#include <vector>
#include <stdio.h>

#define BUFFER_CAPACITY 5
typedef int MyType;

class CircularBuffer
{
private:
	MyType m_buffer[BUFFER_CAPACITY];
	int m_size;
	int m_head;
	int m_tail;
	bool full;
public:
	CircularBuffer();
	~CircularBuffer();
	void pushBack(MyType& value);
	void clear(void);
	bool empty() const;

	MyType& getAt(int index); //index relative from front, exp; front:index 0, no error checking, user has to make sure

	int getSize(void) const;
};

#endif
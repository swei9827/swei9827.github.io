#include "CircularBuffer.h"
#include "windows.h"
#include <iostream>

using namespace std;

CircularBuffer::CircularBuffer()
{
	full = 0;
	m_head = 0;
	m_tail = 0;
	cout << "construct" << endl;
}

CircularBuffer::~CircularBuffer()
{
	cout << "destruct" << endl;
}

void CircularBuffer::pushBack(MyType& value)
{
	m_buffer[m_head] = value;

	if (full)
	{
		m_tail = (m_tail + 1) % BUFFER_CAPACITY;
	}

	m_head = (m_head + 1) % BUFFER_CAPACITY;

	full = (m_head == m_tail);
}

void CircularBuffer::clear(void)
{
	m_head = m_tail;
	full = false;
}

bool CircularBuffer::empty() const
{
	return (!full && (m_head == m_tail));
}

MyType& CircularBuffer::getAt(int index)//index relative from front, exp; front:index 0, no error checking, user has to make sure
{
	int theValue = m_head - index;
	
	if (theValue < 0)
	{
		theValue += BUFFER_CAPACITY;
	}

	MyType value = m_buffer[theValue];

	return value;
}

int CircularBuffer::getSize(void) const
{
	int size = BUFFER_CAPACITY;

	if (!full)
	{
		if (m_head >= m_tail)
		{
			size = m_head - m_tail;
		}
		else
		{
			size = BUFFER_CAPACITY + m_head - m_tail;
		}
	}

	return size;
}
#ifndef STACK
#define STACK
#include <assert.h>

#define DYN_STACK_BLOCK_SIZE 16
//DINAMIC ARRAY
template<class ALUE>
class Stack
{
private:

	ALUE *			s_data;
	unsigned int	s_mem_capacity;
	unsigned int	s_num_elements;

public:

	// Constructors
	Stack() :s_mem_capacity(0), s_num_elements(0), s_data(NULL)
	{
		s_Alloc(DYN_ARRAY_BLOCK_SIZE);
	}

	Stack(unsigned int s_capacity) : s_mem_capacity(0), s_num_elements(0), s_data(NULL)
	{
		s_Alloc(s_capacity);
	}

	// Destructor
	~Stack()
	{
		delete[] s_data;
	}

	//Data Management
	void PushBack_stack(const ALUE& element)
	{
		if (s_num_elements >= s_mem_capacity)
		{
			s_Alloc(s_mem_capacity + DYN_STACK_BLOCK_SIZE);
		}

		s_data[s_num_elements++] = element;
	}

	bool Pop_stack(ALUE& result)
	{
		if (s_num_elements > 0)
		{
			result = s_data[--s_num_elements];
			return true;
		}
		return false;

	}

	const ALUE* At(unsigned int index) const
	{
		ALUE* result = NULL;

		if (index < s_num_elements)
			result = &s_data[index];

		return result;
	}

	ALUE* Top()
	{
		return s_data[s_num_elements - 1];
	}

	void Clear()
	{
		s_num_elements = 0;
	}


	unsigned int s_GetCapacity() const
	{
		return s_mem_capacity;
	}

	unsigned int s_Count() const
	{
		return s_num_elements;
	}


private:

	// Private Utils
	void s_Alloc(unsigned int mem)
	{
		ALUE* tmp = s_data;

		s_mem_capacity = mem;
		s_data = new ALUE[s_mem_capacity];

		if (s_num_elements > s_mem_capacity)
			s_num_elements = s_mem_capacity;

		if (tmp != NULL)
		{
			for (unsigned int i = 0; i < s_num_elements; ++i)
				s_data[i] = tmp[i];

			delete[] tmp;
		}
	}
}
#endif
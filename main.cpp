#include <iostream>
#include <stack>

using namespace std;

int main () {

	int NUM {5};

	int array[NUM] = {1,3,7,4,2};

	stack<int> index_st;
	// Array to hold indexes of the smallest bounds on the left for each index
	int l_small_bounds[NUM] {};
	// Array to hold indexes of the smallest bounds on the right for each index
	int r_small_bounds[NUM] {};

	for (int i {}; i < NUM; i++) {
		// while the index is not empty
		// AND the element at the index at the top of the stack is greater than the current element (not a smaller bound)
		while (!index_st.empty() && (array[index_st.top()] >= array[i]))
			// Remove from the stack
			index_st.pop();

		// The stack will now either have the next smallest element index on the left, or be empty

		//if it's empty
		if (index_st.empty())
			// the boundary will be at index 0
			l_small_bounds[i] = 0;
		else
		// Otherwise, the next smallest boundary on the left will be the index on the top of the stack
		//		(plus one to create a boundary, as the element at the top index
		//       is the smallest on the left: so the boundary would be right after that element)
			l_small_bounds[i] = index_st.top() + 1;

		// place the current index on the stack
		index_st.push(i);
	}

	//Clear the stack for the right bounds
	while(!index_st.empty())
		index_st.pop();

	// Now we do the same, but in reverse, for the smallest bounds indexes on the right side of each element
	for (int i {NUM-1}; i >= 0; i--) {
		// while the index is not empty
		// AND the element at the index at the top of the stack is greater than the current element (not a smaller bound)
		while (!index_st.empty() && (array[index_st.top()] >= array[i]))
			// Remove from the stack
			index_st.pop();

		// The stack will now either have the next smallest element index on the right, or be empty

		//if it's empty
		if (index_st.empty())
			// the boundary will be at the maximum index
			r_small_bounds[i] = NUM-1;
		else
		// Otherwise, the next smallest boundary on the right will be the index on the top of the stack
		//		(minus one to create a boundary, as the element at the top index
		//       is the smallest on the right: so the boundary would be right before that element)
			r_small_bounds[i] = index_st.top() - 1;

		// place the current index on the stack
		index_st.push(i);
	}

	int max_area {};

	for (int i {}; i < NUM; i++) {
		//                         	 height * width
		//                       height  * (right boundary * left boundary + 1)
		max_area = max(max_area, array[i]*(r_small_bounds[i] - l_small_bounds[i] + 1));
	}

	return 0;
}

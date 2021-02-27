#ifndef MINHEAP_H
#define MINHEAP_H

#include <vector>

using namespace std;

// A class for Min Heap 
class MinHeap
{
private:
	vector<pair<uint32_t, float>> harr; // pointer to array of elements in heap 
	uint64_t heap_size; // Current number of elements in min heap 
public:
	MinHeap(uint64_t);

	// Return harr
	vector<pair<uint32_t, float>> arr() { return harr; }

	// Return Size
	uint64_t sizeOf() { return heap_size; }

	// A recursive method to heapify a subtree with the root at given index 
	// This method assumes that the subtrees are already heapified 
	void MinHeapify(uint64_t);

	uint64_t parent(uint64_t i) { return (i - 1) / 2; }

	// to get index of left child of node at index i 
	uint64_t left(uint64_t i) { return (2 * i + 1); }

	// to get index of right child of node at index i 
	uint64_t right(uint64_t i) { return (2 * i + 2); }

	// Method to remove minimum element (or root) from min heap 
	pair<uint32_t, float> extractMin();

	// Returns the minimum key (key at root) from min heap 
	pair<uint32_t, float> getMin() { return harr.at(0); }

	// Inserts a new key 'k' 
	void insertKey(pair<uint32_t, float>);

	// iterate
	void iter();
};


// Constructor 
MinHeap::MinHeap(uint64_t init_size)
{
	heap_size = init_size;
}

// A recursive method to heapify a subtree with the root at given index 
// This method assumes that the subtrees are already heapified 
void MinHeap::MinHeapify(uint64_t i)
{
	uint64_t l = left(i);
	uint64_t r = right(i);
	uint64_t smallest = i;
	if (l < heap_size && harr.at(l).second < harr.at(i).second)
		smallest = l;
	if (r < heap_size && harr.at(r).second < harr.at(smallest).second)
		smallest = r;
	if (smallest != i)
	{
		harr.at(i).swap(harr.at(smallest));
		MinHeapify(smallest);
	}
}

// Method to remove minimum element (or root) from min heap 
pair<uint32_t, float> MinHeap::extractMin()
{
	if (heap_size <= 0)
		throw new runtime_error("Size is 0");

	if (heap_size == 1)
	{
		heap_size--;
		return harr.at(0);
	}

	// Store the minimum value, and remove it from heap 
	pair<uint32_t, float> root = harr.at(0);
	harr.at(0) = harr.at(heap_size - 1);
	harr.pop_back();
	heap_size--;
	MinHeapify(0);

	return root;
}

// Inserts a new key 'k' 
void MinHeap::insertKey(pair<uint32_t, float> k)
{
	// First insert the new key at the end 
	heap_size++;
	uint64_t i = heap_size - 1;
	harr.push_back(k);

	// Fix the min heap property if it is violated 
	while (i != 0 && harr.at(parent(i)).second > harr.at(i).second)
	{
		harr.at(i).swap(harr.at(parent(i)));
		i = parent(i);
	}
}

// iterate array
void MinHeap::iter() {
	for (auto a : harr) {
		cout << a.first << " " << a.second << endl;
	}
	cout << endl;
}
#endif
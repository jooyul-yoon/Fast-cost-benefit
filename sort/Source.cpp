#include <iostream>
#include <array>
#include <vector>
#include <utility> // std::pair
#include <cstdlib> // rand()
#include <chrono> // execution time measure
#include <assert.h> 
#include <iomanip>
#include "MinHeap.h"
#include "RBTree.h"

using namespace std;
using namespace std::chrono;


int main() {
	uint64_t request; 
	cout << "Total number of pages:\t"; cin >> request;
	uint64_t BlocksToReclaim; 
	cout << "Blocks to reclaim:\t"; cin >> BlocksToReclaim;

	MinHeap c1_heap(0);
	RBTree c1_rbtree;



	vector<pair<uint32_t, float>> input;

	vector<pair<uint32_t, float>> weight1;
	vector<pair<uint32_t, float>> weight2;
	vector<pair<uint32_t, float>> weight3;

	vector<uint32_t> list1;
	vector<uint32_t> list2;
	vector<uint32_t> list3;

	for (uint64_t i = 0; i < request; i++) {
		uint32_t fst = rand();
		float snd = ((float)rand() + 1) / (float)RAND_MAX;
		input.push_back({ fst, snd });
	}


	/***  TEST1 - STANDARD  ***/
	auto start = high_resolution_clock::now();

	for (uint64_t i = 0; i < request; i++) {
		uint32_t fst = rand();
		float snd = ((float)rand() + 1) / (float)RAND_MAX;
		weight1.push_back({ fst,snd });
		// weight1.push_back(input.at(i));
	}


	sort(
		weight1.begin(), weight1.end(),
		[](pair<uint32_t, float> a, pair<uint32_t, float> b) -> bool {
		return a.second < b.second;
	});

	for (uint64_t i = 0; i < BlocksToReclaim; i++) {
		list1.push_back(weight1.at(i).first);
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	

	/***  TEST HEAP  ***/
	auto start2 = high_resolution_clock::now();

	float threshold_heap;
	uint64_t MAX_HEAP_SIZE = 0;

	for (uint64_t i = 0; i < request; i++) {	
		uint32_t fst = rand();
		float snd = ((float)rand() + 1) / (float)RAND_MAX;
		c1_heap.insertKey({ fst,snd });
		// input stored into c1
		// c1_heap.insertKey(input.at(i));

		// initialize threshold
		if (weight2.size() == 0) {
			weight2.push_back(c1_heap.extractMin());
			threshold_heap = weight2.at(0).second;
			MAX_HEAP_SIZE += BlocksToReclaim;
			continue;
		}


		// if (current c0 size <= c0 max size)
		if (weight2.size() <= MAX_HEAP_SIZE) {

			// if (current c0 size = c0 max size)
			if (weight2.size() == MAX_HEAP_SIZE) {

				// reset threshold
				threshold_heap = weight2.at(MAX_HEAP_SIZE - 1).second;
				// cout << threshold_heap << endl; check threshold

				// resize c0 max size
				MAX_HEAP_SIZE += BlocksToReclaim;
			}

			// if (CB < threshold)
			if (c1_heap.getMin().second < threshold_heap) {

				// push Minimum from C1 to C0
				weight2.push_back(c1_heap.extractMin());
			}
		}
	}

	auto stop2 = high_resolution_clock::now();
	auto duration2 = duration_cast<microseconds>(stop2 - start2);

	sort(
		weight2.begin(), weight2.end(),
		[](pair<uint32_t, float> a, pair<uint32_t, float> b) -> bool {
		return a.second < b.second;
	});

	for (uint64_t i = 0; i < BlocksToReclaim; i++) {
		list2.push_back(weight2.at(i).first);
	}

	



	/***  TEST RBTree  ***/
	auto start3 = high_resolution_clock::now();

	float threshold_Tree;
	uint64_t MAX_TREE_SIZE = 0;

	for (uint64_t i = 0; i < request; i++) {
		uint32_t fst = rand();
		float snd = ((float)rand() + 1) / (float)RAND_MAX;
		c1_rbtree.insert({ fst,snd });
		// input stored into c1
		// c1_rbtree.insert(input.at(i));

		// initialize threshold
		if (weight3.size() == 0) {
			weight3.push_back(c1_rbtree.extractMin());
			threshold_Tree = weight3.at(0).second;
			MAX_TREE_SIZE += BlocksToReclaim;
			continue;
		}

		// if (current c0 size <= c0 max size)
		if (weight3.size() <= MAX_TREE_SIZE) {

			// if (current c0 size = c0 max size)
			if (weight3.size() == MAX_TREE_SIZE) {

				// reset threshold
				threshold_Tree = weight3.at(MAX_TREE_SIZE - 1).second;
				// cout << threshold_Tree << endl; // check threshold

				// resize c0 max size
				MAX_TREE_SIZE += BlocksToReclaim;
			}

			// if (CB < threshold)
			if (c1_rbtree.getMin().second < threshold_Tree) {
				// push Minimum from C1 to C0
				weight3.push_back(c1_rbtree.extractMin());
			}
		}
	 }


	sort(
		weight3.begin(), weight3.end(),
		[](pair<uint32_t, float> a, pair<uint32_t, float> b) -> bool {
		return a.second < b.second;
	});

	for (uint64_t i = 0; i < BlocksToReclaim; i++) {
		list3.push_back(weight3.at(i).first);
	}

	auto stop3 = high_resolution_clock::now();
	auto duration3 = duration_cast<microseconds>(stop3 - start3);




	// Display Result
	cout << "\n\tstandard\tCost-Benefit\tFast Cost-Benefit\n";
	cout << "-------------------------------------------------------------\n";

	// second value in weight
	for (uint64_t i = 1; i <= BlocksToReclaim; i++) {
		cout << std::setprecision(5) << i << "\t" << weight1.at(i).second
				  << "\t" << weight2.at(i).second
				  << "\t" << weight3.at(i).second << endl;
	}

	// List Size
	cout << "\nSize\t";
	cout << weight1.size() << "\t\t";
	cout << weight2.size() << "\t\t";
	cout << weight3.size() << endl;

	// Time Taken
	cout << "time\t"
		<< duration.count();
	cout << "\t\t"
		<< duration2.count();
	cout << "\t\t"
		<< duration3.count() << endl << endl;

	std::system("pause");
	return 0;
}
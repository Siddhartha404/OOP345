//Name: Siddhartha Thapa Chhetri
//Email: sthapa-chhetri2@myseneca.ca
//ID: 147913222
//Date:2024/07/28
//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments.This submitted piece of work has not been shared with any other student or 3rd party content provider.
// Workshop 9 - Multi-Threading, Thread Class

#include <iostream>
#include <fstream>
#include <functional>
#include <thread>
#include <vector>
#include <numeric>
#include <stdexcept>
#include "ProcessData.h"

namespace seneca
{
	// The following function receives array (pointer) as the first argument, number of array 
	//   elements (size) as second argument, divisor as the third argument, and avg as fourth argument. 
	//   size and divisor are not necessarily same. When size and divisor hold same value, avg will 
	//   hold average of the array elements. When they are different, avg will hold a value called 
	// 	 as average-factor. For part 1, you will be using same value for size and double. Use of 
	//   different values for size and divisor will be useful for multi-threaded implementation in part-2.
	void computeAvgFactor(const int* arr, int size, int divisor, double& avg) {
		avg = 0;
		for (int i = 0; i < size; i++)
		{
			avg += arr[i];
		}
		avg /= divisor;
	}
	// The following function receives array (pointer) as the first argument, number of array elements  
	//   (size) as second argument, divisor as the third argument, computed average value of the data items
	//   as fourth argument, and var as fifth argument. Size and divisor are not necessarily same as in the 
	//   case of computeAvgFactor. When size and divisor hold same value, var will get total variance of 
	//   the array elements. When they are different, var will hold a value called as variance factor. 
	//   For part 1, you will be using same value for size and double. Use of different values for size 
	//   and divisor will be useful for multi-threaded implementation in part-2.
	void computeVarFactor(const int* arr, int size, int divisor, double avg, double& var) {
		var = 0;
		for (int i = 0; i < size; i++)
		{
			var += (arr[i] - avg) * (arr[i] - avg);
		}
		var /= divisor;
	}

	ProcessData::operator bool() const {
		return total_items > 0 && data != nullptr;
	}

	// The following constructor of the functor receives name of the data file, opens it in
	//   binary mode for reading, reads first int data as total_items, allocate memory space
	//   to hold the data items, and reads the data items into the allocated memory space.
	//   It prints first five data items and the last three data items as data samples.
	ProcessData::ProcessData(const std::string& filename) {
		// TODO: Open the file whose name was received as parameter and read the content
		//         into variables "total_items" and "data". Don't forget to allocate
		//         memory for "data".
		//       The file is binary and has the format described in the specs.

		 // Open the file in binary mode
		// Open the file in binary mode
		std::ifstream file(filename, std::ios::binary);
		if (!file) {
			throw std::runtime_error("Failed to open file");
		}

		// Read total_items from the file
		file.read(reinterpret_cast<char*>(&total_items), sizeof(total_items));
		if (file.gcount() != sizeof(total_items)) {
			throw std::runtime_error("Failed to read total_items");
		}

		// Allocate memory for data array
		data = new int[total_items];

		// Read the data items from the file
		file.read(reinterpret_cast<char*>(data), total_items * sizeof(int));
		if (file.gcount() != static_cast<std::streamsize>(total_items * sizeof(int))) {
			delete[] data;
			throw std::runtime_error("Failed to read data items");
		}

		std::cout << "Item's count in file '" << filename << "': " << total_items << std::endl;
		std::cout << "  [" << data[0] << ", " << data[1] << ", " << data[2] << ", ... , "
			<< data[total_items - 3] << ", " << data[total_items - 2] << ", "
			<< data[total_items - 1] << "]\n";
	}

	ProcessData::ProcessData(const std::string& filename, int num_threads)
		: total_items(0), data(nullptr), num_threads(num_threads) // Initialize in the order of declaration
	{
		std::ifstream file(filename, std::ios::binary);
		if (!file) {
			throw std::runtime_error("Failed to open file");
		}

		file.read(reinterpret_cast<char*>(&total_items), sizeof(total_items));
		data = new int[total_items];
		file.read(reinterpret_cast<char*>(data), total_items * sizeof(int));

		if (static_cast<std::streamsize>(file.gcount()) != static_cast<std::streamsize>(total_items * sizeof(int))) {
			delete[] data;
			throw std::runtime_error("File read error");
		}

		std::cout << "Item's count in file '" << filename << "': " << total_items << std::endl;
		std::cout << "  [" << data[0] << ", " << data[1] << ", " << data[2] << ", ... , "
			<< data[total_items - 3] << ", " << data[total_items - 2] << ", "
			<< data[total_items - 1] << "]\n";
	}

	ProcessData::~ProcessData()
	{
		delete[] data;
	}


	// TODO Implement operator(). See workshop instructions for details.

	// Multi-threaded operator() implementation
	int ProcessData::operator()(const std::string& target_filename, double& avg, double& var) {
		const int partition_size = total_items / num_threads;
		std::vector<std::thread> threads;
		std::vector<double> avg_factors(num_threads, 0.0);
		std::vector<double> var_factors(num_threads, 0.0);

		// Compute average factors
		auto computeAvg = std::bind(computeAvgFactor, std::placeholders::_1, std::placeholders::_2, total_items, std::placeholders::_3);
		for (int i = 0; i < num_threads; ++i) {
			int start_index = i * partition_size;
			int end_index = (i == num_threads - 1) ? total_items : start_index + partition_size;
			threads.push_back(std::thread([=, &avg_factors]() {
				computeAvg(data + start_index, end_index - start_index, avg_factors[i]);
				}));
		}
		for (auto& t : threads) {
			t.join();
		}
		avg = std::accumulate(avg_factors.begin(), avg_factors.end(), 0.0);

		// Compute variance factors
		threads.clear();
		auto computeVar = std::bind(computeVarFactor, std::placeholders::_1, std::placeholders::_2, total_items, avg, std::placeholders::_3);
		for (int i = 0; i < num_threads; ++i) {
			int start_index = i * partition_size;
			int end_index = (i == num_threads - 1) ? total_items : start_index + partition_size;
			threads.push_back(std::thread([=, &var_factors]() {
				computeVar(data + start_index, end_index - start_index, var_factors[i]);
				}));
		}
		for (auto& t : threads) {
			t.join();
		}
		var = std::accumulate(var_factors.begin(), var_factors.end(), 0.0);

		// Write data to target file
		std::ofstream outfile(target_filename, std::ios::binary);
		if (!outfile) {
			throw std::runtime_error("Failed to open target file");
		}
		outfile.write(reinterpret_cast<char*>(&total_items), sizeof(total_items));
		outfile.write(reinterpret_cast<char*>(data), total_items * sizeof(int));

		return 0;
	}



}
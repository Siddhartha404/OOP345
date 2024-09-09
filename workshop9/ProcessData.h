//Name: Siddhartha Thapa Chhetri
//Email: sthapa-chhetri2@myseneca.ca
//ID: 147913222
//Date:2024/07/28
//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments.This submitted piece of work has not been shared with any other student or 3rd party content provider.
// Workshop 9 - Multi-Threading, Thread Class

#ifndef SENECA_PROCESSDATA_H
#define SENECA_PROCESSDATA_H

#include <string>

namespace seneca
{
	void computeAvgFactor(const int*, int, int, double&);
	void computeVarFactor(const int*, int, int, double, double&);

	class ProcessData
	{
		int total_items{};
		int* data{};
		int num_threads{ 1 };
	public:
		ProcessData(const std::string&);
		ProcessData(const std::string& filename, int num_threads=-1);
		ProcessData(const ProcessData&) = delete;
		ProcessData& operator=(const ProcessData&) = delete;
		~ProcessData();
		operator bool() const;
		int operator()(const std::string&, double&, double&);
	};
}

#endif
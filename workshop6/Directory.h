//Name: Siddhartha Thapa Chhetri
//Email: sthapa-chhetri2@myseneca.ca
//ID: 147913222
//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments.This submitted piece of work has not been shared with any other student or 3rd party content provider.#ifndef SENECA_DIRECTORY_H
#ifndef SENECA_DIRECTORY_H
#define SENECA_DIRECTORY_H
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include "Resource.h"

namespace seneca
{
	class Directory : public Resource
	{
		std::vector<Resource*> m_contents;

	public:
		Directory(std::string dir);
		void update_parent_path(const std::string&);
		NodeType type() const;
		std::string path() const;
		std::string name() const;
		int count() const;
		size_t size() const;
		Directory& operator+=(Resource*);
		Resource* find(const std::string& name, const std::vector<OpFlags>& flags = {});
		void remove(const std::string&, const std::vector<OpFlags>& flags = {});
		void display(std::ostream& os, const std::vector<FormatFlags>& formatFlags = {}) const;
		~Directory();
		Directory(Directory&) = delete;
		Directory& operator=(Directory&) = delete;
		Directory(Directory&&) noexcept = delete;
		Directory& operator=(Directory&&) noexcept = delete;
	};
}

#endif // !SENECA_DIRECTORY_H

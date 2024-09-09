//Name: Siddhartha Thapa Chhetri
//Email: sthapa-chhetri2@myseneca.ca
//ID: 147913222
//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments.This submitted piece of work has not been shared with any other student or 3rd party content provider.
#include <iomanip>
#include "Directory.h"

namespace seneca
{
	//
	Directory::Directory(std::string dir)
	{
		m_name = dir;
	}

	//
	void Directory::update_parent_path(const std::string& path)
	{
		// Set the parent path for this directory
		m_parent_path = path;

		// Update the absolute path for each resource in this directory
		for (auto* resource : m_contents)
		{
			std::string new_path = m_parent_path + m_name;
			resource->update_parent_path(new_path);
		}
	}

	//
	NodeType Directory::type() const
	{
		return NodeType::DIR;
	}

	//
	std::string Directory::path() const
	{
		return m_parent_path + m_name;
	}

	//
	std::string Directory::name() const
	{
		return m_name;
	}

	//
	int Directory::count() const
	{
		return m_contents.size();
	}

	//
	size_t Directory::size() const
	{
		size_t total_size{ 0u };
		for (const auto* resource : m_contents)
		{
			total_size += resource->size();
		}
		return total_size;
	}

	//
	Directory& Directory::operator+=(Resource* res)
	{
		//
		for (const auto* Resource : m_contents)
		{
			if (Resource->name() == res->name())
			{
				throw std::runtime_error("Resource with the same name already exists.");
			}
		}

		//
		res->update_parent_path(m_parent_path + m_name);
		m_contents.push_back(res);

		return *this;
	}

	//
	Resource* Directory::find(const std::string& name, const std::vector<OpFlags>& flags)
	{
		// Check if RECURSIVE flag is set
		bool recursive = false;
		for (const auto& flag : flags)
		{
			if (flag == OpFlags::RECURSIVE)
			{
				recursive = true;
				break;
			}
		}

		// Search for the resource by name
		for (auto* resource : m_contents)
		{
			if (resource->name() == name)
			{
				return resource;
			}

			// If resource is a directory and recursive flag is set, recursively search within it
			if (recursive && resource->type() == NodeType::DIR)
			{
				auto* dir_resource = dynamic_cast<Directory*>(resource);
				if (dir_resource)
				{
					auto* found_resource = dir_resource->find(name, flags);
					if (found_resource)
					{
						return found_resource;
					}
				}
			}
		}

		// If not found, return nullptr
		return nullptr;
	}

	//
	void Directory::remove(const std::string& name, const std::vector<OpFlags>& flags)
	{
		Resource* to_remove = nullptr;

		for (auto* resource : m_contents)
		{
			if (resource->name() == name)
			{
				to_remove = resource;
				break;
			}
		}

		if (!to_remove)
		{
			throw std::invalid_argument(name + " does not exist in " + m_name);
		}

		if (to_remove->type() == NodeType::DIR)
		{
			bool recursive = false;
			for (const auto& flag : flags)
			{
				if (flag == OpFlags::RECURSIVE)
				{
					recursive = true;
					break;
				}
			}

			if (!recursive)
			{
				throw std::invalid_argument(name + " is a directory. Pass the RECURSIVE flag to delete directories.");
			}
		}

		auto it = std::find(m_contents.begin(), m_contents.end(), to_remove);
		m_contents.erase(it);
		delete to_remove;
	}

	void Directory::display(std::ostream& os, const std::vector<FormatFlags>& formatFlags) const
	{
		size_t total_size = size();
		os << "Total size: " << total_size << " bytes" << std::endl;
		for (const auto* resource : m_contents)
		{
			if (resource->type() == NodeType::DIR)
			{
				os << "D | ";
			}
			else
			{
				os << "F | ";
			}
			os << std::left << std::setw(15) << resource->name() << " |";

			// Check if LONG flag is set
			if (std::find(formatFlags.begin(), formatFlags.end(), FormatFlags::LONG) != formatFlags.end())
			{
				if (resource->type() == NodeType::DIR)
				{
					os << std::right << std::setw(2) << " " << dynamic_cast<const Directory*>(resource)->count() << " | ";
				}
				else
				{
					os << "    | ";
				}
				os << std::right << std::setw(4) << resource->size() << " bytes | ";
			}

			os << std::endl; // Move to the next line
		}
	}

	Directory::~Directory()
	{
		for (auto* resource : m_contents)
		{
			delete resource; // Delete each resource
		}
		m_contents.clear();
	}
}
//Name: Siddhartha Thapa Chhetri
//Email: sthapa-chhetri2@myseneca.ca
//ID: 147913222
//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments.This submitted piece of work has not been shared with any other student or 3rd party content provider.
#include "File.h"

namespace seneca
{
	File::File(std::string name, std::string cont)
	{
		m_name = name;
		m_contents = cont;
	}
	void File::update_parent_path(const std::string& path)
	{
		m_parent_path = path;
	}
	NodeType File::type() const
	{
		return NodeType::FILE;
	}
	std::string File::path() const
	{
		return m_parent_path + m_name;
	}
	std::string File::name() const
	{
		return m_name;
	}
	int File::count() const
	{
		return -1;
	}
	size_t File::size() const
	{
		return m_contents.size();
	}
}
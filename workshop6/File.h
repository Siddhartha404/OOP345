#ifndef SENECA_FILE_H
#define SENECA_FILE_H

#include "Resource.h"

namespace seneca
{
	class File : public Resource
	{
		std::string m_contents;

	public:
		File(std::string name, std::string cont = "");
		void update_parent_path(const std::string&);
		NodeType type() const;
		std::string path() const;
		std::string name() const;
		int count() const;
		size_t size() const;
	};
}

#endif // !SENECA_FILE_H

#pragma once

#include <string>
#include <vector>

namespace Crystal {
	namespace UI {

class FileSaveDialog
{
public:
	explicit FileSaveDialog(const std::string& name);

	void addFilter(char const* filter);

	void show();

	std::string getFileName() const;

private:
	std::vector< char const* > filters;
	char const* filename;
	char const* name;
};

	}
}
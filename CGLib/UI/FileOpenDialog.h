#pragma once

#include "IWindow.h"
#include <string>
#include <vector>

namespace Crystal {
	namespace UI {

class FileOpenDialog
{
public:
	explicit FileOpenDialog(const std::string& name);

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
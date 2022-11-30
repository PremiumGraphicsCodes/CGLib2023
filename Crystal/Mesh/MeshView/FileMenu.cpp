#include "FileMenu.h"

#include "CGLib/UI/Panel.h"
#include "CGLib/UI/MenuItem.h"

#include "CGLib/UI/FileOpenDialog.h"
#include "CGLib/UI/FileSaveDialog.h"

using namespace Crystal::UI;

FileMenu::FileMenu(const std::string& name, World* model, Renderer* canvas) :
	IMenu(name),
	world(model),
	renderer(canvas)
{
	add(new MenuItem("New", [&] { onNew(); }));
	add(new MenuItem("Import", [&] { onImport(); }));
	add(new MenuItem("Export", [&] { onExport(); }));
}

void FileMenu::onNew()
{
}

void FileMenu::onImport()
{
	FileOpenDialog view("");
	view.addFilter("*.pcd");
	view.addFilter("*.ply");
	view.addFilter("*.txt");
	//view.addFilter("*.*");
	view.show();
	const auto& filename = view.getFileName();
	if (!filename.empty()) {
		/*
		FileImporter importer;
		const auto isOk = importer.import(filename);
		if (isOk) {
			world->add(importer.getPointCloud());
		}
		*/
	}
}

void FileMenu::onExport()
{
	FileSaveDialog view("");
	view.addFilter("*.pcd");
	view.addFilter("*.ply");
	view.addFilter("*.txt");
	//view.addFilter("*.*");
	view.show();
	const auto& filename = view.getFileName();
	if (!filename.empty()) {
		//FileExporter exporter;
		//exporter.export_(filename);
	}
}

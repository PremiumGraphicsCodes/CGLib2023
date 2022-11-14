#include "FileMenu.h"
#include "CGLib/UI/FileOpenDialog.h"
#include "CGLib/UI/FileSaveDialog.h"
#include "Crystal/AppBase/MenuItem.h"

#include "FileImporter.h"
#include "FileExporter.h"

#include <iostream>

using namespace Crystal::PC;
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
		FileImporter importer;
		importer.import(filename);

		auto scene = new PointCloudScene();
		scene->setShape(importer.getPointCloud());

		auto presenter = std::make_unique<PointCloudPresenter>(scene, renderer->getPointRenderer());
		presenter->build();
		presenter->send();
		scene->setPresenter(std::move(presenter));
		world->getRootScene()->addScene(scene);
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

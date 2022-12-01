#include "FileMenu.h"

#include "CGLib/UI/Panel.h"
#include "CGLib/UI/MenuItem.h"

#include "CGLib/UI/FileOpenDialog.h"
#include "CGLib/UI/FileSaveDialog.h"

#include "FileImporter.h"
#include "FileExporter.h"

#include "World.h"

using namespace Crystal::Mesh;
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
	view.addFilter("*.obj");
	view.addFilter("*.stl");
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
	view.addFilter("*.obj");
	view.addFilter("*.stl");
	view.show();
	const auto& filename = view.getFileName();

	const auto meshes = world->getRootScene()->findScenesByType(typeid(PolygonMeshScene));

	if (!filename.empty()) {
		FileExporter exporter;
		for (auto m : meshes) {
			auto mm = static_cast<PolygonMeshScene*>(m);
			exporter.add(*mm->getShape());
		}
		exporter.export_(filename);
	}
}

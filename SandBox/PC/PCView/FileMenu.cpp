#include "FileMenu.h"
#include "CGLib/UI/FileOpenView.h"
#include "CGLib/UI/FileSaveView.h"
#include "Crystal/AppBase/MenuItem.h"

#include <iostream>

using namespace Crystal::UI;

FileMenu::FileMenu(const std::string& name, World* model, Renderer* canvas) :
	IMenu(name),
	world(model),
	renderer(renderer)
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
	FileOpenView view("");
	view.addFilter("*.stl");
	view.addFilter("*.obj");
	view.addFilter("*.mtl");
	view.addFilter("*.pcd");
	view.show();
	const auto& filename = view.getFileName();
	if (!filename.empty()) {
		/*
		FileImportCommand command;
		command.setArg(Fil::FilePathLabel, std::string(filename));
		bool isOk = command.execute(model);
		if (!isOk) {
			std::cout << "import failed." << std::endl;
		}
		else {
			const int newId = std::any_cast<int>(command.getResult(FileImportLabels::NewIdLabel));
			auto scene = model->getScenes()->findSceneById<Crystal::Scene::IScene*>(newId);
			auto presenter = scene->getPresenter();
			presenter->createView(getWorld()->getRenderer(), *getWorld()->getGLFactory());
//					scene->getParent()->se
				}
				*/
	}
	//canvas->update();
}

void FileMenu::onExport()
{
	FileSaveView view("");
	view.addFilter("*.stl");
	view.addFilter("*.obj");
	view.addFilter("*.mtl");
	view.addFilter("*.pcd");
	view.show();
	const auto& filename = view.getFileName();
	if (!filename.empty()) {
		/*
		Crystal::Command::Command command(FileExportLabels::FileExportCommandLabel);
		command.setArg(FileExportLabels::FilePathLabel, filename);
		const auto isOk = command.execute(model);
		if (!isOk) {
			std::cout << "export failed." << std::endl;
		}
		*/
	}
	//model->write(filename);
}

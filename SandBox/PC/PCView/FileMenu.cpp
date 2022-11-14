#include "FileMenu.h"
#include "CGLib/UI/FileOpenDialog.h"
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
	FileOpenDialog view("");
	view.addFilter("*.pcd");
	view.addFilter("*.ply");
	view.addFilter("*.txt");
	view.show();
	const auto& filename = view.getFileName();
	if (!filename.empty()) {
		/*
		auto scene = new PointCloudScene();
		PointCloudBuilder builder;
		builder.add(box, uNumView.getValue(), vNumView.getValue(), wNumView.getValue());
		const auto pc = builder.toPointCloud();
		const auto& points = pc->getPoints();
		for (auto& p : points) {
			p->setColor(ColorRGBAf(0, 0, 1, 0));
		}
		scene->setShape(std::move(builder.toPointCloud()));

		auto presenter = std::make_unique<PointCloudPresenter>(scene, renderer->getPointRenderer());
		presenter->build();
		presenter->send();
		scene->setPresenter(std::move(presenter));
		world->getRootScene()->addScene(scene);
		*/
	}
}

void FileMenu::onExport()
{
	/*
	FileSaveView view("");
	view.addFilter("*.stl");
	view.addFilter("*.obj");
	view.addFilter("*.mtl");
	view.addFilter("*.pcd");
	view.show();
	const auto& filename = view.getFileName();
	if (!filename.empty()) {
	}
	*/
}

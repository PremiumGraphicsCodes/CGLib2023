#include "gtest/gtest.h"

#include "../File/PLYFileWriter.h"

using namespace Crystal::Math;
using namespace Crystal::PC;

TEST(PLYFileWriterTest, TestWriteASCII)
{
	PLYFile ply;
	ply.properties.push_back(PLYProperty("x", PLYType::FLOAT));
	ply.properties.push_back(PLYProperty("y", PLYType::FLOAT));
	ply.properties.push_back(PLYProperty("z", PLYType::FLOAT));

	PLYPoint p1;
	p1.values.push_back(1.0f);
	p1.values.push_back(2.0f);
	p1.values.push_back(3.0f);
	ply.vertices.push_back(p1);
	PLYPoint p2;
	p2.values.push_back(2.0f);
	p2.values.push_back(3.0f);
	p2.values.push_back(4.0f);
	ply.vertices.push_back(p2);
	PLYPoint p3;
	p3.values.push_back(3.0f);
	p3.values.push_back(4.0f);
	p3.values.push_back(5.0f);
	ply.vertices.push_back(p3);

	PLYFileWriter writer;
	EXPECT_TRUE(writer.writeASCII("./TestFiles/PLYWriteTestASCII.ply", ply));
}

TEST(PLYFileWriterTest, TestWriteBinary)
{
	PLYFile ply;
	ply.properties.push_back(PLYProperty("x", PLYType::FLOAT));
	ply.properties.push_back(PLYProperty("y", PLYType::FLOAT));
	ply.properties.push_back(PLYProperty("z", PLYType::FLOAT));

	PLYPoint p1;
	p1.values.push_back(1.0f);
	p1.values.push_back(2.0f);
	p1.values.push_back(3.0f);
	ply.vertices.push_back(p1);
	PLYPoint p2;
	p2.values.push_back(2.0f);
	p2.values.push_back(3.0f);
	p2.values.push_back(4.0f);
	ply.vertices.push_back(p2);
	PLYPoint p3;
	p3.values.push_back(3.0f);
	p3.values.push_back(4.0f);
	p3.values.push_back(5.0f);
	ply.vertices.push_back(p3);

	PLYFileWriter writer;
	EXPECT_TRUE(writer.writeBinary("./TestFiles/PLYWriteTestBinary.ply", ply));
}
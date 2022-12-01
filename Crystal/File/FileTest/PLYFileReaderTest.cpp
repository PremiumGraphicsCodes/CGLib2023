#include "gtest/gtest.h"

#include "../File/PLYFileReader.h"

using namespace Crystal::Math;
using namespace Crystal::PC;

TEST(PLYFileReaderTest, TestReadASCII)
{
	PLYFileReader reader;
	const auto isOk = reader.read("./TestFiles/PLYWriteTestASCII.ply");
	EXPECT_TRUE(isOk);
	EXPECT_EQ(3, reader.getPLY().vertices.size());
}

TEST(PLYFileReaderTest, TestReadBinary)
{
	PLYFileReader reader;
	const auto isOk = reader.read("./TestFiles/PLYWriteTestBinary.ply");
	EXPECT_TRUE(isOk);
	EXPECT_EQ(3, reader.getPLY().vertices.size());
}
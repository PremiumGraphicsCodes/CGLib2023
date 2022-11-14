#include "gtest/gtest.h"

#include "../PC/TXTFileWriter.h"

using namespace Crystal::Math;
using namespace Crystal::IO;

TEST(TXTFileWriterTest, TestWrite)
{
	TXTFileWriter writer;
	writer.add(Vector3dd(0, 1, 2));
	writer.add(Vector3dd(3, 4, 5));
	writer.add(Vector3dd(6, 7, 8));

	const auto isOk = writer.write("./TestFiles/TXTFileWriterTest.txt");
	EXPECT_TRUE(isOk);
}
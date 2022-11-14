#include "gtest/gtest.h"

#include "../Space/IndexedSortBasedSeacher.h"

using namespace Crystal::Math;
using namespace Crystal::Space;

TEST(IndexedSortBasedSearcherTest, TestSearch)
{
	IndexedSortBasedSearcher searcher(1.0f);
	searcher.add(Vector3df(0, 0, 0));
	searcher.add(Vector3df(0.5, 0, 0));
	searcher.search();
	const auto pairs = searcher.getPairs();
	EXPECT_EQ(1, pairs.size());
}
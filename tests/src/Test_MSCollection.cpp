#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include <catch2/catch.hpp>
#include "MSCraftDemo.hpp"

SCENARIO("MS base cases")
{
	GIVEN("Generated records") {
		auto data = MS::populateDummyData("testdata", 1000);
		REQUIRE(data.size() == 1000);

		WHEN("Search by column 1 for existing record") {
			auto filteredSet = MS::findMatchingRecords(data, "column1", "testdata500");
			THEN("the record is found") {
				REQUIRE(filteredSet.size() == 1);

				AND_WHEN("the record is deleted") {
					MS::DeleteRecordByID(data, 500);
					filteredSet = MS::findMatchingRecords(data, "column1", "testdata500");

					THEN("the record won't be found") {
						REQUIRE(filteredSet.size() == 0);
					}
				}
			}
		}
		
		WHEN("Search by column 2 for existing records") {
			auto filteredSet = MS::findMatchingRecords(data, "column2", "24");
			THEN("the records are found") {
				REQUIRE(filteredSet.size() == 10);

				AND_WHEN("records are deleted") {
					int target = 24;
					for (size_t i = 0; i < 10; i++)
					{
						MS::DeleteRecordByID(data, target);
						target += 100;
					}
					filteredSet = MS::findMatchingRecords(data, "column2", "24");

					THEN("the records won't be found") {
						REQUIRE(filteredSet.size() == 0);
					}
				}
			}
		}
	}
}

TEST_CASE("MS performance tests")
{
	auto data = MS::populateDummyData("testdata", 1000);

	SECTION("finding a record") {
		MS::RecordsCollection result{};
		BENCHMARK("column1 testdata500") {
			result = MS::findMatchingRecords(data, "column1", "testdata500");
		};
		REQUIRE(result.size() == 1);

		BENCHMARK("column2 24") {
			result = MS::findMatchingRecords(data, "column2", "24");
		};
		REQUIRE(result.size() == 10);
	}

	SECTION("deleting records") {
		BENCHMARK("delete one record") {
			MS::DeleteRecordByID(data, 500);
		};

		BENCHMARK("delete multiple records") {
			int target = 24;
			for (size_t i = 0; i < 10; i++)
			{
				MS::DeleteRecordByID(data, target);
				target += 100;
			}
		};
	}
}

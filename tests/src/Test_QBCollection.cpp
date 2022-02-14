#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include <catch2/catch.hpp>
#include "QBCraftDemo.h"

SCENARIO("QB base cases")
{
	GIVEN("Generated records") {
		auto data = QB::populateDummyData("testdata", 1000);
		REQUIRE(data.size() == 1000);

		WHEN("Search by column 1 for existing record") {
			auto filteredSet = QB::QBFindMatchingRecords(data, "column1", "testdata500");
			THEN("the record is found") {
				REQUIRE(filteredSet.size() == 1);

				AND_WHEN("the record is deleted") {
					QB::DeleteRecordByID(data, 500);
					filteredSet = QB::QBFindMatchingRecords(data, "column1", "testdata500");

					THEN("the record won't be found") {
						REQUIRE(filteredSet.size() == 0);
					}
				}
			}
		}

		WHEN("Search by column 2 for existing records") {
			auto filteredSet = QB::QBFindMatchingRecords(data, "column2", "24");
			THEN("the records are found") {
				REQUIRE(filteredSet.size() == 10);

				AND_WHEN("records are deleted") {
					int target = 24;
					for (size_t i = 0; i < 10; i++)
					{
						QB::DeleteRecordByID(data, target);
						target += 100;
					}
					filteredSet = QB::QBFindMatchingRecords(data, "column2", "24");

					THEN("the records won't be found") {
						REQUIRE(filteredSet.size() == 0);
					}
				}
			}
		}

	}
}

TEST_CASE("QB base performance tests")
{
	auto data = QB::populateDummyData("testdata", 1000);

	SECTION("finding a record") {
		QB::QBRecordCollection result{};
		BENCHMARK("column1 testdata500") {
			result = QB::QBFindMatchingRecords(data, "column1", "testdata500");
		};
		REQUIRE(result.size() == 1);

		BENCHMARK("column2 24") {
			result = QB::QBFindMatchingRecords(data, "column2", "24");
		};
		REQUIRE(result.size() == 10);
	}

	SECTION("deleting records") {
		BENCHMARK("delete one record") {
			QB::DeleteRecordByID(data, 500);
		};

		BENCHMARK("delete multiple records") {
			int target = 24;
			for (size_t i = 0; i < 10; i++)
			{
				QB::DeleteRecordByID(data, target);
				target += 100;
			}
		};
	}
}
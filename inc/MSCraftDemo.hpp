#pragma once
#include <string>
#include <vector>

namespace MS
{

	struct RecordsCollection
	{
		const size_t size() const {
			return recordIds.size();
		}

		std::vector<unsigned int> recordIds;
		std::vector<std::string> column1;
		std::vector<long> column2;
		std::vector<std::string> column3;
	};

	void extractRecordDataForIndex(const RecordsCollection& records, const size_t& index, RecordsCollection& outRecords)
	{
		outRecords.recordIds.emplace_back(records.recordIds[index]);
		outRecords.column1.emplace_back(records.column1[index]);
		outRecords.column2.emplace_back(records.column2[index]);
		outRecords.column3.emplace_back(records.column3[index]);
	}

	RecordsCollection populateDummyData(const std::string& prefix, int numRecords)
	{
		RecordsCollection records{};
		records.recordIds.reserve(numRecords);
		records.column1.reserve(numRecords);
		records.column2.reserve(numRecords);
		records.column3.reserve(numRecords);

		for (size_t i = 0; i < numRecords; i++)
		{
			records.recordIds.emplace_back(i);
			records.column1.emplace_back(prefix + std::to_string(i));
			records.column2.emplace_back(i % 100);
			records.column3.emplace_back(std::to_string(i) + prefix);
		}
		return records;
	}

	/*template<class Filter>
	void collectMatchingRecords(const RecordsCollection& records, RecordsCollection& outRecords, Filter&& filter)
	{
		for (size_t i = 0; i < records.size(); i++) {
			if (filter(i)) {
				extractRecordDataForIndex(records, i, outRecords);
			}
		}
	}*/

	RecordsCollection findMatchingRecords(const RecordsCollection& records, const std::string& columnName, const std::string& matchString)
	{
		RecordsCollection result{};
		
		if (columnName == "column0") {
			unsigned int matchValue = std::stoi(matchString);
			auto it = std::find(std::begin(records.recordIds), std::end(records.recordIds), matchValue);
			if (it != records.recordIds.end()) {
				const auto index = it - records.recordIds.begin();
				extractRecordDataForIndex(records, index, result);
			}
		}
		else if (columnName == "column1") {
			//collectMatchingRecords(records, result, [&records, &matchString](const int& i) { return records.column1[i].find(matchString) != std::string::npos; });
			for (size_t i = 0; i < records.column1.size(); i++) {
				if (records.column1[i].find(matchString) != std::string::npos) {
					extractRecordDataForIndex(records, i, result);
				}
			}
		}
		else if (columnName == "column2") {
			long matchValue = std::stol(matchString);
			//collectMatchingRecords(records, result, [&records, &matchValue](const int& i) { return records.column2[i] == matchValue; });
			for (size_t i = 0; i < records.column2.size(); i++) {
				if (records.column2[i] == matchValue) {
					extractRecordDataForIndex(records, i, result);
				}
			}
		}
		else if (columnName == "column3") {
			//collectMatchingRecords(records, result, [&records, &matchString](const int& i) { return records.column3[i].find(matchString) != std::string::npos; });
			for (size_t i = 0; i < records.column3.size(); i++) {
				if (records.column3[i].find(matchString) != std::string::npos) {
					extractRecordDataForIndex(records, i, result);
				}
			}
		}

		return result;
	}

	void DeleteRecordByID(RecordsCollection& records, unsigned int id)
	{
		auto it = std::find(std::begin(records.recordIds), std::end(records.recordIds), id);
		if (it != std::end(records.recordIds)) {
			const auto index = it - records.recordIds.begin();
			records.recordIds.erase(it);
			records.column1.erase(std::begin(records.column1) + index);
			records.column2.erase(std::begin(records.column2) + index);
			records.column3.erase(std::begin(records.column3) + index);
		}
	}

};

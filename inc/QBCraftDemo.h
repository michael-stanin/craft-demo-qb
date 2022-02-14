#pragma once
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <list>

namespace QB
{
    /**
    Represents a Record Object
    */
    struct QBRecord
    {
        unsigned int column0; // unique id column
        std::string column1;
        long column2;
        std::string column3;
    };

    /**
    Represents a Record Collections
    */
    typedef std::vector<QBRecord> QBRecordCollection;

    /**
        Return records that contains a string in the StringValue field
        records - the initial set of records to filter
        matchString - the string to search for
    */
    QBRecordCollection QBFindMatchingRecords(const QBRecordCollection& records, const std::string & columnName, const std::string& matchString)
    {
        QBRecordCollection result;
        std::copy_if(records.begin(), records.end(), std::back_inserter(result), [&](QBRecord rec) {
            if (columnName == "column0") {
                unsigned int matchValue = std::stoul(matchString);
                return matchValue == rec.column0;
            }
            else if (columnName == "column1") {
                return rec.column1.find(matchString) != std::string::npos;
            }
            else if (columnName == "column2") {
                long matchValue = std::stol(matchString);
                return matchValue == rec.column2;
            }
            else if (columnName == "column3") {
                return rec.column3.find(matchString) != std::string::npos;
            }
            else {
                return false;
            }
        });
        return result;
    }

    void DeleteRecordByID(QBRecordCollection& records, unsigned int id)
    {
        records.erase(std::remove_if(std::begin(records), std::end(records), [&id](const QBRecord& record) { return record.column0 == id; }), std::end(records));
    }

    /**
    Utility to populate a record collection
    prefix - prefix for the string value for every record
    numRecords - number of records to populate in the collection
    */
    QBRecordCollection populateDummyData(const std::string& prefix, int numRecords)
    {
        QBRecordCollection data;
        data.reserve(numRecords);
        for (unsigned int i = 0; i < numRecords; i++)
        {
            QBRecord rec = { i, prefix + std::to_string(i), i % 100, std::to_string(i) + prefix };
            data.emplace_back(rec);
        }
        return data;
    }
}

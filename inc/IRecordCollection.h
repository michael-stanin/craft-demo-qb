#pragma once


template <class RecordCollection>
class IRecordCollection
{
public:

	virtual RecordCollection& FindMatchingRecords(const RecordCollection& records, const std::string& columnName, const std::string& matchString) = 0;
	virtual void			  DeleteRecordByID(			RecordCollection& records, unsigned int id) = 0;
};

#ifndef _EXTRAS_H_
#define _EXTRAS_H_

#include "record.h"

void defrag_empty_record(Record[]);
void defrag_wrong_record(Record[]);
void defrag_record(Record[]);
void sort_record(Record[]);
void sort_data(Record[], char field_select[20], int index);
void search_multiple_record(Record[]);
void delete_range(Record records[]);

#endif
#ifndef _BASE_H_
#define _BASE_H_

#include "record.h"

// function prototypes
void print_all_records(Record[]);
void add_record(Record[]);
int add_file_record(Record records[]);
void delete_record(Record[]);
void update_record(Record[]);
void search_record(Record[]);
int load_record(Record[]);
void save_record(Record[]);
void display_search_data(Record records[], char temp[], int index);
void display_player_data(Record records[]);

#endif
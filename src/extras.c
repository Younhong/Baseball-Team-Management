#include <stdio.h>
#include <string.h>
#include "extras.h"
#include "base.h"

int count;
char selected[1];

// Function: defragment_empty_record()
// Input: record - array of Records; this may contain empty elements in the middle
// Output: none
// - choose to defrag empty data or wrong data
void defrag_record(Record records[]) {
  // option 1 is to defrag empty data, option 2 is to defrag data that are in wrong range.
  printf("Choose option(0: Defrag Empty Data, 1: Defrag Wrong Data): ");
  scanf("%s", selected);

  // defrag empty data
  if (!strcmp(selected, "0")) {
    defrag_empty_record(records);
  }
  // defrag wrong range data
  else if (!strcmp(selected, "1")) {
    defrag_wrong_record(records);
  }
  // wrong option
  else {
    printf("Not an option\n");
    return;
  }

  printf("To Save Data, Enter 9 From Option Menu. To Quit, Enter 10 From Option Menu!\n");

  return;
}

// Function: defragment_empty_record()
// Input: record - array of Records; this may contain empty elements in the middle
// Output: none
// - send empty name or position to the end
void defrag_empty_record(Record records[]){
  Record tempRecord;
  // option 1 is to defrag current data, option 2 is to defrag from reading file.
  printf("Choose Option(0: Defrag From Current Data, 1: Defrag From File): ");
  scanf("%s", selected);

  // defrag from file
  if (!strcmp(selected, "1")) {
    // if file does not exist
    if (load_record(records) == -1) {
      return;
    }
  }
  // did not chose either option
  else if (strcmp(selected, "0")) {
    printf("Not an option\n");
    return;
  }

  // if no record data
  if (count == 0) {
    printf("No record to defrag\n");
    return;
  }

  // defrag by position field
  for (int i = 0; i < count; i++) {
    if (!strcmp(records[i].position, "*")) {
      for (int j = i; j < count; j++) {
        // do not change if either one of position or name is ""
        if (strcmp(records[j].position, "\"\"")  && strcmp(records[j].name, "\"\"")) {
          // swap
          tempRecord = records[i];
          records[i] = records[j];
          records[j] = tempRecord;
        }
      }
    }
  }
  // defrag by name field
  for (int i = 0; i < count; i++) {
    if (!strcmp(records[i].name, "*")) {
      for (int j = i; j < count; j++) {
        // do not change if either one of position or name is ""
        if (strcmp(records[j].name, "*") && strcmp(records[j].position, "*")) {
          // swap
          tempRecord = records[i];
          records[i] = records[j];
          records[j] = tempRecord;
        }
      }
    }
  }

  printf("\nDefrag Result: \n");

  for (int i = 0; i < count; i++) {
    display_player_data(records);
    printf("\n");
    records++;
  }

  printf("Sorted Empty Record Successfully\n");
	
  return; 
}

// Function: defragment_wrong_record()
// Input: record - array of Records; this may contain empty elements in the middle
// Output: none
// - send wrong data(negative, 0 or out of range data) to the end
void defrag_wrong_record(Record records[]) {
  Record tempRecord;
  // option 1 is to defrag from current data, option 2 is to defrag from reading new file.
  printf("Choose Option(0: Defrag From Current Data, 1: Defrag From File): ");
  scanf("%s", selected);

  // defrag from file
  if (!strcmp(selected, "1")) {
    // if file does not exist
    if (load_record(records) == -1) {
      return;
    }
  }
  // did not chose either option
  else if (strcmp(selected, "0")) {
    printf("Not an option\n");
    return;
  }

  // if no data
  if (count == 0) {
    printf("No record to defrag\n");
    return;
  }

  for (int i = 0; i < count; i++) {
    // below are variable range
    // if current data is in those range, swap with data that are not in those range.
    if (
      records[i].age <= 10 || records[i].age >= 50 
      || records[i].weight <= 30 || records[i].weight >= 150 
      || records[i].height <= 120 || records[i].height >= 220  
      || records[i].group_of_year <= 2000 || records[i].group_of_year >= 2020
      || records[i].uniform_number <= 0 || records[i].uniform_number >= 100
    ) {
      for (int j = i; j < count; j++) {
        if (
          records[j].age > 10 && records[j].age < 50 
          && records[j].weight > 30  && records[j].weight < 150
          && records[j].height > 120 && records[j].height < 220
          && records[j].group_of_year > 2000 && records[j].group_of_year < 2020
          && records[j].uniform_number > 0 && records[j].uniform_number < 100 
          ) {
          tempRecord = records[i];
          records[i] = records[j];
          records[j] = tempRecord;
        }
      }
    }
  }

  printf("\nDefrag Result: \n");

  for (int i = 0; i < count; i++) {
    display_player_data(records);
    printf("\n");
    records++;
  }

  printf("Sorted Useless Record Successfully\n");

  return; 
}

// Function: sort_record()
// Input: record - array of Records; this may contain empty elements in the middle
// Output: none
// - sort record based on given criteria
void sort_record(Record records[]) {
  char field_select[20];
  char up_or_down[4];

   // option 1 is to sort from current data, option 2 is to sort from new file.
  printf("Choose Option(0: Sort From Current Data, 1: Sort From File): ");
  scanf("%s", selected);

  // sort from file
  if (!strcmp(selected, "1")) {
    // if file does not exist
    if (load_record(records) == -1) {
      return;
    }
  }
  // did not chose either option
  else if (strcmp(selected, "0")) {
    printf("Not an option\n");
    return;
  }

  // if no data
  if (count == 0) {
    printf("No record to sort\n");
    return;
  }

  // choosing sorting option
  printf("Enter field you want to sort (age, height, weight, year, uniform_number): ");
  scanf("%s", field_select);
  
  // sort by age
  if (!strcmp(field_select, "age")) {
    sort_data(records, field_select, 0);
  }
  // sort by height
  else if (!strcmp(field_select, "height")){
    sort_data(records, field_select, 1);
  }
  // sort by weight
  else if (!strcmp(field_select, "weight")){
    sort_data(records, field_select, 2);
  }
  // sort by year
  else if (!strcmp(field_select, "year")){
    sort_data(records, field_select, 3);
  }
  // sort by uniform number
  else if (!strcmp(field_select, "uniform_number")){
    sort_data(records, field_select, 4);
  }
  // did not chose any proper option
  else {
    printf("Not an option\n");
    return;
  }

  printf("Sorted Record Successfully\n");
  printf("To Save Data, Enter 9 From Option Menu. To Quit, Enter 10 From Option Menu!\n");

  return;
}

// Function: sort_data()
// Input: record - array of Records; this may contain empty elements in the middle
// Output: none
// - logic to sort in increasing or decreasing order
void sort_data(Record records[], char field_select[20], int index) {
  Record tempRecord;
  char up_or_down[4];
  int temp1, temp2;

  // choose to sort by decreasing order or increasing order
  printf("Enter \"up\" to sort by increasing order, \"down\" to sort by decreasing order: ");
  scanf("%s", up_or_down);

  printf("Sorting by %s.....\n", field_select);

  // sort by increasing order
  if (!strcmp(up_or_down, "up")) {
    for (int i = 0; i < count; i++) {
      for (int j = i+1; j < count; j++) {
        if (index == 0) {
          temp1 = records[i].age;
          temp2 = records[j].age;
        }
        else if (index == 1) {
          temp1 = records[i].height;
          temp2 = records[j].height;
        }
        else if (index == 2) {
          temp1 = records[i].weight;
          temp2 = records[j].weight;
        }
        else if (index == 3) {
          temp1 = records[i].group_of_year;
          temp2 = records[j].group_of_year;
        }
        else if (index == 4) {
          temp1 = records[i].uniform_number;
          temp2 = records[j].uniform_number;
        }
        
        if (temp1 > temp2) {
          tempRecord = records[i];
          records[i] = records[j];
          records[j] = tempRecord;
        }
      }
    }
  }
  // sort by decreasing order
  else if (!strcmp(up_or_down, "down")) {
    for (int i = 0; i < count; i++) {
      for (int j = i+1; j < count; j++) {
        if (index == 0) {
          temp1 = records[i].age;
          temp2 = records[j].age;
        }
        else if (index == 1) {
          temp1 = records[i].height;
          temp2 = records[j].height;
        }
        else if (index == 2) {
          temp1 = records[i].weight;
          temp2 = records[j].weight;
        }
        else if (index == 3) {
          temp1 = records[i].group_of_year;
          temp2 = records[j].group_of_year;
        }
        else if (index == 4) {
          temp1 = records[i].uniform_number;
          temp2 = records[j].uniform_number;
        }
        
        if (temp1 < temp2) {
          tempRecord = records[i];
          records[i] = records[j];
          records[j] = tempRecord;
        }
      }
    }
  }
  // wrong option
  else {
    printf("Not an option\n");
    return;
  }

  // display sorted data for check
  for (int i = 0; i < count; i++) {
    display_player_data(records);
    printf("\n");
    records++;
  }

  return;
}
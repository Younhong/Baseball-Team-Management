#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "base.h"

char selected[1];
int count = 0;

// Function: display_player_data
// Input: record element
// Output: none
// - Display each record element
void display_player_data(Record records[]) {
  printf("Name: %s\n", records->name);
  printf("Position: %s\n", records->position);
  printf("Age: %d\n", records->age);
  printf("Height: %.1f\n", records->height);
  printf("Weight: %.1f\n", records->weight);
  printf("Year of Join: %d\n", records->group_of_year);
  printf("Uniform Number: %d\n", records->uniform_number);

  return;
}

// Function: print_all_records()
// Input: record - array of Records; this may contain empty elements in the middle
// Output: none
// - Display all the current record or file record
void print_all_records(Record records[]){
  // Option 1 is to read from current data records, option 2 is to read from file. If you choose this option, current data will be overwritten.
  printf("Choose display option(0: Current Data, 1: File Data): ");
  scanf("%s", selected);

  // diplay data for option1
  if (!strcmp(selected, "0")) {
    for (int i = 0; i < count; i++) {
      display_player_data(records);

      printf("\n");
      records++;
    }
  }
  // display for option2
  else if (!strcmp(selected, "1")) {
    if (load_record(records) == -1) {
      return;
    }
  }
  // did not chose either of them
  else {
    printf("Not an option\n");
    return;
  }

  // if record is empty
  if (count == 0) {
    printf("No record to display\n");
    return;
  }

  printf("Displayed Record Successfully\n");
  printf("To Save Data, Enter 9 From Option Menu. To Quit, Enter 10 From Option Menu!\n");

  return;
}

// Function: add_file_record()
// Input: record - array of Records; this may contain empty elements in the middle
// Output: none
// - Adding file record to current data
int add_file_record(Record records[]) {
  char filename[20];
  char text[4] = ".txt";
  char csv[4] = ".csv";
  char * status[7];
  int i = 0;
  char temp[100];

  printf("Enter 0 for text file, 1 for csv file: ");
  scanf("%s", selected);

  printf("Enter file name to load: ");
  scanf("%s", filename);

  if (!strcmp(selected, "0")){
    strncat(filename, text, 4);
  }   
  else if (!strcmp(selected, "1")){
    strncat(filename, csv, 4);
  } 

  // open file
  FILE *f = fopen(filename, "r");

  // when file name does not exist
  if (f == NULL) {
    fputs("File Error\n", stderr);
    return -1;
  }

  // move to the end of data file to add new data
  for (int i = 0; i < count; i++) {
    records++;
  }

  if (!strcmp(selected, "0")) {
    // read data from file, save it to proper variable. Use temporary var to choose data I need.
    while(!feof(f)) {
      fscanf(f, "%s", temp);
      fscanf(f, "%s", records->name);
      fscanf(f, "%s", temp);
      fscanf(f, "%s", records->position);
      fscanf(f, "%s", temp);
      fscanf(f, "%d", &records->age);
      fscanf(f, "%s", temp);
      fscanf(f, "%f", &records->height);
      fscanf(f, "%s", temp);
      fscanf(f, "%f", &records->weight);
      fscanf(f, "%s", temp);
      fscanf(f, "%d", &records->group_of_year);
      fscanf(f, "%s", temp);
      fscanf(f, "%d", &records->uniform_number);

      records++;
      count++;
    }    
  }
  else if (!strcmp(selected, "1")){
    fgets(temp, sizeof(temp), f);    
    while(!feof(f)) {
      fgets(temp, sizeof(temp), f);

      char * token = strtok(temp, ",");
      int i = 0;
      while (token != NULL) {
        status[i++] = token;
        token = strtok(NULL, ",");
      }
      strcpy(records->name, status[0]);
      strcpy(records->position, status[1]);
      records->age = atoi(status[2]);
      records->height = atof(status[3]);
      records->weight = atof(status[4]);
      records->group_of_year = atoi(status[5]);
      records->uniform_number = atoi(status[6]);   

      records++;
      count++;
    }
  }

  fclose(f);


  return 0;
}

// Function: add_record()
// Input: record - array of Records; this may contain empty elements in the middle
// Output: none
// - Add new record through keyboard input or file
void add_record(Record records[]){
  // option 1 is to add new data from keyboard input, option 2 is to add from file input.
  printf("Choose Option(0: Add New Data, 1: Add File Data): ");
  scanf("%s", selected);

  // chose keyboard input
  if (!strcmp(selected, "0")) {
    // move to the end of file to add new data
    for (int i = 0; i < count; i++) {
      records++;
    }
    
    // enter data input
    printf("Enter New Member's Info\n");
    printf("Name: ");
    scanf("%s", records->name);
    printf("Position: ");
    scanf("%s", records->position);
    printf("Age: ");
    scanf("%d", &records->age);
    printf("Height: ");
    scanf("%f", &records->height);
    printf("Weight: ");
    scanf("%f", &records->weight);
    printf("Year of Join: ");
    scanf("%d", &records->group_of_year);
    printf("Uniform Number: ");
    scanf("%d", &records->uniform_number);

    count++;
  }
  // chose file input
  else if (!strcmp(selected, "1")) {
    // if file does not exist
    if (add_file_record(records) == -1) {
      return;
    }
  }
  // wrong option
  else {
    printf("Not an option\n");
    return;
  }

  printf("Added Record Successfully\n");
  printf("To Save Data, Enter 9 From Option Menu. To Quit, Enter 10 From Option Menu!\n");

  return;
}

// Function: delete_record()
// Input: record - array of Records; this may contain empty elements in the middle
// Output: none
// - Delete specific record from array
void delete_record(Record records[]) {
  // option 1 is to delete from current data record, option 2 is to delete from reading new file.
  printf("Choose Option(0: Delete From Current Data, 1: Delete From File): ");
  scanf("%s", selected);

  char user[20];
  char yes_or_no[3];
  char position[20];
  char temp[20];

  // delete from file
  if (!strcmp(selected, "1")) {
    if (load_record(records) == -1) {
      return;
    }
  }
  // did not chose either of them
  else if (strcmp(selected, "0")) {
    printf("Not an option\n");
    return;
  }

  // current data is empty
  if (count == 0) {
    printf("No record to delete\n");
    return;
  }

  // 0: delete player(delete all field of player), 1: delete player position(keep other data)
  // can delete every data that fits to condition
  printf("Enter 0 to delete player's data, 1 to delete player's position: ");
  scanf("%s", selected);

  // deleting player
  if (!strcmp(selected, "0")) {
    printf("Enter player's name you want to delete: ");
    scanf("%s", user);

    for (int i = 0; i < count; i++) {
      // if input player name is same as current data, check whether to delete or not
      if (!strcmp(records->name, user)) {
        printf("Current data of %s is\n", records->name);
        display_player_data(records);
        printf("Enter y to continue, n to quit: ");
        scanf("%s", yes_or_no);

        // if yes, delete field. string to "", int to 0
        if (!strcmp(yes_or_no, "y")) {
          strcpy(records->name, "*");
          strcpy(records->position, "*");
          records->age = 0;
          records->height = 0;
          records->weight = 0;
          records->group_of_year = 0;
          records->uniform_number = 0;
        }
        // if no, cancel
        else if (!strcmp(yes_or_no, "n")) {
          printf("Cancel Delete\n");
        }
        // wrong option
        else {
          printf("Not an option\n");
          return;
        }
      }
      records++;
    }
  }
  // deleting position
  else if (!strcmp(selected, "1")) {
    printf("Enter player's position: ");
    scanf("%s", position);

    for (int i = 0; i < count; i++) {
      // if input position is same as current data, check whether to delete or not
      if (!strcmp(records->position, position)) {
        display_player_data(records);
        printf("Enter y to continue, n to quit: ");
        scanf("%s", yes_or_no);
        
        // if yes, change position to ""
        if (!strcmp(yes_or_no, "y")) {
          strcpy(records->position, "*");
        }
        // if no, cancel
        else if (!strcmp(yes_or_no, "n")) {
          printf("Cancel Update\n");
        }
        // wrong option
        else {
          printf("Not an option\n");
          return;
        }
      }
      records++;
    }
  }
  // wrong option
  else {
    printf("Not an option\n");
    return;
  }

  printf("Deleted Record Successfully\n");
  printf("To Save Data, Enter 9 From Option Menu. To Quit, Enter 10 From Option Menu!\n");

  return;
}

// Function: update_record()
// Input: record - array of Records; this may contain empty elements in the middle
// Output: none
// - Update specific record from array
// - 1. Change data by user name(Can change all the data of user except name)
// - 2. Change only position
void update_record(Record records[]) {
  // option 1 is to update current data record, option 2 is to update from file.
  printf("Choose Option(0: Update From Current Data, 1: Update From File): ");
  scanf("%s", selected);
  char user[20];
  char position[20];
  char yes_or_no[3];
  char temp[20];

  // chose to update current data
  if (!strcmp(selected, "1")) {
    if (load_record(records) == -1) {
      return;
    }
  }
  // did not chose either
  else if (strcmp(selected, "0")) {
    printf("Not an option\n");
    return;
  }

  // current data is empty
  if (count == 0) {
    printf("No record to update\n");
    return;
  }

  // 0: update player's data, 1: update only position
  // can update every data that fits in to condition
  printf("Enter 0 to update player's data, 1 to update player's position: ");
  scanf("%s", selected);

  // update player data
  if (!strcmp(selected, "0")) {
    printf("Enter player's name you want to update: ");
    scanf("%s", user);

    for (int i = 0; i < count; i++) {
      // if input player name is same as current data, ask whether to update or not.
      if (!strcmp(records->name, user)) {
        printf("Current data of %s is\n", records->name);
        display_player_data(records);
        printf("Enter y to continue, n to quit: ");
        scanf("%s", yes_or_no);

        // if yes,enter new data for update
        if (!strcmp(yes_or_no, "y")) {
          printf("Enter New Data For Player\n");
          printf("Position: ");
          scanf("%s", records->position);
          printf("Age: ");
          scanf("%d", &records->age);
          printf("Height: ");
          scanf("%f", &records->height);
          printf("Weight: ");
          scanf("%f", &records->weight);
          printf("Year of Join: ");
          scanf("%d", &records->group_of_year);
          printf("Uniform Number: ");
          scanf("%d", &records->uniform_number);
        }
        // if no, cancel
        else if (!strcmp(yes_or_no, "n")) {
          printf("Cancel Update\n");
        }
        // wrong option
        else {
          printf("Not an option\n");
          return;
        }
      }
      records++;
    }
  }
  // update player's position
  else if (!strcmp(selected, "1")) {
    printf("Enter player's position: ");
    scanf("%s", position);

    for (int i = 0; i < count; i++) {
      /// if input position is same as current data, ask wheter to update or not.
      if (!strcmp(records->position, position)) {
        display_player_data(records);
        printf("Enter y to continue, n to quit: ");
        scanf("%s", yes_or_no);

        // if yes, enter new position
        if (!strcmp(yes_or_no, "y")) {
          printf("Enter New Position For the Player: ");
          scanf("%s", temp);
          strcpy(records->position, temp);
        }
        // if no, cancel
        else if (!strcmp(yes_or_no, "n")) {
          printf("Cancel Update\n");
        }
        // wrong option
        else {
          printf("Not an option\n");
          return;
        }
      }
      records++;
    }
  }
  // wrong option
  else {
    printf("Not an option\n");
    return;
  }

  printf("Updated Record Successfully\n");
  printf("To Save Data, Enter 9 From Option Menu. To Quit, Enter 10 From Option Menu!\n");

  return;
}

// Function: search_record()
// Input: record - array of Records; this may contain empty elements in the middle
// Output: none
// - Search specific record from array
void search_record(Record records[]) {
  // option 1 is to search from current data record, option 2 is to search from new file.
  printf("Choose Option(0: Search From Current Data, 1: Search From File): ");
  scanf("%s", selected);
  char temp[20];

  // search from new data
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

  // empty data
  if (count == 0) {
    printf("No record to search\n");
    return;
  }
  
  // select to search by name or position
  printf("Enter the type of data you want to search ");
  printf("(name or position): ");
  scanf("%s", selected);

  // search by name
  if (!strcmp(selected, "name")) {
    printf("Enter name you want to find: ");
    scanf("%s", temp);
    display_search_data(records, temp, 0);
  }
  // search by position
  else if (!strcmp(selected, "position")) {
    printf("Enter position you want to find: ");
    scanf("%s", temp);
    display_search_data(records, temp, 1);
  }
  // wrong option
  else {
    printf("Not an option\n");
    return;
  }

  printf("Search Ended!\n");

  printf("To Save Data, Enter 9 From Option Menu. To Quit, Enter 10 From Option Menu!\n");

  return;
}

// Function: display_data()
// Input: record - array of Records; this may contain empty elements in the middle
// Output: none
// - Display searched record(String type data)
void display_search_data(Record records[], char temp[], int index) {
  char data[20];
  for (int i = 0; i < count; i++) {
    // search by name
    if (index == 0) {
      // display if data matches
      if (!strcmp(records->name, temp)) {
        display_player_data(records);
        printf("\n");
      }
    }
    // search by position
    else if (index == 1) {
      // display if data matches
      if (!strcmp(records->position, temp)) {
        display_player_data(records);
        printf("\n");
      };
    }
    records++;
  }

  return;
} 

// Function: load_record()
// Input: record - array of Records; this may contain empty elements in the middle
// Output: none
// - load record from file 
// - this function will overwrite current data, so be careful when using it.
int load_record(Record records[]) {
  char filename[20];
  char text[4] = ".txt";
  char csv[4] = ".csv";
  char * status[7];
  int i = 0;
  char temp[100];

  printf("Enter 0 for text file, 1 for csv file: ");
  scanf("%s", selected);

  printf("Enter file name to load: ");
  scanf("%s", filename);

  if (!strcmp(selected, "0")){
    strncat(filename, text, 4);
  }   
  else if (!strcmp(selected, "1")){
    strncat(filename, csv, 4);
  } 

  // open file
  FILE *f = fopen(filename, "r");

  // if file does not exist
  if (f == NULL) {
    fputs("File Error\n", stderr);
    return -1;
  }
  // initialize record number to 0
  count = 0;

  if (!strcmp(selected, "0")){
    // until reading end of file, save data to record field
    while(!feof(f)) {
      fscanf(f, "%s", temp);
      fscanf(f, "%s", records->name);
      fscanf(f, "%s", temp);
      fscanf(f, "%s", records->position);
      fscanf(f, "%s", temp);
      fscanf(f, "%d", &records->age);
      fscanf(f, "%s", temp);
      fscanf(f, "%f", &records->height);
      fscanf(f, "%s", temp);
      fscanf(f, "%f", &records->weight);
      fscanf(f, "%s", temp);
      fscanf(f, "%d", &records->group_of_year);
      fscanf(f, "%s", temp);
      fscanf(f, "%d", &records->uniform_number);

      display_player_data(records);
      printf("\n");
      records++;
      count++;
    }
  }  
  else if (!strcmp(selected, "1")){
    fgets(temp, sizeof(temp), f);    
    while(!feof(f)) {
      fgets(temp, sizeof(temp), f);

      char * token = strtok(temp, ",");
      int i = 0;
      while (token != NULL) {
        status[i++] = token;
        token = strtok(NULL, ",");
      }
      strcpy(records->name, status[0]);
      strcpy(records->position, status[1]);
      records->age = atoi(status[2]);
      records->height = atof(status[3]);
      records->weight = atof(status[4]);
      records->group_of_year = atoi(status[5]);
      records->uniform_number = atoi(status[6]);   

      display_player_data(records);
      printf("\n"); 
      records++;
      count++;
    }
  }

  fclose(f);

  return 0;
}

// Function: save_record()
// Input: record - array of Records; this may contain empty elements in the middle
// Output: none
// - save current record to a text file
void save_record(Record records[]) {
  char filename[20];
  char text[4] = ".txt";
  char csv[4] = ".csv";
  
  // if no data
  if (count == 0) {
    printf("No record to save\n");
    return;
  }

  // option 1 is to save as text format(report format), option 2 is to save as any format you want.
  printf("Choose Option(0: Save as report format(txt), 1: Save as data format(csv)): ");

  scanf("%s", selected);

  // report format
  if (!strcmp(selected, "1")) {
    printf("Enter file name to save: ");
    scanf("%s", filename);
    strncat(filename, csv, 4);
  }
  // any format
  else if (!strcmp(selected, "0")) {
    printf("Enter file name to save(.txt): ");
    scanf("%s", filename);
    strncat(filename, text, 4);
  }
  //wrong option
  else {
    printf("Not an option\n");
    return;
  }

  // open file for write
  FILE *f = fopen(filename, "w");

  if (!strcmp(selected, "0")) {
    // save all the record
    for (int i = 0; i < count; i++) {
      fprintf(f, "Name: %s\n", records->name);
      fprintf(f, "Position: %s\n", records->position);
      fprintf(f, "Age: %d\n", records->age);
      fprintf(f, "Height: %.1f\n", records->height);
      fprintf(f, "Weight: %.1f\n", records->weight);
      fprintf(f, "Year-of-Join: %d\n", records->group_of_year);
      if (i == count - 1) {
        fprintf(f, "Uniform-Number: %d", records->uniform_number);
      }
      else {
        fprintf(f, "Uniform-Number: %d\n\n", records->uniform_number);
      }

      records++;
    }  
  }
  else if (!strcmp(selected, "1")) {
    fprintf(f, "Name,Position,Age,Height,Weight,Year,UniformNumber\n");
    for (int i = 0; i < count; i++) {
      fprintf(f, "%s,%s,%d,%.1f,%.1f,%d", records->name, records->position, records->age, records->height, records->weight, records->group_of_year);
      if (i == count - 1) {
        fprintf(f, ",%d", records->uniform_number);
      }
      else {
        fprintf(f, ",%d\n", records->uniform_number);
      }
      records++;
    }
  }


  printf("Saved Record Successfully\n");
  printf("To Quit, Enter 10 From Option Menu!\n");

  fclose(f);

  return;
}
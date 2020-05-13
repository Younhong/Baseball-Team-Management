#include <stdio.h>
#include <string.h>
#include "base.h"
#include "extras.h"
#include "record.h"

#define MAX_RECORDS 1000

// function prototypes
void input_handler(char user_input[], Record[]);
void display_menu();

// main function
int main(){
  Record records[MAX_RECORDS];
  char user_input[2] = "";
  while(strcmp(user_input, "10")){
    display_menu();
    printf("\nSelect Menu> ");
    scanf("%s", user_input);
    input_handler(user_input, records);
    printf("\n");
  }

	return 0;
}

// Function: input_handler()
// Input: record - array of Records; this may contain empty elements in the middle
// Output: none
// - Handles the user input and invokes functions that correspond to the user input
void input_handler(char user_input[], Record records[]){
  if(!strcmp(user_input, "1"))
    add_record(records);
  else if(!strcmp(user_input, "2"))
    update_record(records);
  else if(!strcmp(user_input, "3"))
    delete_record(records);
  else if(!strcmp(user_input, "4"))
    search_record(records);
  else if(!strcmp(user_input, "5"))
    sort_record(records);
  else if(!strcmp(user_input, "6"))
    defrag_record(records);
  else if(!strcmp(user_input, "7"))
    print_all_records(records);
  else if(!strcmp(user_input, "8"))
    load_record(records);
  else if(!strcmp(user_input, "9"))
    save_record(records);
  else if(!strcmp(user_input, "10"))
    delete_range(records);
  else if(!strcmp(user_input, "11"))
    printf("Terminating... bye!\n"); // Quit
  else
    printf("Unknown menu: %s \n", user_input);

  return;
}

// Function: display_menu()
// Input: none
// Output: none
// - Print out options that user can choose to operate
void display_menu(){
    printf("1. Add New Member\n");
    printf("2. Update Member\n");
    printf("3. Delete Member\n");
    printf("4. Search Member\n");
    printf("5. Sort Member\n");
    printf("6. Defrag Record\n");
    printf("7. Show Member\n");
    printf("8. Load Member\n");
    printf("9. Save Member\n");
    printf("10. Delete users in the scope\n");
    printf("11. Quit\n");
}

#ifndef _RECORD_H_
#define _RECORD_H_

// type defition
// If program gets bigger, you can add player's playing record such as home-run, four balls, strike out, and more.
typedef struct{
  char name[20];
  char position[20];
  int age;
  int height;
  int weight;
  int group_of_year;
  int uniform_number;
} Record;

// Position: catcher, pitcher, designated hitter, first_basement, second_basement, third_basement, shortstop, left_fielder, right_fielder, center_fielder, coach, trainer
#endif
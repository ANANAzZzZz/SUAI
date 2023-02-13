#include "iostream"

using namespace std;

typedef struct {
  int day;
  int month;
  int year;
} date;

int main () {
  date stDate;
  stDate.day = 1;
  stDate.month = 3;
  stDate.year = 2003;

  char* date[10];

  if (stDate.day < 10) {
    date.insert(0, "0");
    date.insert(1, to_string(friendPerson.dateOfBirth.day));
  } else {
    date.insert(0, to_string(stDate.day));
  }
  date.insert(2, ".");

  if (stDate.month < 10) {
    date.insert(3, "0");
    date.insert(4, to_string(stDate.month));
  } else {
    date.insert(3, to_string(stDate.month));
  }
  date.insert(5, ".");
  date.insert(6, to_string(stDate.year));

  cout << date << " length: " << date.length();

  return 0;
};
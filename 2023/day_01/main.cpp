//main.cpp  ::  01_tribock

/**
Something is wrong with global snow production,
and you've been selected to take a look.
The Elves have even given you a map; on it,
they've used stars to mark the top fifty locations that
are likely to be having problems.

You've been doing this long enough to know
that to restore snow operations,
you need to check all fifty stars by December 25th.

Collect stars by solving puzzles.
Two puzzles will be made available
on each day in the Advent calendar;
the second puzzle is unlocked
when you complete the first.
Each puzzle grants one star. Good luck!

You try to ask why they can't just use a weather machine
("not powerful enough") and where they're even sending you ("the sky")
and why your map looks mostly blank ("you sure ask a lot of questions")
and hang on did you just say the sky
("of course, where do you think snow comes from")
when you realize that the Elves
are already loading you into a trebuchet
("please hold still, we need to strap you in").

As they're making the final adjustments,
they discover that their calibration document (your puzzle input)
has been amended(korrigiert) by a very young Elf
who was apparently just excited to show off her art skills.
Consequently, the Elves are having trouble reading the values on the document.

The newly-improved calibration document consists of lines of text;
each line originally contained a specific calibration value
that the Elves now need to recover.
On each line, the calibration value can be found
by combining the first digit and the last digit (in that order)
to form a single two-digit number.

For example:

1abc2
pqr3stu8vwx
a1b2c3d4e5f
treb7uchet

In this example, the calibration values of these four lines
are 12, 38, 15, and 77.
Adding these together produces 142.

Consider your entire calibration document.
What is the sum of all of the calibration values?

kurz:
Es gilt die Quelldatei zu laden.
In jeder Zeile aus dem 1. und letztem Zeichen der Zeile, die eine Ziffer sind, eine Nummer bilden.
und alle so gebildeten Ziffern zu summieren und diese Summe zurückzugeben.

--- Part Two ---

Your calculation isn't quite right.
It looks like some of the digits are actually spelled out with letters:
one, two, three, four, five, six, seven, eight, and nine also count as valid "digits".

Equipped with this new information,
you now need to find the real first and last digit on each line.
For example:

two1nine
eightwothree
abcone2threexyz
xtwone3four
4nineeightseven2
zoneight234
7pqrstsixteen

In this example, the calibration values are 29, 83, 13, 24, 42, 14, and 76. Adding these together produces 281.

What is the sum of all of the calibration values?

part 2 kurz:
Die Wörter one, two, three, four, five, six, seven, eight, und nine zählen ebenfalls als Ziffer.
Wie lautet dann die Summe

*/


#include <iostream>
#include <fstream>
#include <string>
#include <map> // part2

unsigned int num_of_first_last_digit(const std::string&);
void set_digits(std::string&); //part2


int main(int argc, char* argv[]){

  std::ifstream input("res/01_input.txt");
  std::string line;
  unsigned int sum{};
  unsigned int sum2{};
  while(input.good()){
    std::getline(input,line);
    if (line.size()) {
      sum += num_of_first_last_digit(line);
      // part2
      set_digits(line);
      sum2 += num_of_first_last_digit(line);
    }
  }

  std::cout << "2023 Day 01 part 1 : " << sum << std::endl;
  std::cout << "2023 Day 01 part 2 : " << sum2 << std::endl;
  // 2023 Day 01 part 1 : 55002
  // 2023 Day 01 part 2 : 55093
  
  return 0;
}

bool is_not_digit(char c){
  return c < '0' || c > '9'; 
}

unsigned int num_of_first_last_digit(const std::string& s){
  unsigned int result{};
  unsigned int position{};

  while( position < s.size() && is_not_digit( s[position] ) ) ++position;
  if (position < s.size()) {
    result += (s[position] - '0') * 10;
    position = s.size() - 1;
    while( position  && is_not_digit(s[position])) --position;
    result += (s[position]-'0');
  } else
    std::cout << "In " << s << " is no digit" << std::endl;

  return result;
}

// part 2
void set_digits(std::string& s){
  const std::map<std::string,char> s_digits{
    {"one",'1'},
    {"two",'2'},
    {"three",'3'},
    {"four",'4'},
    {"five",'5'},
    {"six",'6'},
    {"seven",'7'},
    {"eight",'8'},
    {"nine",'9'}
  };
  
  unsigned long first_position{std::string::npos};
  unsigned long last_position{};
  char first,last;
  for(auto digit : s_digits){
    unsigned long found_at{};
    if( (found_at = s.find(digit.first) ) != std::string::npos ){
      
      if(found_at<first_position){
	first_position = found_at;
	first   = digit.second;
      } 

      found_at = s.rfind(digit.first);
      if(found_at>last_position){
	last_position = found_at;
	last   = digit.second;
      }
      
    } // if there is a digitname
      
  }// end for all digitnames

  if(first_position != std::string::npos){
    s[first_position] = first;
    if(last_position != first_position)
      s[last_position] = last; 
  }
  
}

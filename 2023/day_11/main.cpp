//main.cpp  ::  11
/**
   --- Day 11: Cosmic Expansion ---

You continue following signs
for "Hot Springs" and eventually
come across an observatory.
The Elf within turns out to
be a researcher studying cosmic expansion
using the giant telescope here.

He doesn't know anything about the missing machine parts;
he's only visiting for this research project.
However, he confirms that the hot springs
are the next-closest area likely to have people;
he'll even take you straight there
once he's done with today's observation analysis.

Maybe you can help him with the analysis to speed things up?

The researcher has collected a bunch of data
and compiled the data into a single giant image (your puzzle input).
The image includes empty space (.) and galaxies (#).
For example:

...#......
.......#..
#.........
..........
......#...
.#........
.........#
..........
.......#..
#...#.....

The researcher is trying to figure out
the sum of the lengths
of the shortest path
between every pair of galaxies.
However, there's a catch:
the universe expanded in the time
it took the light from those galaxies
to reach the observatory.

Due to something involving gravitational effects,
only some space expands.
In fact, the result is that any rows or columns
that contain no galaxies should all actually be twice as big.

In the above example,
three columns and two rows
contain no galaxies:

   v  v  v
 ...#......
 .......#..
 #.........
>..........<
 ......#...
 .#........
 .........#
>..........<
 .......#..
 #...#.....
   ^  ^  ^

These rows and columns need to be twice as big;
the result of cosmic expansion therefore looks like this:

....#........
.........#...
#............
.............
.............
........#....
.#...........
............#
.............
.............
.........#...
#....#.......

Equipped with this expanded universe,
the shortest path between
every pair of galaxies can be found.
It can help to assign every galaxy a unique number:

....1........
.........2...
3............
.............
.............
........4....
.5...........
............6
.............
.............
.........7...
8....9.......

In these 9 galaxies,
there are 36 pairs.
Only count each pair once;
order within the pair doesn't matter.

For each pair,
find any shortest path between the two galaxies
using only steps that
move up, down, left, or right exactly one . or # at a time.
(The shortest path between two galaxies
is allowed to pass through another galaxy.)

For example,
here is one of the shortest paths
between galaxies 5 and 9:

....1........
.........2...
3............
.............
.............
........4....
.5...........
.##.........6
..##.........
...##........
....##...7...
8....9.......

This path has length 9 because
it takes a minimum of nine steps
to get from galaxy 5 to galaxy 9
(the eight locations marked # plus the step onto galaxy 9 itself).
Here are some other example shortest path lengths:

    Between galaxy 1 and galaxy 7: 15
    Between galaxy 3 and galaxy 6: 17
    Between galaxy 8 and galaxy 9: 5

In this example,
after expanding the universe,
the sum of the shortest path between
all 36 pairs of galaxies is 374.

Expand the universe,
then find the length of the shortest
path between every pair of galaxies.
What is the sum of these lengths?

--- Part Two ---

The galaxies are much older
(and thus much farther apart)
than the researcher initially estimated.

Now, instead of the expansion
you did before,
make each empty row or column one million times larger.
That is, each empty row should be replaced
with 1000000 empty rows,
and each empty column should be replaced
with 1000000 empty columns.

(In the example above,
if each empty row or column
were merely 10 times larger,
the sum of the shortest paths
between every pair of galaxies
would be 1030.
If each empty row or column
were merely 100 times larger,
the sum of the shortest paths
between every pair of galaxies
would be 8410.

However, your universe will need to expand far beyond these values.)

Starting with the same initial image,
expand the universe according to these new rules,
then find the length of the shortest path between
every pair of galaxies.
What is the sum of these lengths?


 */


#include <iostream>
#include <fstream>
#include <vector>
#include <set>

int main(int argc, char* argv[]){

  //std::ifstream input("res/11_example.txt");
  std::ifstream input("res/11_input.txt");
  std::vector<std::string> puzzle;
  std::set<unsigned long> columns_with_galaxy;
  if(!input.good()) std::cerr << "Can't read the file" << std::endl;
  while(input.good()){
    std::string line;
    std::getline(input, line);
    if(line.size()){
      unsigned long galaxy_position{};
      bool has_galaxy = false;
      while( ( galaxy_position = line.find('#', galaxy_position) ) != std::string::npos){
	columns_with_galaxy.insert(galaxy_position++);
	has_galaxy = true;
      }
      
      if(!has_galaxy) puzzle.push_back(std::string( line.size(),'X'));
      else puzzle.push_back(line);
    }// end no empty line
  }// end for each line;
  input.close();

  for(std::string& s : puzzle ){
    std::string expanded_line;
    for(unsigned int col = 0; col < s.size();++col){
      if(columns_with_galaxy.count(col)){
	expanded_line += s[col];
      }// end if columns with galaxy
      else{
	expanded_line += "X";
      }
    }//for all colums in universe
    s = expanded_line;
  } // expand each line in puzzle

  struct Position{
    unsigned long row{};
    unsigned long col{};
  };
  
  std::vector<Position> rauten;
  for (unsigned long row=0;row<puzzle.size();++row) 
    for(unsigned int col=0;col<puzzle[row].size();++col)
      if(puzzle[row][col] == '#') rauten.push_back({row,col});

  unsigned long long sum_path_length_part1{};
  unsigned long long sum_path_length_part2{};
  for(unsigned long i=0;i<rauten.size();++i){
    for (unsigned long j = i + 1; j < rauten.size(); ++j) {
      // get the max and mins
      long max_col
	= rauten[i].col > rauten[j].col ? rauten[i].col
	:rauten[j].col;
      long max_row
	= rauten[i].row > rauten[j].row ? rauten[i].row
	:rauten[j].row;
      long min_col
	= rauten[i].col < rauten[j].col ? rauten[i].col
	:rauten[j].col;
      long min_row
	= rauten[i].row < rauten[j].row ? rauten[i].row
	:rauten[j].row;
      //count expands between columns
      unsigned long expand_count{};
      for(unsigned long c=min_col+1; c < max_col;++c){
	if(puzzle[min_row][c] == 'X') ++expand_count;
      }
      // and rows
      for(unsigned long r=min_row+1; r < max_row;++r){
	if(puzzle[r][min_col] == 'X') ++expand_count;
      }

      long col_diff = max_col - min_col;
      long row_diff = max_row - min_row;

      sum_path_length_part1
	+= col_diff
	+ row_diff
	+ expand_count*2
	-expand_count;
      
      sum_path_length_part2
	+= col_diff
	+ row_diff
	+ expand_count*1000000
	- expand_count;
    }
  }

  std::cout << "part1: " << sum_path_length_part1 << std::endl;
  std::cout << "part2: " << sum_path_length_part2 << std::endl;
  
  return 0;
}

//main.cpp  ::  10
/**
   --- Day 10: Pipe Maze ---

You use the hang glider to ride the hot air from Desert Island
all the way up to the floating metal island.
This island is surprisingly cold
and there definitely aren't any thermals to glide on,
so you leave your hang glider behind.

You wander around for a while,
but you don't find any people or animals.
However, you do occasionally find signposts
labeled "Hot Springs" pointing in a seemingly consistent direction;
maybe you can find someone
at the hot springs and ask them
where the desert-machine parts are made.

The landscape here is alien;
even the flowers and trees are made of metal.
As you stop to admire some metal grass,
you notice something metallic scurry away
in your peripheral vision and jump into a big pipe!
It didn't look like any animal you've ever seen;
if you want a better look, you'll need to get ahead of it.

Scanning the area,
you discover that the entire field you're standing on
is densely packed with pipes;
it was hard to tell at first
because they're the same metallic silver color as the "ground".
You make a quick sketch of all of the surface pipes
you can see (your puzzle input).

The pipes are arranged in a two-dimensional grid of tiles:

    | is a vertical pipe connecting north and south.
    - is a horizontal pipe connecting east and west.
    L is a 90-degree bend connecting north and east.
    J is a 90-degree bend connecting north and west.
    7 is a 90-degree bend connecting south and west.
    F is a 90-degree bend connecting south and east.
    . is ground; there is no pipe in this tile.
    S is the starting position of the animal;
    there is a pipe on this tile,
    but your sketch doesn't show what shape the pipe has.

Based on the acoustics of the animal's scurrying,
you're confident the pipe that contains
the animal is one large, continuous loop.

For example, here is a square loop of pipe:

.....
.F-7.
.|.|.
.L-J.
.....

If the animal had entered this loop in the northwest corner,
the sketch would instead look like this:

.....
.S-7.
.|.|.
.L-J.
.....

In the above diagram, the S tile is still a 90-degree F bend:
you can tell because of how the adjacent pipes connect to it.

Unfortunately, there are also many pipes that aren't connected to the loop!
This sketch shows the same loop as above:

-L|F7
7S-7|
L|7||
-L-J|
L|-JF

In the above diagram,
you can still figure out
which pipes form the main loop:
they're the ones connected to S,
pipes those pipes connect to,
pipes those pipes connect to,
and so on.
Every pipe in the main loop connects to its two neighbors
(including S, which will have
exactly two pipes connecting to it,
and which is assumed to connect back to those two pipes).

Here is a sketch that contains
a slightly more complex main loop:

..F7.
.FJ|.
SJ.L7
|F--J
LJ...

Here's the same example sketch with the extra,
non-main-loop pipe tiles also shown:

7-F7-
.FJ|7
SJLL7
|F--J
LJ.LJ

If you want to get out ahead of the animal,
you should find the tile in the loop
that is farthest from the starting position.
Because the animal is in the pipe,
it doesn't make sense to measure this by direct distance.
Instead, you need to find the tile
that would take the longest number of steps
along the loop to reach from the starting point
- regardless of which way around the loop the animal went.

In the first example with the square loop:

.....
.S-7.
.|.|.
.L-J.
.....

You can count the distance
each tile in the loop is
from the starting point like this:

.....
.012.
.1.3.
.234.
.....

In this example,
the farthest point from the start is 4 steps away.

Here's the more complex loop again:

..F7.
.FJ|.
SJ.L7
|F--J
LJ...

Here are the distances for each tile on that loop:

..45.
.236.
01.78
14567
23...

Find the single giant loop starting at S.
How many steps along the loop does it take
to get from the starting position
to the point farthest from the starting position?

--- Part Two ---

You quickly reach the farthest point of the loop,
but the animal never emerges.
Maybe its nest is within the area enclosed by the loop?

To determine whether it's even worth
taking the time to search for such a nest,
you should calculate how many tiles are contained within the loop.
For example:

...........
.S-------7.
.|F-----7|.
.||.....||.
.||.....||.
.|L-7.F-J|.
.|..|.|..|.
.L--J.L--J.
...........

The above loop encloses merely four tiles
- the two pairs of .
in the southwest and southeast (marked I below).
The middle . tiles (marked O below) are not in the loop.
Here is the same loop again with those regions marked:

...........
.S-------7.
.|F-----7|.
.||OOOOO||.
.||OOOOO||.
.|L-7OF-J|.
.|II|O|II|.
.L--JOL--J.
.....O.....

In fact,
there doesn't even need to be a full tile path
to the outside for tiles to count as outside the loop
- squeezing between pipes is also allowed!
Here, I is still within the loop and O is still outside the loop:

..........
.S------7.
.|F----7|.
.||OOOO||.
.||OOOO||.
.|L-7F-J|.
.|II||II|.
.L--JL--J.
..........

In both of the above examples, 4 tiles are enclosed by the loop.

Here's a larger example:

.F----7F7F7F7F-7....
.|F--7||||||||FJ....
.||.FJ||||||||L7....
FJL7L7LJLJ||LJ.L-7..
L--J.L7...LJS7F-7L7.
....F-J..F7FJ|L7L7L7
....L7.F7||L7|.L7L7|
.....|FJLJ|FJ|F7|.LJ
....FJL-7.||.||||...
....L---J.LJ.LJLJ...

The above sketch has many random bits of ground,
some of which are in the loop (I)
and some of which are outside it (O):

OF----7F7F7F7F-7OOOO
O|F--7||||||||FJOOOO
O||OFJ||||||||L7OOOO
FJL7L7LJLJ||LJIL-7OO
L--JOL7IIILJS7F-7L7O
OOOOF-JIIF7FJ|L7L7L7
OOOOL7IF7||L7|IL7L7|
OOOOO|FJLJ|FJ|F7|OLJ
OOOOFJL-7O||O||||OOO
OOOOL---JOLJOLJLJOOO

In this larger example,
8 tiles are enclosed by the loop.

Any tile that isn't part of the main loop
can count as being enclosed by the loop.
Here's another example
with many bits of junk pipe
lying around that aren't connected to the main loop at all:

FF7FSF7F7F7F7F7F---7
L|LJ||||||||||||F--J
FL-7LJLJ||||||LJL-77
F--JF--7||LJLJ7F7FJ-
L---JF-JLJ.||-FJLJJ7
|F|F-JF---7F7-L7L|7|
|FFJF7L7F-JF7|JL---7
7-L-JL7||F7|L7F-7F7|
L.L7LFJ|||||FJL7||LJ
L7JLJL-JLJLJL--JLJ.L

Here are just the tiles
that are enclosed by the loop marked with I:

FF7FSF7F7F7F7F7F---7
L|LJ||||||||||||F--J
FL-7LJLJ||||||LJL-77
F--JF--7||LJLJIF7FJ-
L---JF-JLJIIIIFJLJJ7
|F|F-JF---7IIIL7L|7|
|FFJF7L7F-JF7IIL---7
7-L-JL7||F7|L7F-7F7|
L.L7LFJ|||||FJL7||LJ
L7JLJL-JLJLJL--JLJ.L

In this last example,
10 tiles are enclosed by the loop.

Figure out whether you have time to search
for the nest by calculating the area
within the loop.
How many tiles are enclosed by the loop?

Solution: count all not viseted behind a not even number of edges "|JL"

TODO:
1. clean up
2. Wy the set is not working in function  get_connectors
   (while a Position is allready in the set the count is still 0,
   so i have to test all elements - this works because the elment is in the set,
   so the count have to be 1 but is 0?)
 */


#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>

struct Position{
  unsigned long row,col;
  Position operator+(const Position& o) const {return {row+o.row,col+o.col};}
  Position operator-(const Position& o) const {return {row-o.row,col-o.col};}
  bool operator==(const Position& o) const{return row==o.row && col == o.col;}
  bool operator!=(const Position& o) const{return !(*this == o);}
  bool operator<(const Position& o) const{return row<o.row?true:col<o.col;}
};

std::vector<Position> get_connectors(
    const std::vector<std::string>& puzzle,
    const Position current_position,
    const std::set<Position>& last_positions
    );


int main(int argc, char* argv[]){

  std::vector<std::string> puzzle;
  //std::ifstream input("res/10_example.txt");
  std::ifstream input("res/10_input.txt");
  Position start;
 
  unsigned long s_col{};
  while(input.good()){
    std::string line;
    std::getline(input, line);

    if(line.size()){
      puzzle.push_back(line);
      if( ( (s_col = line.find('S')) != std::string::npos) )
	start = { puzzle.size()-1, s_col};
    }// end no empty line
  }// end reading
  input.close();

  
  Position current_position = start;
  unsigned long long max_steps{};
  std::vector<unsigned long> counts{0};
  std::set<Position> last_positions{start};
  std::vector<std::vector<Position>>
    ways{get_connectors(puzzle,start,last_positions)};
  std::vector<std::string> match{puzzle};
  match[start.row][start.col] ='X';
  std::vector<Position> connectors;
  while(ways.size()){
    connectors = ways.back();
    unsigned long steps{counts.back()};
    ways.pop_back();
    counts.pop_back();
    do {
      current_position = connectors.back();

      if (std::string{"|JL"}.find(
	    match[current_position.row][current_position.col])
	  != std::string::npos)
	match[current_position.row][current_position.col] = '#';
      else match[current_position.row][current_position.col] = 'X';

      connectors.pop_back(); 
      if(connectors.size()) {
	ways.push_back(connectors);
	counts.push_back(steps);
      }
      ++steps;
      last_positions.insert(current_position); 
      connectors = get_connectors(puzzle, current_position,last_positions); 
    } while (connectors.size());

    
    if(steps>max_steps) max_steps = steps;
    } // end while ways

    unsigned long enclosed{};
    for (std::string s : match) {
      unsigned int count_raute{};
      for (char c : s) {
        if (c == '#') 
          ++count_raute;
        else if (c !='X' && count_raute % 2) 
          ++enclosed;
      }// end for each char in line
    } // end for each line

    std::cout << "part1: " << (max_steps/2 + max_steps%2)<< std::endl; //6831
    std::cout << "part2: " << enclosed << std::endl; // 305

  return 0;
}

std::vector<Position> get_connectors(
    const std::vector<std::string>& puzzle,
    const Position current_position,
    const std::set<Position>& last_positions
  ){
  std::vector<Position> result;
  const std::string go_north{"|7F"}; 
  const std::string to_north{"|LJS"};// on current_position |LJ           
  const std::string go_east {"-7J"};  
  const std::string to_east {"-LFS"};// -LF == go_west on current_position
  const std::string go_south{"|LJ"};
  const std::string to_south {"|7FS"}; // on current_position  |7F == go_north+'S'
  const std::string go_west {"-LF"}; 
  const std::string to_west {"-7JS"}; // -7JS == go_east+'S' on current_position
  
  Position new_position;

  if( // ^
    current_position.row
    &&
    !last_positions.count(new_position = {current_position.row-1,current_position.col})
    &&
    to_north.find( // on current_position
      puzzle[current_position.row][current_position.col]
      )  != std::string::npos
    &&
    go_north.find( // ^ on position obove
      puzzle[new_position.row][new_position.col])
    != std::string::npos){

    bool sets_are_shit = false;
    for (auto e : last_positions) {
      if (new_position.row == e.row && new_position.col == e.col) {
        sets_are_shit = true;
	break;
      }
    }
    
    if (!sets_are_shit) 
      result.push_back(new_position);


  }

  if( // >
    current_position.col < puzzle[0].size()-1
    &&
    !last_positions.count(new_position = {current_position.row,current_position.col+1})
    &&
    to_east.find( // on current_position
      puzzle[current_position.row][current_position.col]
      ) != std::string::npos
    &&
    go_east.find( // > on position to the right
      puzzle[new_position.row][new_position.col])
     != std::string::npos){

    bool sets_are_shit = false;
    for (auto e : last_positions) {
      if (new_position.row == e.row && new_position.col == e.col) {
        sets_are_shit = true;
	break;
      }
    }
    if (!sets_are_shit) 
      result.push_back(new_position);
  

  }
  
  if( // v
    current_position.row < puzzle.size()-1
    &&
    !last_positions.count(new_position = {current_position.row+1,current_position.col})
    &&
    to_south.find( // on current_position
      puzzle[current_position.row][current_position.col]
      ) != std::string::npos
    &&
    go_south.find( // v on position below
       puzzle[new_position.row][new_position.col])
     != std::string::npos){

    bool sets_are_shit = false;
    for (auto e : last_positions) {
      if (new_position.row == e.row && new_position.col == e.col) {
        sets_are_shit = true;
	break;
      }
    }
    if (!sets_are_shit) 
      result.push_back(new_position);

    
  }

  if( // <
    current_position.col
    &&
    !last_positions.count(new_position = {current_position.row,current_position.col-1})
    &&
    to_west.find( // on current_position
      puzzle[current_position.row][current_position.col]
      ) != std::string::npos
    &&
    go_west.find( // < on position to the left
       puzzle[new_position.row][new_position.col])
     != std::string::npos){

    bool sets_are_shit = false;
    for (auto e : last_positions) {
      if (new_position.row == e.row && new_position.col == e.col) {
        sets_are_shit = true;
	break;
      }
    }
    if (!sets_are_shit) 
      result.push_back(new_position);

  }

  return result;
}

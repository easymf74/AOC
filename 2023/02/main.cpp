//main.cpp  ::  02
/**
   --- Day 2: Cube Conundrum ---

You're launched high into the atmosphere!
The apex of your trajectory (Flugbahn)
just barely reaches the surface
of a large island floating in the sky.
You gently land in a fluffy |pile of leaves|(Blätterdach).
It's quite cold, but you don't see much snow.
An Elf runs over to greet you.

The Elf explains that you've arrived
at Snow Island and apologizes for the lack of snow.
He'll be happy to explain the situation,
but it's a bit of a walk, so you have some time.
They don't get many visitors up here;
would you like to play a game in the meantime?

As you walk, the Elf shows you
a small bag and some cubes
which are either red, green, or blue.
Each time you play this game,
he will hide a secret number of cubes of each color in the bag,
and your goal is to figure out information about the number of cubes.

To get information,
once a bag has been loaded with cubes,
the Elf will reach into the bag,
grab a handful of random cubes,
show them to you, and then put them back in the bag.
He'll do this a few times per game.

You play several games and
record the information from each game (your puzzle input).
Each game is listed with its ID number (like the 11 in Game 11: ...)
followed by a semicolon-separated list
of subsets of cubes that were revealed(aufgedeckt)
from the bag (like 3 red, 5 green, 4 blue).

For example, the record of a few games might look like this:

Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue
Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red
Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red
Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green

In game 1,
three sets of cubes are revealed from the bag
(and then put back again).
The first set is 3 blue cubes and 4 red cubes;
the second set is 1 red cube, 2 green cubes, and 6 blue cubes;
the third set is only 2 green cubes.

The Elf would first like to know
which games would have been possible
if the bag contained only 12 red cubes, 13 green cubes, and 14 blue cubes?

In the example above,
games 1, 2, and 5 would have been possible
if the bag had been loaded with that configuration.
However, game 3 would have been impossible
because at one point the Elf showed you 20 red cubes at once;
similarly, game 4 would also have been impossible
because the Elf showed you 15 blue cubes at once.
If you add up the IDs of the games that would have been possible,
you get 8.

Determine which games would have been possible
if the bag had been loaded with only
12 red cubes,
13 green cubes, and
14 blue cubes.
What is the sum of the IDs of those games?

Kurz:
Jede zeile enthält eine ID, danach Mengen von Farben
Wir suchen die Summe der ID's, bei denen in der Menge der Farben,
die Menge von 12 red, 13 green, 14 blue nicht überschritten wird.

--- Part Two ---

The Elf says they've stopped producing snow
because they aren't getting any water!
He isn't sure why the water stopped;
however, he can show you how to get to the water source
to check it out for yourself. It's just up ahead!

As you continue your walk,
the Elf poses a second question:
in each game you played,
what is the fewest number of cubes of each color
that could have been in the bag to make the game possible?

Again consider the example games from earlier:

Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue
Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red
Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red
Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green

    In game 1,
    the game could have been played with as few as 4 red, 2 green, and 6 blue cubes.
    If any color had even one fewer cube, the game would have been impossible.
    Game 2 could have been played with a minimum of 1 red, 3 green, and 4 blue cubes.
    Game 3 must have been played with at least 20 red, 13 green, and 6 blue cubes.
    Game 4 required at least 14 red, 3 green, and 15 blue cubes.
    Game 5 needed no fewer than 6 red, 3 green, and 2 blue cubes in the bag.

The power of a set of cubes is equal to
the numbers of red, green, and blue cubes multiplied together.
The power of the minimum set of cubes in game 1 is 48.
In games 2-5 it was 12, 1560, 630, and 36, respectively. Adding up these five powers produces the sum 2286.

For each game, find the minimum set of cubes that must have been present. What is the sum of the power of these sets?

kurz:
Für alle Zeilen das Produkt der maximalen Menge je Farbe herausfinden
gesucht wird die Summe der Produkte aus allen Zeilen.

 */

#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <vector>

int main(int argc, char* argv[]){

  std::ifstream input("res/02_input.txt");
  //std::ifstream input("res/02_example.txt");
  std::regex game     ("(\\d+):");
  std::regex red      ("(\\d+) r");
  std::regex green    ("(\\d+) g");
  std::regex blue     ("(\\d+) b");
  std::smatch match;
  std::vector<unsigned int> limits{12 , 13   , 14};
  std::vector<std::regex>   colors{red, green, blue};
  unsigned long id_sum{};
  //part2
  std::vector<unsigned int> max_amounts{0,0,0};
  unsigned long product_sum{};
  
  while(input.good()){
    std::string line;
    std::getline(input,line);
    if(line.size()){
      bool possible=true;
      for(unsigned int i=0;i<3;++i){
	std::string search_in = line;
	unsigned int amount;

        while (std::regex_search(search_in, match, colors[i])) {
	  if( (amount = std::stoi(match[1]) ) > limits[i] ) possible=false;
	  if( amount > max_amounts[i] ) max_amounts[i] = amount; //part2
          search_in = match.suffix().str();
        } // end while ther are more matches
      }// end for all colours
      
      if(possible){
	if(std::regex_search(line, match, game))
	  id_sum += std::stoi(match[1]);
	else
	  std::cout << "No Game-ID in line " << line << std::endl;
      }

      // part2
      unsigned long product_of_min_amouts{1};
      for (unsigned int amount : max_amounts) product_of_min_amouts *= amount;
      max_amounts = {0,0,0};
      product_sum += product_of_min_amouts;
      
    } // end if line is not empty
  } // end reading input

  std::cout << "part1: " << id_sum << std::endl; //2268
  std::cout << "part2: " << product_sum << std::endl; //63542
  
  return 0;
}

//main.cpp  ::  05
/**
   --- Day 5: If You Give A Seed A Fertilizer ---

You take the boat
and find the gardener
right where you were told he would be:
managing a giant "garden" that looks more to you like a farm.

"A water source? Island Island is the water source!"
You point out that Snow Island isn't receiving any water.

"Oh, we had to stop the water
because we ran out of sand to filter it with!
Can't make snow with dirty water.
Don't worry, I'm sure we'll get more sand soon;
we only turned off the water a few days...
weeks... oh no."
His face sinks into a look of horrified realization.

"I've been so busy making sure everyone here has food
that I completely forgot to check why we stopped getting more sand!
There's a ferry leaving soon that is headed over in that direction
- it's much faster than your boat. Could you please go check it out?"

You barely have time to agree to this request
when he brings up another.
"While you wait for the ferry,
maybe you can help us with our food production problem.
The latest Island Island Almanac just arrived
and we're having trouble making sense of it."

The almanac (Kalender) (your puzzle input)
lists all of the seeds that need to be planted.
It also lists what type of soil (Boden)
to use with each kind of seed,
what type of fertilizer (Dügger) to use with each kind of soil,
what type of water to use with each kind of fertilizer, and so on.
Every type of seed, soil, fertilizer and so on is identified with a number,
but numbers are reused by each category - that is,
soil 123 and fertilizer 123 aren't necessarily related to each other.

For example:

seeds: 79 14 55 13

seed-to-soil map:
50 98 2
52 50 48

soil-to-fertilizer map:
0 15 37
37 52 2
39 0 15

fertilizer-to-water map:
49 53 8
0 11 42
42 0 7
57 7 4

water-to-light map:
88 18 7
18 25 70

light-to-temperature map:
45 77 23
81 45 19
68 64 13

temperature-to-humidity map:
0 69 1
1 0 69

humidity-to-location map:
60 56 37
56 93 4

The almanac starts by
listing which seeds need to be planted: seeds 79, 14, 55, and 13.

The rest of the almanac contains a list of maps
which describe how to convert numbers from a source category into numbers
in a destination category.
That is,
the section that starts with seed-to-soil map:
describes how to convert a seed number (the source)
to a soil number (the destination).
This lets the gardener and his team know
which soil to use with which seeds,
which water to use with which fertilizer,
and so on.

Rather than list every source number
and its corresponding destination number one by one,
the maps describe entire ranges of numbers
that can be converted.
Each line within a map contains three numbers:
the destination range start,
the source range start,
and the range length.

Consider again the example seed-to-soil map:

50 98 2
52 50 48

The first line has a destination range start of 50,
a source range start of 98,
and a range length of 2.
This line means that the source range starts at 98
and contains two values: 98 and 99.
The destination range is the same length,
but it starts at 50, so its two values are 50 and 51.
With this information, you know that
seed number 98 corresponds to soil number 50
and that seed number 99 corresponds to soil number 51.

The second line means
that the source range starts at 50
and contains 48 values: 50, 51, ..., 96, 97.
This corresponds to a destination range starting at 52
and also containing 48 values: 52, 53, ..., 98, 99.
So, seed number 53 corresponds to soil number 55.

Any source numbers that aren't mapped
correspond to the same destination number.
So, seed number 10 corresponds to soil number 10.

So, the entire list of seed numbers and their corresponding soil numbers looks like this:

seed  soil
0     0
1     1
...   ...
48    48
49    49
50    52
51    53
...   ...
96    98
97    99
98    50
99    51

With this map, you can look up the soil number required for each initial seed number:

    Seed number 79 corresponds to soil number 81.
    Seed number 14 corresponds to soil number 14.
    Seed number 55 corresponds to soil number 57.
    Seed number 13 corresponds to soil number 13.

The gardener and his team want to get started as soon as possible,
so they'd like to know the closest location that needs a seed.
Using these maps, find the lowest location number that corresponds to any of the initial seeds.
To do this, you'll need to convert each seed number
through other categories
until you can find its corresponding location number.
In this example, the corresponding types are:

    Seed 79, soil 81, fertilizer 81, water 81, light 74, temperature 78, humidity 78, location 82.
    Seed 14, soil 14, fertilizer 53, water 49, light 42, temperature 42, humidity 43, location 43.
    Seed 55, soil 57, fertilizer 57, water 53, light 46, temperature 82, humidity 82, location 86.
    Seed 13, soil 13, fertilizer 52, water 41, light 34, temperature 34, humidity 35, location 35.

So, the lowest location number in this example is 35.

What is the lowest location number that corresponds to any of the initial seed numbers?

--- Part Two ---

Everyone will starve
if you only plant such a small number of seeds.
Re-reading the almanac, it looks like the seeds:
line actually describes ranges of seed numbers.

The values on the initial seeds:
line come in pairs.
Within each pair,
the first value is the start of the range
and the second value is the length of the range.
So, in the first line of the example above:

seeds: 79 14 55 13

This line describes two ranges of seed numbers to be planted in the garden.
The first range starts with seed number 79 and contains 14 values:
79, 80, ..., 91, 92.
The second range starts with seed number 55 and contains 13 values:
55, 56, ..., 66, 67.

Now, rather than considering four seed numbers,
you need to consider a total of 27 seed numbers.

In the above example,
the lowest location number can be obtained from seed number 82,
which corresponds to soil 84,
fertilizer 84,
water 84,
light 77,
temperature 45,
humidity 46, and
location 46.
So, the lowest location number is 46.

Consider all of the initial seed numbers
listed in the ranges on the first line of the almanac.
What is the lowest location number that corresponds to any of the initial seed numbers?

 */

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <deque>
#include <set>

class Range{
public:
  unsigned long long get_min()const{return min;}
  unsigned long long get_max()const{return max;}
  Range(
    unsigned long long min,
    unsigned long long max
    ):min{min},max{max}{}

  Range operator+=(unsigned long long i){
    min+=i;
    max+=i;
    return *this;
  }
  
  bool operator<(const Range& o)const{return min<o.min;}

  operator bool()const{return !(min==0 && max==0);}

  /**
     tests the interception of the range with the given range
     returns a vector of ranges, wereas the first Element is the interception
     if there is no interception the first Element is {0,0}
     the followed Elements are the the Ranges without Interception,
     but only for this Range not for the given:
     Examples:
     1-5[3-8]    -> [3-5] [1-2] 
     3-8[1-5]    -> [3-5] [6-8]
     5-20[12-15] -> [12-15] [5-11] [16-20]
     12-15[5-20] -> [12-15]
     5-8[12-15]  -> [0-0][5-8]
     12-15[5-8]  -> [0-0][12-15]
   */
  std::vector<Range> operator[](const Range& r) const {
    std::vector<Range> result;
    
    unsigned long long max_min = min > r.min ? min : r.min;
    unsigned long long min_max = max < r.max ? max : r.max;
    if(max < r.min || min > r.max)
      result = { {0,0}, {min,max} };
    else {
      result.push_back({max_min,min_max});
      if(min<r.min)
	result.push_back({min,r.min-1});
      if(max > r.max)
	result.push_back({r.max+1,max});
    }

    return result;
  }
  
  friend
  std::ostream& operator<<(std::ostream& o,const Range& r){
    o << "[ " << r.min << "-" << r.max << " ]";
    return o;
  }
  
private:
  unsigned long long  min;
  unsigned long long  max;
  
};

using vvl = std::vector<std::vector<unsigned long long>>; 
unsigned long long dest(unsigned int src,const vvl& rules);
std::vector<Range> r_dest(const Range& src_rg, const vvl& rules);
			  
int main(int argc, char* argv[]){
  unsigned long long part1{};
  //std::ifstream input("res/05_example.txt");
  std::ifstream input("res/05_input.txt");
  vvl seed_soil;
  vvl soil_fertilizer;
  vvl fertilizer_water;
  vvl water_light;
  vvl light_temperature;
  vvl temperature_humidity;
  vvl humidity_location;
  std::vector<unsigned int> seeds;
  std::vector<vvl*> maps{
    nullptr,
    &seed_soil,
    &soil_fertilizer,
    &fertilizer_water,
    &water_light,
    &light_temperature,
    &temperature_humidity,
    &humidity_location
  };
  
  std::string line;
  unsigned int map_part{};
  while(input.good()){
    std::getline(input, line);
    if(line.size()){
      if(map_part){
	char first = line[0];
	if(first>='0' && first<='9'){
	  std::string num;
	  std::vector<unsigned long long> nums;
	  for(char c : line){
	    if(c==' '){
	      nums.push_back(std::stoull(num));
	      num.clear();
	    }else num += c;
	  } // end for each char in line
	  if(num.size()) nums.push_back(std::stoull(num));
	  
	  // create map
	  maps[map_part]->push_back(nums);
	}
      }else{
	//seeds
	std::string num;
	line = line.substr(7);
	for(char c : line){
	  if(c == ' '){
	    seeds.push_back(std::stoull(num));
	    num.clear();
	  }else num+=c;
	}// end for each char in line
	if(num.size()) seeds.push_back(std::stoull(num));
      }
    }else ++map_part;
    
  }
  input.close();

  for(unsigned long long seed : seeds){
    std::vector<unsigned long long> ln{seed};

    for(unsigned i=1; i<maps.size();++i){
      ln.push_back( dest(ln.back(),*maps[i]));
    }

    if(!part1) part1 = ln.back();
    else if(ln.back() < part1) part1 = ln.back();
      
    ln.clear();
    
  } // end for all seeds
  
  // part 2
  std::vector<Range> rgs;
  std::set<Range> end_rgs;
  for(unsigned int i=0; i<seeds.size();i+=2){
    Range seed{seeds[i], seeds[i] + seeds[i + 1] - 1};
    rgs = r_dest(seed, *maps[1]);
    
    for (unsigned int n = 2; n < maps.size(); ++n) {
      std::vector<Range> n_rgs; 
      for(Range r : rgs){
	std::vector<Range> got_n_rgs;
	got_n_rgs = r_dest(r, *maps[n]);
	for(Range nr : got_n_rgs) n_rgs.push_back(nr);
      } //for all Ranges
      rgs = n_rgs;
    } // for all maps
    
    for(Range r : rgs) end_rgs.insert(r);
  }//end for all seeds

  unsigned long part2 = end_rgs.begin()->get_min();
  
  std::cout <<"part1: " << part1 << std::endl; // 486613012
  std::cout <<"part2: " << part2 << std::endl; // 56931769

  return 0;
}


unsigned long long dest(unsigned int src,const vvl& rules){
  unsigned long long dest{src};
  for(unsigned int i=0; i<rules.size() && dest ==src; ++i){
    unsigned long from = rules[i][1];
    unsigned long to   = from + rules[i][2];
    if( src>=from && src < to)
      dest = src - from  + rules[i][0]; 
  }

  return dest;
}

std::vector<Range> r_dest(const Range& src_rg, const vvl& rules){
  std::vector<Range> result;
  std::deque<Range> worker{src_rg};
  
  while(worker.size()){
    Range work = worker.front();
    worker.pop_front();
    
    for(unsigned int i=0; i<rules.size(); ++i){
      Range rule {rules[i][1],rules[i][1]+rules[i][2]-1};
    
      std::vector<Range> match = work[rule];

      if (match[0]) {
        long long condition = rules[i][0] - rules[i][1];
        match[0] += condition;
        result.push_back(match[0]);
	work = {0,0};
	for(unsigned int n=1;n<match.size();++n) worker.push_back(match[n]);
      } // end if there is a match

    } // end for all rules
    if(work) result.push_back(work);
  } // end while there ar Ranges to proof
  
  return result;
}

/**
Ist wirklich eine interessante Aufgabe. Ich hatte die ganzen seeds tatsächlich durchrödeln lassen - nach weniger als 1,5 Stunden hatte ich die Lösung.  Deine Lösung verstehe ich tatsächlich nicht.  Wenn ich aber mal Zeit habe, werde ich das Programm dadurch optimieren, dass ich immer ganze Bereiche und nicht einzelne seeds betrachte.  Das dürfte einen gehörigen Geschwindigkeitsschub bringen. Anhand des Beispiels lässt sich das leicht durchspielen:
seeds: 79-92, 55-67
soil: 
98-99 (-48)   keine seeds im Bereich; 
50-97 (+2) 79-92 -> 81-94; 55-67-> 57-69
 fertilizer:
0-14  (+39) keine Treffer
15-51 (-15) keine Treffer
52-53 (-15) keine Treffer
-> 81-94; 57-69
water:
0-6    (+42) keine Treffer
7-10 (+50) keine Treffer
11-52 (-11) keine Treffer
53-60 (-4) 57-60 -> 53-56    || 57-69 |> 57-60 + 61-69
-> 61-69; 81-94
light:
18-24 (+70) keine Treffer
25-94 (-7)  53-56->46-49;  61-69->54-62;   81-94->74-87 
temperature:
45-63 (+36) 46-49->82-85;  54-62->90-98
64-76 ( +4) 74-76->78-80
77-99 (-32) 77-87-> 45-55
humidity:
69-69 (-69) keine treffer
0-68   (+1)  45-55-> 46-56
-> 78-80; 82-85;  90-98
location:
56-92 (+4) 56-56 -> 60-60;  78-80->82-84;  82-85->86-89; 90-92->94-96
93-96 (-36) 93-96-> 57-60
->46-55;97-98
So das am Ende folgende Bereiche bleiben:
46-55;  57-60;  82-84; 86-89; 94-98
Wovon die kleinste Untergrenze der Lösung entspricht.

seeds 79-92 55-67
match: [ 79-92 ]/[ 50-97 ]>>[ 79-92 ] -> [ 81-94 ]
2: [ 81-94 ]>
3: [ 81-94 ]>
match: [ 81-94 ]/[ 25-94 ]>>[ 81-94 ] -> [ 74-87 ]
4: [ 74-87 ]>
match: [ 74-87 ]/[ 77-99 ]>>[ 77-87 ] -> [ 45-55 ]
match: [ 74-76 ]/[ 64-76 ]>>[ 74-76 ] -> [ 78-80 ]
5: [ 45-55 ]>[ 78-80 ]>
match: [ 45-55 ]/[ 0-68 ]>>[ 45-55 ] -> [ 46-56 ]
6: [ 46-56 ]>[ 78-80 ]>
match: [ 46-56 ]/[ 56-92 ]>>[ 56-56 ] -> [ 60-60 ]
match: [ 78-80 ]/[ 56-92 ]>>[ 78-80 ] -> [ 82-84 ]
7: [ 60-60 ]>[ 46-55 ]>[ 82-84 ]>
match: [ 55-67 ]/[ 50-97 ]>>[ 55-67 ] -> [ 57-69 ]
2: [ 57-69 ]>
match: [ 57-69 ]/[ 53-60 ]>>[ 57-60 ] -> [ 53-56 ]
3: [ 53-56 ]>[ 61-69 ]>
match: [ 53-56 ]/[ 25-94 ]>>[ 53-56 ] -> [ 46-49 ]
match: [ 61-69 ]/[ 25-94 ]>>[ 61-69 ] -> [ 54-62 ]
4: [ 46-49 ]>[ 54-62 ]>
match: [ 46-49 ]/[ 45-63 ]>>[ 46-49 ] -> [ 82-85 ]
match: [ 54-62 ]/[ 45-63 ]>>[ 54-62 ] -> [ 90-98 ]
5: [ 82-85 ]>[ 90-98 ]>
6: [ 82-85 ]>[ 90-98 ]>
match: [ 82-85 ]/[ 56-92 ]>>[ 82-85 ] -> [ 86-89 ]
match: [ 90-98 ]/[ 56-92 ]>>[ 90-92 ] -> [ 94-96 ]
match: [ 93-98 ]/[ 93-96 ]>>[ 93-96 ] -> [ 56-59 ]
7: [ 86-89 ]>[ 94-96 ]>[ 56-59 ]>[ 97-98 ]>
[ 46-55 ]~[ 56-59 ]~[ 60-60 ]~[ 82-84 ]~[ 86-89 ]~[ 94-96 ]~[ 97-98 ]~


 */

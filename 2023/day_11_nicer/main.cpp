//main.cpp  ::  11v2

#include <iostream>
#include <fstream>
#include <vector>
#include <set>

class Position {
public:
  Position(unsigned long x, unsigned long y) : x(x), y(y) {}
  Position& operator+=(const Position& o) {x += o.x; y += o.y; return *this;}
  unsigned long long dist(const Position& o)const{return abs(x-o.x) + abs(y-o.y);}
  unsigned long get_x() const {return x;}
  unsigned long get_y() const {return y;}
private:
  unsigned long x,y;
  unsigned long long abs(long long v) const {return v>0?v:v*-1;}
};

class Universe{
public:
  Universe(std::vector<Position> x):galaxies{x}{}
  Universe expand(unsigned long factor){
    Universe expanded_universe{*this};
    std::set<unsigned long> xs,ys;
    for(Position& g : expanded_universe.galaxies){
      xs.insert(g.get_x());
      ys.insert(g.get_y());
    }
    //expand rows
    for(unsigned long i=*xs.rbegin()-1;i>*xs.begin();--i)
      if(!xs.count(i))
	for(Position& g : expanded_universe.galaxies)
	  if(g.get_x()>i) g+={factor-1,0};

    //expand cols
    for(unsigned long i=*ys.rbegin()-1;i>*ys.begin();--i)
      if(!ys.count(i))
	for(Position& g : expanded_universe.galaxies)
	  if(g.get_y()>i) g+={0,factor-1};
    
    return expanded_universe;
  }
  
  unsigned long long operator()() const {
    unsigned long long sum{};
    for(unsigned int i=0; i<galaxies.size();++i)
      for(unsigned int j=i+1;j<galaxies.size();++j)
	sum += galaxies[i].dist(galaxies[j]);
    return sum;
  }
private:
  std::vector<Position> galaxies;
  
};

int main(int argc, char* argv[]){

  std::ifstream input("res/11_input.txt");
  std::vector<Position> galaxies;
  std::vector<unsigned long> x_exp, y_exp;
  
  if(!input.good()){
    std::cerr << "cant read file" << std::endl;
    return 1;
  }
  
  unsigned long x_pos_galaxy{};
  while(input.good()){
    std::string line;
    std::getline(input, line);
    if(line.size()){
      unsigned long y_pos_galaxy{};
      while( (y_pos_galaxy = line.find('#',y_pos_galaxy) ) != std::string::npos)
	galaxies.push_back({x_pos_galaxy,y_pos_galaxy++});
      ++x_pos_galaxy;
    }// not an empty line
  }// end reading
  input.close();
  
  Universe universe(galaxies);

  std::cout << "part1: " << universe.expand(2)() << std::endl;
  std::cout << "part2: " << universe.expand(1000000)() << std::endl;

  return 0;
}

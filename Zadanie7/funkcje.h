#ifndef _FUNKCJE_H
#define _FUNKCJE_H

#include <utility>
#include <string>
#include <vector>
#include <iostream>
#include <vector>
#include <numeric>
#include <iomanip>
#include <fstream>
#include <random>
#include <functional>
#include <map>
#include <list>
#include <chrono>
#include "funkcje.h"






using Time=std::chrono::time_point <std::chrono::system_clock, std::chrono::duration<double>>;
typedef std::tuple<std::vector<std::vector<int>>, int,int,int> (*FnPtr)(std::vector<int>,int, int, int,Time,bool);



int Quality(std::vector<std::vector<int>> v, int T);
std::tuple<std::vector<std::vector<int>>, int, int, int> random_sampling(std::vector<int>, int, int, int,Time,bool);
std::tuple<std::vector<std::vector<int>>, int, int, int> random_hill_climbing(std::vector<int>, int, int, int,Time,bool);
std::tuple<std::vector<std::vector<int>>, int, int, int> hill_climbing_det(std::vector<int>, int , int, int, Time,bool);
std::vector<std::vector<int>> find_best_neighbours(std::vector<std::vector<int>> ,int, bool);
std::tuple<std::vector<std::vector<int>>, int, int, int> tabu_search(std::vector<int>, int, int, int,Time,bool);
std::tuple<std::vector<std::vector<int>>, int, int, int> simulated_annealing(std::vector<int>, int, int, int,Time,bool);
std::tuple<std::vector<std::vector<int>>, int, int, int> przeglad(std::vector<int>, int, int, int,Time,bool);
std::pair<std::string, std::vector<int>> readFile(std::string);

#endif



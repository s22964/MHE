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

extern std::vector<int> S;

extern bool krzywa,l_celu;
extern int X,lc;
extern std::chrono::time_point <std::chrono::system_clock, std::chrono::duration<double>> czas_start;

typedef std::pair<std::vector<std::vector<int>>, int> (*FnPtr)(int, int, int);

int Quality(std::vector<std::vector<int>> v, int T);
std::pair<std::vector<std::vector<int>>, int> random_sampling(int , int, int);
std::pair<std::vector<std::vector<int>>, int> random_hill_climbing(int , int, int);
std::pair<std::vector<std::vector<int>>, int> hill_climbing_det(int , int , int );
std::vector<std::vector<int>> find_best_neighbours(std::vector<std::vector<int>> ,int );
std::pair<std::vector<std::vector<int>>, int> tabu_search(int, int, int);
std::pair<std::vector<std::vector<int>>, int> przeglad(int, int, int);
std::pair<std::string, std::vector<int>> readFile(std::string);

#endif



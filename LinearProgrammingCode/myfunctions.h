#pragma once

#include "gurobi_c++.h"

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
//#include <stdlib.h>
//#include <time.h>
#include <random>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <ctime>

using namespace std;


extern unordered_map<string, string> datasetfilemap;
extern unordered_map<string, string> PINorPWD;
extern unordered_map<string, int> N_map;
extern unordered_map<string, int> distinct_map;


double binopdf(long x, long n, double p);
// calculate the sum of binopdf(x,n,p) for x1 <= x <= x2
double binocdf(long x1, long x2, long n, double p);

//generate frequency,count pairs for 000webhost and neopets datasets
void generatefrequencycountpairs();
bool static ismorefreqent(const pair<long, long> &a, const pair<long, long> &b) { return a.first > b.first; }
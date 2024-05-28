#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <unordered_map>
#include <unordered_set> 
#include <chrono>
using namespace std;

// This helper file implemented functions that are not used in the "Towards a Rigorous Statistical Analysis of Empirical 
// Password Datasets" paper, but for other projects

struct pwdguess {
	string pwd;
	double guessnum;
	int freq;
};

// generate SamplingLB with data file in bai's format
void experiment_samplingLB3(string dname, string output);
// generate ExtendedLB with data file in bai's format
void experiment_ExtendedLB3(string dname, string output);

//plot the guessing curves using the attack results in bai's format
void experiment_plotguessingcurves3(string dname);


// the same as the ismorefrequent function in main.cpp
bool VectorIntDecreasingOrderComp(const vector<int> &a, const vector<int> &b);
bool StructPwdguessIncreasingOrderCompt(const pwdguess &a, const pwdguess &b);

//monte carlo
void MonteCarloCounterExample();
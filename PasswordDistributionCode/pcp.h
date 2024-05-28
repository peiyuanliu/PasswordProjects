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

void experiment_extractpasswordswithPCPs(string dname);

// manually amend passwords that do not satisfy PCP by appending append_surfix at the end.
void experiment_manuallyAmendpasswordswithPCPs(string dname);

void ExtractSubsetWithPCP(string dname, string daddr, vector<unordered_map<string, int>>& PCP);
bool CheckPCP(string password, vector<unordered_map<string, int>>& PCP);

// manually amend passwords that do not satisfy PCP by appending append_surfix at the end.
void ManuallyAmendPasswordSetToSatisfyPCP(string dname, string daddr, vector<unordered_map<string, int>>& PCP, string append_surfix);
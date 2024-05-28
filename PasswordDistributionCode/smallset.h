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

// This helper file implemented functions that are used in the PIN paper with small datasets 

// Subsample d passwords from raw dataset (each line is a user selected password) and output in forms of {count, plaintext}
void subsample_rawdata_to_pwdfreq(string input_dir, string output_dir, string dname, int d, char delimiter = '\t');

// Convert guessing curves {guessing number, password, guessing curve} from S&P19 paper to guessing numbers {guessing number, password}
void convert_guessing_curve_to_guessing_number(string dir, string dname, char delimiter = '\t');

// Check if the pins/passwords in dname are the top k pin/passwords in the blocklist
// if k = -1, consider the whole blocklist
void checkBlocklist(string blocklist_name, string dname, int k, bool export_to_file=false, string output_path="");

// subsample d password/PIN from raw data (each line is a user selected password/PIN) output in forms of raw data
void subsample_raw_data_to_raw_data(string input_dir, string output_dir, string dname, int d);

// output the distinct number and total number of passwords/PINs in the input dataset (freq count pairs)
vector<int> get_metadata(string input_path);

// Convert (freq, pwd) list to (freq, count) list and (pwd, freq) list
void freqpwd_to_frequencylist(string dname, string input_path, string output_dir);

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

#include "myhelper.h"
#include "pcp.h"
#include "smallset.h"

using namespace std;

unordered_map<string, string> dictfilemap{
	{ "PIN4digit-amitay-dict", "D:/Purdue/Research/Datasets/PIN/amitay/passcodeDataDict.txt" },
};

unordered_map<string, string> datasetfilemap {
	{ "UserStudy_first-choice_4-digit", "D:/Purdue/Research/Datasets/PIN/UserStudy_first-choice_4-digit-Freq.txt"},
	{ "UserStudy_first-choice_4-digit-PINFreq", "D:/Purdue/Research/Datasets/PIN/UserStudy_first-choice_4-digit-PINFreq.txt" },
	{ "PIN4digit-amitay-dp", "D:/Purdue/Research/Datasets/PIN/amitay/passcodeDataDP-epsilon=0.25.txt" },
	{ "PIN4digit-amitay-dp-block1", "D:/Purdue/Research/Datasets/PIN/amitay/passcodeDataDP-epsilon=0.25Block1.txt" },
	{ "PIN4digit-amitay-dp-block27", "D:/Purdue/Research/Datasets/PIN/amitay/passcodeDataDP-epsilon=0.25Block27.txt" },
	{ "PIN4digit-amitay-dp-block100", "D:/Purdue/Research/Datasets/PIN/amitay/passcodeDataDP-epsilon=0.25Block100.txt" },
	{ "PIN4digit-amitay-dp-block1000", "D:/Purdue/Research/Datasets/PIN/amitay/passcodeDataDP-epsilon=0.25Block1000.txt" },
	{ "PIN4digit-amitay-dp-block2740", "D:/Purdue/Research/Datasets/PIN/amitay/passcodeDataDP-epsilon=0.25Block2740.txt" },
	{ "PIN4digit-amitay-dp-block4000", "D:/Purdue/Research/Datasets/PIN/amitay/passcodeDataDP-epsilon=0.25Block4000.txt" },
	{ "linkedin", "D:/Purdue/CS590 PWD/dataset/linkedin_dataset/full.out"},
	{ "yahoo", "D:/Purdue/CS590 PWD/dataset/yahoo_password_frequencies_corpus/yahoo-all.txt"},
	{ "rockyou", "D:/Purdue/CS590 PWD/dataset/rockyouFreq.txt"},
	{ "rockyou-original", "D:/Purdue/CS590 PWD/dataset/rockyou-withcount.txt/rockyou-withcount.txt" },
	{"000webhost", "D:/Purdue/CS590 PWD/dataset/Jeremiah/09_perfect/000webhost_shuf_clean-withcount.txt"},
	{ "neopets", "D:/Purdue/CS590 PWD/dataset/Jeremiah/09_perfect/neopets_shuf_clean-withcount.txt" },
	{ "bfield", "D:/Purdue/CS590 PWD/dataset/Jeremiah/09_perfect/bfield_shuf_clean-withcount.txt" },
	{ "brazzers", "D:/Purdue/CS590 PWD/dataset/Jeremiah/09_perfect/brazzers_shuf_clean-withcount.txt" },
	{ "clixsense", "D:/Purdue/CS590 PWD/dataset/Jeremiah/09_perfect/clixsense_shuf_clean-withcount.txt" },
	{ "csdn", "D:/Purdue/CS590 PWD/dataset/Jeremiah/09_perfect/csdn_shuf_clean-withcount.txt" },
	{ "000webhost-freq", "D:/Purdue/CS590 PWD/dataset/000webhostFreq.txt" },
	{ "neopets-freq", "D:/Purdue/CS590 PWD/dataset/neopetsFreq.txt" },
	{ "bfield-freq", "D:/Purdue/CS590 PWD/dataset/bfieldFreq.txt" },
	{ "brazzers-freq", "D:/Purdue/CS590 PWD/dataset/brazzersFreq.txt" },
	{ "clixsense-freq", "D:/Purdue/CS590 PWD/dataset/clixsenseFreq.txt" },
	{ "csdn-freq", "D:/Purdue/CS590 PWD/dataset/csdnFreq.txt" },
	{ "linkedinsmall", "D:/Purdue/CS590 PWD/dataset/Datasets-master/linkedin/linkedin.com_98_68.pw.ascii.1.256.unhexed.full.weight" },
	{ "yahoo10000", "D:/Purdue/CS590 PWD/dataset/yahoo_subsample/yahoo_subsample_size=10000.txt" },
	{ "yahoo100000", "D:/Purdue/CS590 PWD/dataset/yahoo_subsample/yahoo_subsample_size=100000.txt" },
	{ "yahoo1000000", "D:/Purdue/CS590 PWD/dataset/yahoo_subsample/yahoo_subsample_size=1000000.txt" },
	{ "yahoo10000000", "D:/Purdue/CS590 PWD/dataset/yahoo_subsample/yahoo_subsample_size=10000000.txt" },
	{ "PIN4digit-rockyou", "D:/Purdue/Research/Datasets/PIN/RockYou-4-digit-Freq.txt" },
	{ "PIN6digit-rockyou", "D:/Purdue/Research/Datasets/PIN/RockYou-6-digit-Freq.txt" },
	{ "yahoo-nonereq", "D:/Purdue/CS590 PWD/dataset/yahoo_password_frequencies_corpus/yahoo-reg-basic-v2.txt" },
	{ "yahoo-6charmin", "D:/Purdue/CS590 PWD/dataset/yahoo_password_frequencies_corpus/yahoo-reg-basic-v3.txt" },
	{ "yahoo-female", "D:/Purdue/CS590 PWD/dataset/yahoo_password_frequencies_corpus/yahoo-gender-female.txt" },
	{ "yahoo-male", "D:/Purdue/CS590 PWD/dataset/yahoo_password_frequencies_corpus/yahoo-gender-male.txt" },
	{ "yahoo-0y", "D:/Purdue/CS590 PWD/dataset/yahoo_password_frequencies_corpus/yahoo-tenure-_1y.txt" },
	{ "yahoo-1y", "D:/Purdue/CS590 PWD/dataset/yahoo_password_frequencies_corpus/yahoo-tenure-1y.txt" },
	{ "yahoo-2y", "D:/Purdue/CS590 PWD/dataset/yahoo_password_frequencies_corpus/yahoo-tenure-2y.txt" },
	{ "yahoo-3y", "D:/Purdue/CS590 PWD/dataset/yahoo_password_frequencies_corpus/yahoo-tenure-3y.txt" },
	{ "yahoo-4y", "D:/Purdue/CS590 PWD/dataset/yahoo_password_frequencies_corpus/yahoo-tenure-4y.txt" },
	{ "yahoo-5-10y", "D:/Purdue/CS590 PWD/dataset/yahoo_password_frequencies_corpus/yahoo-tenure-5-10y.txt" },
	{ "yahoo-reset0", "D:/Purdue/CS590 PWD/dataset/yahoo_password_frequencies_corpus/yahoo-activity-pw-rec-count-0.txt" },
	{ "yahoo-reset1", "D:/Purdue/CS590 PWD/dataset/yahoo_password_frequencies_corpus/yahoo-activity-pw-rec-count-1.txt" },
	{ "yahoo-reset_1", "D:/Purdue/CS590 PWD/dataset/yahoo_password_frequencies_corpus/yahoo-activity-pw-rec-count-_1.txt" },
	{ "yahoo-resetGeq5", "D:/Purdue/CS590 PWD/dataset/yahoo_password_frequencies_corpus/yahoo-activity-pw-rec-count-_5.txt" },
	{ "neopets-m8", "D:/Purdue/CS590 PWD/dataset/PCP/neopets/neopets-min8lower0upper0digit0symbol0.txt" },
	{ "neopets-m8l1u1d1", "D:/Purdue/CS590 PWD/dataset/PCP/neopets/neopets-min8lower1upper1digit1symbol0.txt" },
	{ "neopets-m8l1u1d1s1", "D:/Purdue/CS590 PWD/dataset/PCP/neopets/neopets-min8lower1upper1digit1symbol1.txt" },
	{ "neopets-m16", "D:/Purdue/CS590 PWD/dataset/PCP/neopets/neopets-min16lower0upper0digit0symbol0.txt" },
	{ "neopets-m8-freq", "D:/Purdue/CS590 PWD/dataset/PCP/neopets/neopets-m8-freq.txt" },
	{ "neopets-m8l1u1d1-freq", "D:/Purdue/CS590 PWD/dataset/PCP/neopets/neopets-m8l1u1d1-freq.txt" },
	{ "neopets-m8l1u1d1s1-freq", "D:/Purdue/CS590 PWD/dataset/PCP/neopets/neopets-m8l1u1d1s1-freq.txt" },
	{ "neopets-m16-freq", "D:/Purdue/CS590 PWD/dataset/PCP/neopets/neopets-m16-freq.txt" },
};


unordered_map<string, int> N_map{
	{ "UserStudy_first-choice_4-digit", 851},
	{ "PIN4digit-amitay-dp", 204445 },
	{ "PIN4digit-amitay-dp-block1", 195558 },
	{ "PIN4digit-amitay-dp-block27", 163641 },
	{ "PIN4digit-amitay-dp-block100", 144570 },
	{ "PIN4digit-amitay-dp-block1000", 89078 },
	{ "PIN4digit-amitay-dp-block2740", 52048 },
	{ "PIN4digit-amitay-dp-block4000", 36343 },
	{"linkedin", 174292189},
	{"yahoo", 69301337},
	{"rockyou", 32603388},
	{ "rockyou-original", 32603388 },
	{"000webhost", 15268903},
	{ "neopets", 68345757},
	{ "bfield", 541016 },
	{ "brazzers", 925614 },
	{ "clixsense", 2222529 },
	{ "csdn", 6428449 },
	{ "linkedinsmall", 68361064},
	{ "yahoo10000", 10000 },
	{ "yahoo100000", 100000 },
	{ "yahoo1000000", 1000000 },
	{ "yahoo10000000", 10000000 },
	{ "PIN4digit-rockyou", 1780587 },
	{ "PIN6digit-rockyou", 2758490 },
	{ "yahoo-nonereq", 20434875 },
	{ "yahoo-6charmin", 13332334 },
	{ "yahoo-female", 30545765 },
	{ "yahoo-male", 38624554 },
	{ "yahoo-0y", 5182527 },
	{ "yahoo-1y", 5182527 },
	{ "yahoo-2y", 12261556 },
	{ "yahoo-3y", 10332348 },
	{ "yahoo-4y", 9290840 },
	{ "yahoo-5-10y", 29104856 },
	{ "yahoo-reset0", 61805038 },
	{ "yahoo-reset1", 4378667 },
	{ "yahoo-reset_1", 3117632 },
	{ "yahoo-resetGeq5", 387469 },
	{ "neopets-m8-freq", 42610271 },
	{ "neopets-m8l1u1d1-freq", 1716789 },
	{ "neopets-m8l1u1d1s1-freq", 187634 },
	{ "neopets-m16-freq", 1169493 },
};

unordered_map<string, int> distinct_map{
	{ "UserStudy_first-choice_4-digit", 722 },
	{ "PIN4digit-amitay-dp", 9885 },
	{ "PIN4digit-amitay-dp-block1", 9884 },
	{ "PIN4digit-amitay-dp-block27", 9858 },
	{ "PIN4digit-amitay-dp-block100", 9785 },
	{ "PIN4digit-amitay-dp-block1000", 8885 },
	{ "PIN4digit-amitay-dp-block2740", 7145 },
	{ "PIN4digit-amitay-dp-block4000", 5885 },
	{"linkedin", 57431283},
	{"yahoo", 33895873},
	{"rockyou", 14344391},
	{ "rockyou-original", 14344391 },
	{"000webhost", 10592935},
	{ "neopets", 27987227},
	{ "bfield", 416130 },
	{ "brazzers", 587934 },
	{ "clixsense", 1628577 },
	{ "csdn", 4037749 },
	{ "linkedinsmall", 6840885},
	{ "yahoo10000", 9583 },
	{ "yahoo100000", 88110 },
	{ "yahoo1000000", 764307 },
	{ "yahoo10000000", 6135968 },
	{ "PIN4digit-rockyou", 10000 },
	{ "PIN6digit-rockyou", 448185 },
	{ "yahoo-nonereq", 10728510 },
	{ "yahoo-6charmin", 7909580 },
	{ "yahoo-female", 15753280 },
	{ "yahoo-male", 20627909 },
	{ "yahoo-0y", 3600983 },
	{ "yahoo-1y", 3600983 },
	{ "yahoo-2y", 7430337 },
	{ "yahoo-3y", 6285194 },
	{ "yahoo-4y", 5562516 },
	{ "yahoo-5-10y", 15236685 },
	{ "yahoo-reset0", 29749212 },
	{ "yahoo-reset1", 3319177 },
	{"yahoo-reset_1", 2496611 },
	{"yahoo-resetGeq5", 351172 },
	{ "neopets-m8-freq", 21009893 },
	{ "neopets-m8l1u1d1-freq", 1212432 },
	{ "neopets-m8l1u1d1s1-freq", 164727 },
	{ "neopets-m16-freq", 959757 },
};

unordered_map<string, int> distinct_25k_map{
	{ "000webhost", 24304 },
	{ "neopets", 24116 },
	{ "bfield", 23220 },
	{ "brazzers", 22454 },
	{ "clixsense", 23750 },
	// { "csdn", 21089 } old
	{ "csdn", 21138 }
};

vector<string> PGSattacknames = { "Hashcat_wordlist-best64-generated2", "Markov_wordlist-order5-smoothed",
"PCFG_wordlist-2015", "NN_neural" };

//double t_delta(double delta, long N, int j);
int factorial(int n);
void theoreticallowerboundLgeq1_bestresult(string dname, int jmax, double mydelta, string output);
void theoreticallowerboundLgeq1();
void theoreticallowerboundLgeq1_countpasswordpair();
void plotPGSGuessingCurves();

//change the frequency-count dataset to password-startidx-endidx datset
void recoversamples(string inputfilename, string outputfilename);
//recoversamples+shuffle the dataset
void recoversamples_shuffled(string dataset);
void testifsamplevalid(string filename);
bool ismorefrequent(vector<int> &a, vector<int> &b);
bool static ismorefreqent_pair_long_long(const pair<long, long> &a, const pair<long, long> &b) { return a.first > b.first; }
bool ismorefrequent_pair(pair<string, int> &a, pair<string, int> &b);
bool isearlierguessed(pair<string, double> &a, pair<string, double> &b);
bool isPGSstr(string &s); // verify if the string s ONLY constrains characters in ASCII 32~126 (required by PGS)
bool hassmallerguessingnumber(pair<string, double> &a, pair<string, double> &b);
int countdistinctpasswords(string inputfilename);
// count the G most frequent passwords (and FrequencyUB) for linkedin, yahoo, rockyou datasets
void countmostfrequentpasswords(string output, vector<string> resourcenames, string foutname, double delta1 = 0.00009, bool usePinGlist = false);
///////////////void countmostfrequentpasswords(string output);
// count the G most frequent passwords (the upperbobund) for linkedinsmall dataset
// Don't use this function
void countmostfrequentpasswords2();
// perfect knowledge attack for clixsense_test.csv; use the original clixsense dataset to guess the clixsense_test dataset
void perfectknowledgeattack();
// count how many passwords in the dataset constrain characters in ASCII 32~126 (required by PGS)
void countPGSpasswords();
//find the min guessing number of each passwords among all empirical attack results we have in 000webhost25k or neopets25k
void minguessingnumber();

//output total number of passwords and number of distinct passwords for datasets in forms of {count, plaintext}
void basicinfo(string dname);
//subsample d number of passwords for datasets in forms of {count, plaintext}
void subsample(string dname, int d);



//generate the new lower bound described in section 5.3 in the writeup 
// generate SamplingLB
void experiment_newlowerbound(string dname, string output);
//generate the new lower bound described in section 5.3 in the writeup for datasets used in IEEES&P 19 paper (SamplingLB)
// generate SamplingLB in [SP:BloLiu23] paper with datasets used in IEEE S&P 19 paper
void experiment_newlowerbound2(string dname, string output);
//plot the guessing curves using the attack results generated by IEEES&P 19 paper
void experiment_plotguessingcurves2(string dname);
//generate the new lower bound described in section 5.4 in the writeup for datasets used in IEEES&P 19 paper
//the attack is, randomly partition the dataset into two sets D1, D2. First use all passwords in D1 to guess D2, 
// then use the password guesses in an empirical attack to guess passwords in D2, so that we can make more than $distinct$ guesses
// generate ExtendedLB in [SP:BloLiu23] paper  with datasets used in IEEE S&P 19 paper
void experiment_newlowerbound4(string dname, string output);
//generate the new lower bound described in section 5.3 in the writeup for linkedinsmall dataset 
//Datasets/linkedin/linkedin.com_98_68.pw.ascii.1.256.unhexed.full.weight
// Don't use this function
void experiment_newlowerbound3();
//generate PGS attack result file for rockyou in form of guessingnumber password percentage of cracked passwords (The same as attack result files for IEEES&P 19 paper)
void generatePGSresultfile();

//try to guess the unique passwords by modifying non-unique passwords using certain rulls (e.g. edit distance = 1)
// previous experiment; not used in the final version of the paper
void experiment_editdistance(string dname);
// plot the guessing curves generated by the unseen paper matlab code
void experiment_plotunseenguessingcurves();

void CDFzipflaw();

void subsample_frequencypair(string dname, long Nsub);

//generate frequency,count pairs for datasets in the IEEE S&P 19 paper like 000webhost and neopets datasets
void generatefrequencycountpairs(string dname);
// replace the space between frequency and password with '\t' for datasts in the IEEE s&p paper like 000webhost and neopets datasets
void replacedelimiter(string dname, char dilim);

// PIN
// raw PIN number dataset to formatted raw PIN number dataset by padding '0's (e.g. for 4-digit PINs, "85" --> "0085" )
void rawPIN_to_formattedrawPIN(string dname, int digit);
// raw PIN number dataset to frequency count pairs
void rawPIN_to_frequencylist(string dname);
// Attack dataset dname in format (pwd count) using a password dictionary in format (pwd)
// and then use Theorem 5,6 with d=N in [SP:BL23]
void experiment_lowerboundsbydictionaryattack(string dname, string dictName, string output);
// generate plots of frequency attack (guessing the password in decreasing order of frequency in the dataset)
void experiment_frequencyattack_frequencylist(string input_dir, string dname, string surfix);


int main() {
	// MonteCarloCounterExample();

	/*
	string dname_prefix = "passcodeDatawithRepetition"; // "passcodeDatawithRepetitionBlock4000";
	vector<int> d_list = { 2000, 1500, 1000, 500 };
	vector<int> block_num_list = { 0, 1, 27, 100, 1000, 2740, 4000 };
	string dname = "";
	for (auto d : d_list) {
		vector<string> dnames_same_size;
		for (auto block_num : block_num_list) {
			if (block_num > 0) {
				dname = dname_prefix + "Block" + to_string(block_num);
			}
			else {
				dname = dname_prefix;
			}
			dname = dname + "-subsample" + to_string(d) + "-Freq";
			datasetfilemap[dname] = "D:/Purdue/Research/Datasets/PIN/amitay/subsample/freqlist/" + dname + ".txt";
			cout << datasetfilemap[dname] << endl;
			vector<int> metadata = get_metadata(datasetfilemap[dname]);
			N_map[dname] = metadata[0];
			distinct_map[dname] = metadata[1];
			dnames_same_size.push_back(dname);
			// subsample_raw_data_to_raw_data("D:/Purdue/Research/Datasets/PIN/amitay/", "D:/Purdue/Research/Datasets/PIN/amitay/subsample/", dname, d);
			// rawPIN_to_frequencylist(dname);
			recoversamples_shuffled(dname);
			experiment_newlowerbound(dname, "lambda_G");
		}
		countmostfrequentpasswords("lambda_G", dnames_same_size, dname_prefix + "-subsample" + to_string(d) + "-FrequencyUB", 0.01);
	}
	*/

	/*
	checkBlocklist("D:/Purdue/Research/Datasets/PIN/amitay/passcodeDataDict.txt",
		"D:/Purdue/Research/Datasets/PIN/amitay/passcodeDatawithRepetition.txt",
		4000,
		true,
		"D:/Purdue/Research/Datasets/PIN/amitay/passcodeDatawithRepetitionBlock4000.txt");
	*/
	/*
	checkBlocklist("D:/Purdue/Research/Datasets/PIN/blocklists/Intersection-DD-iOS.txt",
		"D:/Purdue/Research/Datasets/PIN/UserStudy_intersection_first-choice_pin.txt",
		-1,
		true,
		"D:/Purdue/Research/Datasets/PIN/UserStudy_intersection_first-choice_pin_filtered_with_blocklist.txt");
	*/
	
	/*
	vector<int> d_list = { 5000, 2000, 1000, 500 };
	for (auto d : d_list) {
		subsample_rawdata_to_pwdfreq("D:/Purdue/CS590 PWD/dataset/Jeremiah/datasets/", "D:/Purdue/Research/Datasets/neopets_subsample/", "neopets25k", d);
	}
	*/

	/*
	vector<int> d_list = { 2000, 1500, 1000, 500 };
	vector<string> dname_list = { "yahoo-nonereq",  "yahoo-6charmin", "yahoo-0y", "yahoo-5-10y", "yahoo-female", "yahoo-male" };
	for (auto dname : dname_list) {
		for (auto d : d_list) {
			subsample_frequencypair(dname, d);
		}
	}
	*/
	/*
	vector<string> dnames = { "csdn" };
	for (auto dname : dnames) {
		// convert_guessing_curve_to_guessing_number("D:/Purdue/CS590 PWD/dataset/Datasets-master/smaller datasets/monte/", dname);
		string input_path = "D:/Purdue/CS590 PWD/dataset/Datasets-master/smaller datasets/datasets/" + dname + "25k.withcount";
		string output_dir = "D:/Purdue/CS590 PWD/dataset/Datasets-master/smaller datasets/datasets/moreformats/";
		freqpwd_to_frequencylist(dname, input_path, output_dir);
	}
	*/
	/*
	vector<string> dnames = { "000webhost", "neopets", "bfield", "brazzers", "clixsense", "csdn" };
	for (auto dname : dnames) {
		// convert_guessing_curve_to_guessing_number("D:/Purdue/CS590 PWD/dataset/Datasets-master/smaller datasets/monte/", dname);
		string input_path = "D:/Purdue/CS590 PWD/dataset/Jeremiah/09_perfect/" + dname + "_shuf_clean-withcount.txt";
		string output_dir = "D:/Purdue/CS590 PWD/dataset/Jeremiah/09_perfect/moreformats/";
		freqpwd_to_frequencylist(dname, input_path, output_dir);
	}
	*/
	
	// PIN
	/*
	vector<string> pinNames = {
		"UserStudy_intersection_first-choice_pin_filtered_with_blocklist",
		// "UserStudy_blockpin-1234_selected_pin", // final selected pin set after applying blocklist {1234}
		// "UserStudy_intersection_first-choice_pin",
		// "UserStudy_intersection_selected_pin",
		// "UserStudy_ios_4digit_noclickthrough_first-choice_pin",
		// "UserStudy_ios_4digit_noclickthrough_selected_pin",
		// "UserStudy_datadriven1_4digit_noclickthrough_first-choice_pin",
		// "UserStudy_datadriven1_4digit_noclickthrough_selected_pin",
		// "UserStudy_datadriven2_4digit_noclickthrough_first-choice_pin",
		// "UserStudy_datadriven2_4digit_noclickthrough_selected_pin",
	};
	for (auto pinName : pinNames) {
		// rawPIN_to_formattedrawPIN(pinName, 4);
		rawPIN_to_frequencylist(pinName);
	}
	*/
	
	// rawPIN_to_formattedrawPIN("UserStudy_control_4digit_noclickthrough_first-choice_pin", 4);
	// rawPIN_to_frequencylist("UserStudy_control_4digit_noclickthrough_first-choice_pin");  //"UserStudy_first-choice_4-digit" "RockYou-6-digit"
	// recoversamples_shuffled("PIN6digit-rockyou");
	// experiment_newlowerbound("PIN6digit-rockyou", "lambda_G");
	// countmostfrequentpasswords("lambda_G");

	countmostfrequentpasswords("lambda_G", {"UserStudy_first-choice_4-digit"}, "UserStudy_first-choice_4-digit-FrequencyUB", 0.01, true);
	
	/*
	string input_dir = "D:/Purdue/Research/Datasets/PIN/";
	vector<string> pinNames = { "UserStudy_first-choice_4-digit" };
	for (auto dname : pinNames) {
		experiment_frequencyattack_frequencylist(input_dir, dname, "-Freq");
	}
	*/
	/*
	vector<string> pinNames = {};// "UserStudy_first-choice_4-digit";  // "PIN4digit-amitay-dp";
	string pinNamePrefix = "PIN4digit-amitay-dp-block";
	vector<int> blocknumlist = { 1, 27, 100, 1000, 2740, 4000 };
	for (int i = 0; i < blocknumlist.size(); i++) {
		pinNames.push_back(pinNamePrefix + to_string(blocknumlist[i]));
	}
	for (auto pinName : pinNames) {
		// rawPIN_to_frequencylist(pinName);
		// recoversamples_shuffled(pinName);
		// experiment_newlowerbound(pinName, "lambda_G");
		//string dictName = "PIN4digit-amitay-dict";
		//experiment_lowerboundsbydictionaryattack(pinName, dictName, "lambda_G");
	}
	// countmostfrequentpasswords("lambda_G", pinNames, pinNamePrefix + "-FrequencyUB", 0.01);
	*/



	// Password project 

	// experiment_extractpasswordswithPCPs("neopets"); //extract passwords following specific password composition policies
	
	// experiment_manuallyAmendpasswordswithPCPs("neopets");

	// perfectknowledgeattack();
	// experiment_plotguessingcurves3("clixsense");
	// experiment_samplingLB3("clixsense", "lambda_G");
	// experiment_ExtendedLB3("clixsense", "lambda_G");


	
	//subsample("rockyou", 25000);
	//countPGSpasswords();
	//generatePGSresultfile();

	/*
	
	//vector<string> dnames = { "yahoo", "rockyou", "linkedin" }; // {"bfield", "brazzers", "clixsense", "csdn"};
	// vector<string> dnames = { "000webhost", "neopets", "bfield", "brazzers", "clixsense", "csdn" };
	// vector<string> dnames = { "yahoo10000", "yahoo100000", "yahoo1000000", "yahoo10000000" }; // {"bfield", "brazzers", "clixsense", "csdn"};
	// vector<string> dnames = { "yahoo-nonereq", "yahoo-6charmin" };
	// vector<string> dnames = { "yahoo-female", "yahoo-male" };
	// vector<string> dnames = { "yahoo-5-10y","yahoo-0y", "yahoo-1y", "yahoo-2y", "yahoo-3y", "yahoo-4y" };
	// vector<string> dnames = { "yahoo-reset0", "yahoo-reset1", "yahoo-reset_1", "yahoo-resetGeq5" };
	// vector<string> dnames = { "neopets-m8", "neopets-m8l1u1d1", "neopets-m8l1u1d1s1", "neopets-m16" };
	vector<string> dnames = { "csdn" };

	//for (int i = 0; i < dnames.size(); i++) { dnames[i] += "-freq"; }
	// countmostfrequentpasswords("lambda_G", dnames, "neopetsPCP");
	
	for (int i = 0; i < dnames.size(); i++) {
		// basicinfo(dnames[i]);
		// replacedelimiter(dnames[i],'\t');
		// generatefrequencycountpairs(dnames[i]); // generate frequency count pairs for datasets from Liu et al IEEE S&P 19 paper   
		
		//theoreticallowerboundLgeq1_bestresult(dnames[i], 1000, 0.01, "lambda_G"); //lower bound from prior work
		//theoreticallowerboundLgeq1_bestresult(dnames[i]+"-freq", 1000, 0.01, "lambda_G");

		// Generate SamplingLB using (frequency,count) pairs
		// recoversamples_shuffled(dnames[i]);
		// experiment_newlowerbound(dnames[i], "lambda_G"); // generate SamplingLB for lambda_G with yahoo/rockyou/linkedin dataset (frequency count pairs)
		
		experiment_newlowerbound2(dnames[i], "lambda_G"); // generate our SamplingLB for datasets from Liu et al IEEE S&P 19 paper   
		//experiment_newlowerbound4(dnames[i], "lambda_G");  // generate our extendedLB using empirical attack results for datasets from Liu et al IEEE S&P 19 paper 
		
		// experiment_plotguessingcurves2(dnames[i]);  //plot existing empirical attack results for datasets from Liu et al IEEE S&P 19 paper  
	}
	
	*/
	// CDFzipflaw();

	/*
	//generate subsampled frequency count pairs
	string dname = "yahoo";
	for (int Nsub = 1000; Nsub < N_map[dname]; Nsub *= 10) {
		subsample_frequencypair(dname, Nsub);
	}
	*/

	
	//recoversamples_shuffled("yahoo");
	
	
	
	//experiment_editdistance("neopets");
	

	//experiment_plotunseenguessingcurves();

	// minguessingnumber();

	//experiment_newlowerbound3();
	//countmostfrequentpasswords2();

	


	//theoreticallowerboundLgeq1_countpasswordpair();
	//plotPGSGuessingCurves();
	//theoreticallowerboundLgeq1();


	


	/*
	ifstream fin("D:/Purdue/CS590 PWD/dataset/myrockyou/rockyou25k_withoutcount.txt");
	ofstream fout("D:/Purdue/CS590 PWD/dataset/myrockyou/rockyou25k16PGSclean.txt");
	string linestr = "";
	unordered_set<string> subsample25k;
	vector<string> extraPGSpwd = { "tiatia", "e4t434t", "96impala", "willdav", "jaaabyy", "090105", "pakapol", "patang",
		"tezzy", "babygirl", "pisang", "Pink6623", "iloveyou11", "07041982", "super698769", "1188399", "bigezra",
		"99060589", "20219881521989", "resuello"};
	int nonPGScount = 0;
	while (getline(fin, linestr)) {
		if (isPGSstr(linestr)) {
			fout << linestr << "\n";
			subsample25k.insert(linestr);
		}
		else {
			nonPGScount++;
			continue;
		}
	}
	int count = 0;
	for (int i = 0; i < extraPGSpwd.size() && count < nonPGScount; i++) {
		if (isPGSstr(extraPGSpwd[i])) {
			if (subsample25k.find(extraPGSpwd[i]) == subsample25k.end()) fout << extraPGSpwd[i] << "\n";
			count++;
		}
		else {
			cout << extraPGSpwd[i] << " has non PGS characters" << endl;
			continue;
		}
	}
	*/
	
	cout << "Press ENTER to exit." << endl;
	cin.get();
	return 0;
}

int factorial(int n) {
	if (n < 0) {
		cout << "ERROR: invalid factorial n < 0" << endl;
		cin.get();
		return -1;
	}
	return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}


void theoreticallowerboundLgeq1_bestresult(string dname, int jmax, double mydelta, string output) {
	ifstream fin;
	ofstream fout;
	int j;
	long long L;
	long long N = 0;
	long long G;
	double sumY;
	double percentageY;
	double delta;
	double delta1 = 0.00009;
	double t_delta;

	//fin.open("D:/Purdue/CS590 PWD/dataset/linkedin_dataset/full.out");
	//fout.open("linkedin_plots.txt");
	//fout.open("linkedin_output.txt");
	//fin.open("D:/Purdue/CS590 PWD/dataset/yahoo_password_frequencies_corpus/yahoo-all.txt");
	//fout.open("yahoo_plots.txt");
	//fout.open("yahoo_output.txt");
	//fin.open("D:/Purdue/CS590 PWD/dataset/rockyouFreq.txt");
	//fout.open("rockyou_plots.txt");
	//fout.open("rockyou_output.txt");
	fin.open(datasetfilemap[dname]);
	fout.open(output + "-oldLBmax-" + dname + "_plots.txt");

	//fout.open("test.txt");

	long frequency, count;
	long tmp = -1;
	vector<long> fgeqj(jmax+1, 0);
	//long fgeqj2 = 0, fgeqj3 = 0, fgeqj4 = 0, fgeqj5 = 0;
	while (!fin.eof()) {
		frequency = 0;
		count = 0;
		fin >> frequency;
		fin >> count;
		//cout << frequency << endl;
		//cout << count << endl;
		if ((N + frequency * count) < 0 || (N + frequency * count) < N) {
			cout << "Error: the value of N exceeds the maximum value of a long interger!!!" << endl;
			cin.get();
		}
		N += frequency * count;
		/*
		if (frequency >= 2) fgeqj2 += frequency * count;
		if (frequency >= 3) fgeqj3 += frequency * count;
		if (frequency >= 4) fgeqj4 += frequency * count;
		if (frequency >= 5) fgeqj5 += frequency * count;
		*/
		for (int idx = 2; idx <= jmax; idx++) {
			if (frequency >= idx) fgeqj[idx] += frequency * count;
		}
		if (tmp == frequency) {
			cout << "tmp = " << tmp << "  frequency = " << frequency << endl;
			cin.get();
		}
		tmp = frequency;
	}

	vector<long long> Lplots(6*9, 0);// = { 1,2,3,5,10,50,100,500,1000,5000,10000, 50000, 100000, 500000, 1000000 };
	
	for (int i = 0; i < Lplots.size(); i++) {
		int i1 = i / 9;
		int i2 = i % 9;
		Lplots[i] = pow(10, i1)*(i2+1);
		//cout << Lplots[i] << " ";
	}
	//cin.get();

	if (output == "lambda(S,G)") delta = mydelta; //0.01
	else if (output == "lambda_G") delta = mydelta - delta1;
	else { cout << "ERROR: wrong parameter output = " << output << endl; cin.get(); }

	fout << "%" << output << endl;
	if (output == "lambda(S,G)") fout << "% delta(t) = " << delta << endl;
	else if (output == "lambda_G") fout << "% delta(t) = " << delta << "  delta1 = " << delta1 << endl;
	fout << "%" << dname << ", 2 <= j <= " << jmax << endl;
	fout << "\\addplot coordinates {";
	for (int i = 0; i < Lplots.size(); i++) {
		L = Lplots[i];
		G = N*L;
		delta = mydelta;// 0.01;
		double max_percentageY = 0.0;
		for (j = 2; j <= jmax; j++) {
			t_delta = j * sqrt(-1.0 / 2.0*N*log(delta));
			sumY = fgeqj[j] - ((double)N) / (factorial(j - 1)*pow((double)L, j - 1)) - t_delta;
			percentageY = sumY / (double)N * 100.0;
			if (output == "lambda_G") {
				double epsilon1 = sqrt(-log(delta1) / (2.0*(double)N));
				percentageY -= epsilon1;
			}
			if (max_percentageY < percentageY) max_percentageY = percentageY;
		}
		fout << "(" << G << "," << max_percentageY << ") ";
	}
	fout << "};" << endl;
	/*
	for (j = 2; j <= jmax; j++) {
		fout << "%RockYou, j = " << j << endl;
		fout << "\\addplot coordinates {";
		for (int i = 0; i < Lplots.size(); i++) {
			L = Lplots[i];
			G = N*L;
			delta = 0.001;
			t_delta = j * sqrt(-1.0 / 2.0*N*log(delta));
			sumY = fgeqj[j] - ((double)N) / (factorial(j - 1)*pow((double)L, j - 1)) - t_delta;
			percentageY = sumY / (double)N * 100.0;
			fout << "(" << G << "," << percentageY << ") ";
			if (L == 1) {
				cout << "j = " << j << "  L = " << L << endl;
				cout << "fgeqj[j] = " << fgeqj[j] << endl;
				cout << "((double)N) / (factorial(j - 1)*pow((double)L, j - 1)) = " << ((double)N) / (factorial(j - 1)*pow((double)L, j - 1)) << endl;
				cout << "t_delta = " << t_delta << endl;
			}
		}
		fout << "};" << endl;
	}
	*/
	//cin.get();


	fin.close();
	fout.close();
	return;
}


void theoreticallowerboundLgeq1() {
	ifstream fin;
	ofstream fout;
	int j = 2;
	long long L;
	long long N = 0;
	long long G;
	double sumY;
	double percentageY;
	double delta;
	double t_delta;

	//fin.open("D:/Purdue/CS590 PWD/dataset/linkedin_dataset/full.out");
	//fout.open("linkedin_plots.txt");
	//fout.open("linkedin_output.txt");
	//fin.open("D:/Purdue/CS590 PWD/dataset/yahoo_password_frequencies_corpus/yahoo-all.txt");
	//fout.open("yahoo_plots.txt");
	//fout.open("yahoo_output.txt");
	fin.open("D:/Purdue/CS590 PWD/dataset/rockyouFreq.txt");
	//fout.open("rockyou_plots.txt");
	fout.open("rockyou_output.txt");
	
	//fout.open("test.txt");

	long frequency, count;
	long tmp = -1;
	vector<long> fgeqj(6, 0);
	//long fgeqj2 = 0, fgeqj3 = 0, fgeqj4 = 0, fgeqj5 = 0;
	while (!fin.eof()) {
		frequency = 0;
		count = 0;
		fin >> frequency;
		fin >> count;
		//cout << frequency << endl;
		//cout << count << endl;
		if ((N + frequency * count) < 0 || (N + frequency * count) < N) {
			cout << "Error: the value of N exceeds the maximum value of a long interger!!!" << endl;
			cin.get();
		}
		N += frequency * count;
		/*
		if (frequency >= 2) fgeqj2 += frequency * count;
		if (frequency >= 3) fgeqj3 += frequency * count;
		if (frequency >= 4) fgeqj4 += frequency * count;
		if (frequency >= 5) fgeqj5 += frequency * count;
		*/
		for (int idx = 2; idx <= 5; idx++) {
			if (frequency >= idx) fgeqj[idx] += frequency * count;
		}
		if (tmp == frequency) {
			cout << "tmp = " << tmp << "  frequency = " << frequency << endl;
			cin.get();
		}
		tmp = frequency;
	}

	vector<long long> Lplots = { 1,2,3,5,10,50,100,500,1000,5000,10000, 50000, 100000, 500000, 1000000 };
	//j = 2
	j = 2;
	for (j = 2; j <= 5; j++) {
		fout << "%RockYou, j = " << j << endl;
		fout << "\\addplot coordinates {";
		for (int i = 0; i < Lplots.size(); i++) {
			L = Lplots[i];
			G = N*L;
			delta = 0.001;
			t_delta = j * sqrt(-1.0 / 2.0*N*log(delta));
			sumY = fgeqj[j] - ((double)N) / (factorial(j - 1)*pow((double)L, j - 1)) - t_delta;
			percentageY = sumY / (double)N * 100.0;
			fout << "(" << G << "," << percentageY << ") ";
			if (L == 1) {
				cout << "j = " << j << "  L = " << L << endl;
				cout << "fgeqj[j] = " << fgeqj[j] << endl;
				cout << "((double)N) / (factorial(j - 1)*pow((double)L, j - 1)) = " << ((double)N) / (factorial(j - 1)*pow((double)L, j - 1)) << endl;
				cout << "t_delta = " << t_delta << endl;
			}
		}
		fout << "};" << endl;
	}

	cin.get();


	/*
	long Lset[3] = {2,5,10};


	//j = 2
	fout << "\\begin{table}[ht]" << endl;
	fout << "\\centering" << endl;
	fout << "\\begin{tabular}{ | l | l | l | l | l | }" << endl;
	fout << "\\hline" << endl;
	fout << "L & G = NL & \\% cracked & $\\delta$ & $t_{ \\delta }$ \\\\ \\hline" << endl;
	j = 2;
	//fout << "N = " << N << ", j = " << j << endl;
	for (int i = 0; i < 3; i++) {
	L = Lset[i];
	G = N*L;
	delta = 0.01;
	t_delta = j * sqrt(-1.0 / 2.0*N*log(delta));
	sumY = fgeqj2 - ((double)N) / (1.0*pow((double)L, j - 1)) - t_delta;
	percentageY = sumY / (double)N * 100.0;
	if (sumY < 0) {
	cout << "sumY = " << sumY << endl;
	cout << "fgeqj2 = " << fgeqj2 << endl;
	cout << "((double)N) / (1.0*pow((double)L, j - 1)) = " << ((double)N) / (1.0*pow((double)L, j - 1)) << endl;
	cout << "t_delta = " << t_delta << endl;
	//cin.get();
	}
	fout << "\\multirow{ 2 }*{" << L << "} & \\multirow{ 2 }*{" << G << "} & " << percentageY << " & " << delta << " & " << t_delta << " \\\\" << endl;
	fout << "\\cline{3-5}" << endl;
	delta = 0.001;
	t_delta = j * sqrt(-1.0 / 2.0*N*log(delta));
	sumY = fgeqj2 - ((double)N) / (1.0*pow((double)L, j - 1)) - t_delta;
	percentageY = sumY / (double)N * 100.0;
	fout << "& & " << percentageY << " & " << delta << " & " << t_delta << " \\\\ \\hline" << endl;
	}
	fout << "\\end{tabular}" << endl;
	fout << "\\caption{ $N = " << N << " , j = " << j << " $ }" << endl;
	fout << "\\end{table}" << endl;
	fout << endl;



	//j = 3
	fout << "\\begin{table}[ht]" << endl;
	fout << "\\centering" << endl;
	fout << "\\begin{tabular}{ | l | l | l | l | l | }" << endl;
	fout << "\\hline" << endl;
	fout << "L & G = NL & \\% cracked & $\\delta$ & $t_{ \\delta }$ \\\\ \\hline" << endl;
	j = 3;
	//fout << "N = " << N << ", j = " << j << endl;
	for (int i = 0; i < 3; i++) {
	L = Lset[i];
	G = N*L;
	delta = 0.01;
	t_delta = j * sqrt(-1.0 / 2.0*N*log(delta));
	sumY = fgeqj3 - ((double)N) / (2.0*1.0*pow((double)L, j - 1)) - t_delta;
	percentageY = sumY / (double)N * 100.0;
	fout << "\\multirow{ 2 }*{" << L << "} & \\multirow{ 2 }*{" << G << "} & " << percentageY << " & " << delta << " & " << t_delta << " \\\\" << endl;
	fout << "\\cline{3-5}" << endl;
	delta = 0.001;
	t_delta = j * sqrt(-1.0 / 2.0*N*log(delta));
	sumY = fgeqj3 - ((double)N) / (2.0*1.0*pow((double)L, j - 1)) - t_delta;
	percentageY = sumY / (double)N * 100.0;
	fout << "& & " << percentageY << " & " << delta << " & " << t_delta << " \\\\ \\hline" << endl;
	}
	//cout << "t_delta/(double)N*100.0 = " << t_delta / (double)N*100.0 << endl;
	//cin.get();
	fout << "\\end{tabular}" << endl;
	fout << "\\caption{ $N = " << N << " , j = " << j << " $ }" << endl;
	fout << "\\end{table}" << endl;
	fout << endl;




	//j = 4
	fout << "\\begin{table}[ht]" << endl;
	fout << "\\centering" << endl;
	fout << "\\begin{tabular}{ | l | l | l | l | l | }" << endl;
	fout << "\\hline" << endl;
	fout << "L & G = NL & \\% cracked & $\\delta$ & $t_{ \\delta }$ \\\\ \\hline" << endl;
	j = 4;
	//fout << "N = " << N << ", j = " << j << endl;
	for (int i = 0; i < 3; i++) {
	L = Lset[i];
	G = N*L;
	delta = 0.01;
	t_delta = j * sqrt(-1.0 / 2.0*N*log(delta));
	sumY = fgeqj4 - ((double)N) / (3.0*2.0*1.0*pow((double)L, j - 1)) - t_delta;
	percentageY = sumY / (double)N * 100.0;
	fout << "\\multirow{ 2 }*{" << L << "} & \\multirow{ 2 }*{" << G << "} & " << percentageY << " & " << delta << " & " << t_delta << " \\\\" << endl;
	fout << "\\cline{3-5}" << endl;
	delta = 0.001;
	t_delta = j * sqrt(-1.0 / 2.0*N*log(delta));
	sumY = fgeqj4 - ((double)N) / (3.0*2.0*1.0*pow((double)L, j - 1)) - t_delta;
	percentageY = sumY / (double)N * 100.0;
	fout << "& & " << percentageY << " & " << delta << " & " << t_delta << " \\\\ \\hline" << endl;
	}
	fout << "\\end{tabular}" << endl;
	fout << "\\caption{ $N = " << N << " , j = " << j << " $ }" << endl;
	fout << "\\end{table}" << endl;
	fout << endl;
	*/

fin.close();
fout.close();
return;
}

void theoreticallowerboundLgeq1_countpasswordpair() {
	ifstream fin;
	ofstream fout;
	int j = 2;
	long long L;
	long long N = 0;
	long long G;
	double sumY;
	double percentageY;
	double delta;
	double t_delta;

	//fin.open("D:/Purdue/CS590 PWD/dataset/Datasets-master/linkedin/linkedin.com_98_68.pw.ascii.1.256.unhexed.10m.withcount");
	//fout.open("linkedin.com_98_68.pw.ascii.1.256.unhexed.10m_plots.txt");
	fin.open("D:/Purdue/CS590 PWD/dataset/Datasets-master/linkedin/linkedin.com_98_68.pw.ascii.1.256.unhexed.full.weight");
	fout.open("linkedin.com_98_68.pw.ascii.1.256.unhexed.full.weight_plots.txt");



	long frequency;
	string password;
	
	vector<long> fgeqj(6, 0);
	//long fgeqj2 = 0, fgeqj3 = 0, fgeqj4 = 0, fgeqj5 = 0;
	int i = 0;
	string linestr;
	stringstream ss;
	while (getline(fin, linestr)) {
		frequency = 0;
		password = "";
		ss << linestr;
		ss >> frequency;
		ss.clear();
		ss.str("");
		linestr = "";
		/*
		if (frequency == 0) {
			cout << "frequency = " << frequency << endl;
			cout << i << endl;
			cin.get();
		}
		*/
		//cout << frequency << endl;
		//cout << count << endl;
		if ((N + frequency) < 0 || (N + frequency) < N) {
			cout << "Error: the value of N exceeds the maximum value of a long interger!!!" << endl;
			cin.get();
		}
		N += frequency;
		for (int idx = 2; idx <= 5; idx++) {
			if (frequency >= idx) fgeqj[idx] += frequency;
		}
		i++;
		if (i % 1000000 == 0) cout << i << endl;
	}
	cout << "N = " << N << endl;
	vector<long long> Lplots = { 1,2,3,5,10,50,100,500,1000,5000,10000, 50000, 100000, 500000, 1000000 };
	//j = 2
	j = 2;
	for (j = 2; j <= 5; j++) {
		fout << "%linkedin.com_98_68.pw.ascii.1.256.unhexed.full.weight, j = " << j << endl;
		fout << "\\addplot coordinates {";
		for (int i = 0; i < Lplots.size(); i++) {
			L = Lplots[i];
			G = N*L;
			delta = 0.001;
			t_delta = j * sqrt(-1.0 / 2.0*N*log(delta));
			sumY = fgeqj[j] - ((double)N) / (factorial(j - 1)*pow((double)L, j - 1)) - t_delta;
			percentageY = sumY / (double)N * 100.0;
			fout << "(" << G << "," << percentageY << ") ";
			if (L == 1) {
				cout << "j = " << j << "  L = " << L << endl;
				cout << "fgeqj[j] = " << fgeqj[j] << endl;
				cout << "((double)N) / (factorial(j - 1)*pow((double)L, j - 1)) = " << ((double)N) / (factorial(j - 1)*pow((double)L, j - 1)) << endl;
				cout << "t_delta = " << t_delta << endl;
			}
		}
		fout << "};" << endl;
	}

	cin.get();


	/*
	long Lset[3] = {2,5,10};


	//j = 2
	fout << "\\begin{table}[ht]" << endl;
	fout << "\\centering" << endl;
	fout << "\\begin{tabular}{ | l | l | l | l | l | }" << endl;
	fout << "\\hline" << endl;
	fout << "L & G = NL & \\% cracked & $\\delta$ & $t_{ \\delta }$ \\\\ \\hline" << endl;
	j = 2;
	//fout << "N = " << N << ", j = " << j << endl;
	for (int i = 0; i < 3; i++) {
	L = Lset[i];
	G = N*L;
	delta = 0.01;
	t_delta = j * sqrt(-1.0 / 2.0*N*log(delta));
	sumY = fgeqj2 - ((double)N) / (1.0*pow((double)L, j - 1)) - t_delta;
	percentageY = sumY / (double)N * 100.0;
	if (sumY < 0) {
	cout << "sumY = " << sumY << endl;
	cout << "fgeqj2 = " << fgeqj2 << endl;
	cout << "((double)N) / (1.0*pow((double)L, j - 1)) = " << ((double)N) / (1.0*pow((double)L, j - 1)) << endl;
	cout << "t_delta = " << t_delta << endl;
	//cin.get();
	}
	fout << "\\multirow{ 2 }*{" << L << "} & \\multirow{ 2 }*{" << G << "} & " << percentageY << " & " << delta << " & " << t_delta << " \\\\" << endl;
	fout << "\\cline{3-5}" << endl;
	delta = 0.001;
	t_delta = j * sqrt(-1.0 / 2.0*N*log(delta));
	sumY = fgeqj2 - ((double)N) / (1.0*pow((double)L, j - 1)) - t_delta;
	percentageY = sumY / (double)N * 100.0;
	fout << "& & " << percentageY << " & " << delta << " & " << t_delta << " \\\\ \\hline" << endl;
	}
	fout << "\\end{tabular}" << endl;
	fout << "\\caption{ $N = " << N << " , j = " << j << " $ }" << endl;
	fout << "\\end{table}" << endl;
	fout << endl;



	//j = 3
	fout << "\\begin{table}[ht]" << endl;
	fout << "\\centering" << endl;
	fout << "\\begin{tabular}{ | l | l | l | l | l | }" << endl;
	fout << "\\hline" << endl;
	fout << "L & G = NL & \\% cracked & $\\delta$ & $t_{ \\delta }$ \\\\ \\hline" << endl;
	j = 3;
	//fout << "N = " << N << ", j = " << j << endl;
	for (int i = 0; i < 3; i++) {
	L = Lset[i];
	G = N*L;
	delta = 0.01;
	t_delta = j * sqrt(-1.0 / 2.0*N*log(delta));
	sumY = fgeqj3 - ((double)N) / (2.0*1.0*pow((double)L, j - 1)) - t_delta;
	percentageY = sumY / (double)N * 100.0;
	fout << "\\multirow{ 2 }*{" << L << "} & \\multirow{ 2 }*{" << G << "} & " << percentageY << " & " << delta << " & " << t_delta << " \\\\" << endl;
	fout << "\\cline{3-5}" << endl;
	delta = 0.001;
	t_delta = j * sqrt(-1.0 / 2.0*N*log(delta));
	sumY = fgeqj3 - ((double)N) / (2.0*1.0*pow((double)L, j - 1)) - t_delta;
	percentageY = sumY / (double)N * 100.0;
	fout << "& & " << percentageY << " & " << delta << " & " << t_delta << " \\\\ \\hline" << endl;
	}
	//cout << "t_delta/(double)N*100.0 = " << t_delta / (double)N*100.0 << endl;
	//cin.get();
	fout << "\\end{tabular}" << endl;
	fout << "\\caption{ $N = " << N << " , j = " << j << " $ }" << endl;
	fout << "\\end{table}" << endl;
	fout << endl;




	//j = 4
	fout << "\\begin{table}[ht]" << endl;
	fout << "\\centering" << endl;
	fout << "\\begin{tabular}{ | l | l | l | l | l | }" << endl;
	fout << "\\hline" << endl;
	fout << "L & G = NL & \\% cracked & $\\delta$ & $t_{ \\delta }$ \\\\ \\hline" << endl;
	j = 4;
	//fout << "N = " << N << ", j = " << j << endl;
	for (int i = 0; i < 3; i++) {
	L = Lset[i];
	G = N*L;
	delta = 0.01;
	t_delta = j * sqrt(-1.0 / 2.0*N*log(delta));
	sumY = fgeqj4 - ((double)N) / (3.0*2.0*1.0*pow((double)L, j - 1)) - t_delta;
	percentageY = sumY / (double)N * 100.0;
	fout << "\\multirow{ 2 }*{" << L << "} & \\multirow{ 2 }*{" << G << "} & " << percentageY << " & " << delta << " & " << t_delta << " \\\\" << endl;
	fout << "\\cline{3-5}" << endl;
	delta = 0.001;
	t_delta = j * sqrt(-1.0 / 2.0*N*log(delta));
	sumY = fgeqj4 - ((double)N) / (3.0*2.0*1.0*pow((double)L, j - 1)) - t_delta;
	percentageY = sumY / (double)N * 100.0;
	fout << "& & " << percentageY << " & " << delta << " & " << t_delta << " \\\\ \\hline" << endl;
	}
	fout << "\\end{tabular}" << endl;
	fout << "\\caption{ $N = " << N << " , j = " << j << " $ }" << endl;
	fout << "\\end{table}" << endl;
	fout << endl;
	*/

	fin.close();
	fout.close();
	return;
}

void plotPGSGuessingCurves() {
	ifstream fin;
	ofstream fout;
	long long L;
	vector<long long> Lplots = { 1,2,3,5,10,50,100,500,1000,5000,10000, 50000, 100000, 500000, 1000000 };
	long long N = 68361064;
	long long G;
	long totalpass = 0;
	vector<double> sumY(Lplots.size(), 0);
	double percentageY;

	//fin.open("D:/Purdue/CS590 PWD/dataset/linkedin_dataset/full.out");
	//fout.open("linkedin_plots.txt");
	//fout.open("linkedin_output.txt");

	//fin.open("D:/Purdue/CS590 PWD/dataset/Datasets-master/linkedin subsample - PGS/linkedin30k_markov.txt");
	//fout.open("linkedin30k_markov_plots.txt");
	//fin.open("D:/Purdue/CS590 PWD/dataset/Datasets-master/linkedin subsample - PGS/linkedin30k_neuralnet.txt");
	//fout.open("linkedin30k_neuralnet_plots.txt");
	fin.open("D:/Purdue/CS590 PWD/dataset/Datasets-master/linkedin subsample - PGS/linkedin30k_pcfg.txt");
	fout.open("linkedin30k_pcfg_plots.txt");


	string password;
	double guess;
	long safe = 0;
	while (!fin.eof()) {
		password = "";
		guess = 0.0;
		fin >> password;
		fin >> guess;
		if (password != "") totalpass++;
		if (guess == -5) {
			safe++;
			continue;
		}
		for (int i = 0; i < Lplots.size(); i++) {
			L = Lplots[i];
			G = N*L;
			if (G < N || G < L) {
				cout << "ERROR: G=N*L exceeds the limit!" << endl;
				cin.get();
			}
			if (guess <= G) sumY[i]++;
		}
	}
	cout << "safe = " << safe << endl;
	fout << "total number of passwords = " << totalpass << endl;
	fout << "%linkedin30k_pcfg"  << endl;
	fout << "\\addplot coordinates {";
	for (int i = 0; i < Lplots.size(); i++) {
		percentageY = sumY[i] / (double)totalpass * 100.0;
		fout << "(" << N*Lplots[i] << "," << percentageY << ") ";
	}
	fout << "};" << endl;
	cin.get();


	fin.close();
	fout.close();
	return;
}

void experiment_newlowerbound(string dname, string output) {
	string datasetname = dname; // "rockyou";  //"yahoo"; // "linkedin";  
	/*
	if (dname != "linkedin" && dname != "yahoo" && dname != "rockyou" 
		&& dname.substr(0,5) != "yahoo" 
		&& dname != "PIN4digit-rockyou" && dname != "PIN6digit-rockyou"
		&& dname != "yahoo-nonereq" && dname != "yahoo-6charmin"
		&& dname != "yahoo-female" && dname != "yahoo-male"
		&& dname != "yahoo-0y" && dname != "yahoo-1y" && dname != "yahoo-2y"
		&& dname != "yahoo-3y" && dname != "yahoo-4y" && dname != "yahoo-5-10y"
		&& dname != "yahoo-reset0" && dname != "yahoo-reset1" && dname != "yahoo-reset_1" && dname != "yahoo-resetGeq5"
		) {
		cout << "ERROR: unknown dname = " << dname << endl;
		cin.get();
		return;
	}
	*/
	if (output != "lambda_G" && output != "lambda(S,G)") {
		cout << "ERROR: unknown output = " << output << endl;
		cin.get();
		return;
	}

	string inputfilename = datasetfilemap[datasetname];

	/*
	unordered_map<string, string> shuffledsamplefilemap;
	shuffledsamplefilemap["linkedin"] = "linkedin_samples_shuffled.txt";
	shuffledsamplefilemap["yahoo"] = "yahoo_samples_shuffled.txt";
	shuffledsamplefilemap["rockyou"] = "rockyou_samples_shuffled.txt";
	string samplefilename = shuffledsamplefilemap[datasetname];
	*/
	string samplefilename = dname + "_samples_shuffled.txt";

	//string inputfilename = "D:/Purdue/CS590 PWD/dataset/linkedin_dataset/full.out";
	//string samplefilename = "linkedin_samples.txt";
	//string inputfilename = "D:/Purdue/CS590 PWD/dataset/yahoo_password_frequencies_corpus/yahoo-all.txt";
	//string samplefilename = "yahoo_samples.txt";
	//string inputfilename = "D:/Purdue/CS590 PWD/dataset/rockyouFreq.txt";
	//string samplefilename = "rockyou_samples.txt";

	//only need to be done for once
	//recoversamples(inputfilename, samplefilename);
	
	//testifsamplevalid(samplefilename);


	int N = N_map[datasetname];
	int distinct = distinct_map[datasetname];

	//int Nd_divisor = 2;
	//int d = N / Nd_divisor;


	////// start setting d
	int d = N / 3; //  pow(10, 5); // 25000; // 100000;
	// test for yahoo subsample size = 10^4 ~ 10^7
	// if we set delta=0.05
	/*
	if (dname.substr(0, 5) == "yahoo") {
		if (N == N_map["yahoo"]) d = 25000;
		else if (N <= 10000) d = 1000;
		else d = 10767;
	}
	*/
	// if we set delta=0.01 as usual
	if (dname.substr(0, 6) == "yahoo1") {
		cout << "ATTENTION: change d value due to dname.substr(0, 6) == \"yahoo1\"" << endl;
		cin.get();
		if (N <= 10000) d = 2500;
		else d = 25000;
	}
	//for small PIN datasets
	if (N <= d * 2) d = N / 2;
	////// end setting d

	//int N_linkedin = 174292189;
	//int N_yahoo = 69301337;
	//int N_rockyou = 32603388;
	//int distinct_yahoo = countdistinctpasswords(samplefilename);
	//int distinct_linkedin = countdistinctpasswords(samplefilename);
	//int distinct_rockyou = countdistinctpasswords(samplefilename);
	//int distinct_linkedin = 57431283;
	//int distinct_yahoo = 33895873;
	//int distinct_rockyou = 14344391;
	//int N = N_rockyou; //N_linkedin;  // N_yahoo; 
	//int distinct = distinct_rockyou; // distinct_linkedin;  // distinct_yahoo; 
	
	int G = 1;
	//string outputfilename = "newlowerbound-N_div_d=" + to_string(Nd_divisor) + "-" + datasetname + "_plots.txt";
	string outputfilename = output + "newlowerbound-d=" + to_string(d) + "-" + datasetname + "_plots.txt";
	ifstream fin(samplefilename);
	ofstream fout(outputfilename);

	////ofstream fout2("newlowerbound-N_div_d=" + to_string(Nd_divisor) + "-" + datasetname + "_S-D&Dfrequencies.txt");
	//ofstream fout2("newlowerbound-d=" + to_string(d) + "-" + datasetname + "_S-D&Dfrequencies.txt");
	//ofstream mylog(datasetname + "-N_div_d = " + to_string(Nd_divisor) + "_logfile.txt");
	ofstream mylog(output + datasetname + "-d = " + to_string(d) + "_logfile.txt");


	int seed = 123456;
	default_random_engine e(seed);
	uniform_int_distribution<unsigned> u1(0, N-1);
	vector<bool> samplelist(N, false);
	int randidx;
	cout << "start generating d different random indices" << endl;
	for (int i = 0; i < d; i++) {
		randidx = u1(e);
		while (samplelist[randidx] == true) randidx = u1(e);
		samplelist[randidx] = true;
	}
	cout << "end generating d different random indices" << endl;
	vector<vector<int>> SminusD(distinct,vector<int>(2,0));
	for (int i = 0; i < distinct; i++) SminusD[i][0] = i;
	vector<int> Dset(distinct, 0);
	string curpassword = "";
	int curpassidx = 0;
	int startidx, endidx;
	cout << "start constructing set D and set S-D" << endl;
	while (!fin.eof()) {
		curpassword = "";
		startidx = 0;
		endidx = 0;
		fin >> curpassword >> startidx >> endidx;
		if (curpassword == "") break;
		if (endidx >= N) {
			cout << "ERROR: more samples than expected (N)!!" << endl;
			cin.get();
			exit(-1);
		}
		for (int i = startidx; i <= endidx; i++) {
			if (samplelist[i] == true) {
				Dset[curpassidx]++;
			}
			else SminusD[curpassidx][1]++;
		}
		curpassidx++;
	}
	cout << "end constructing set D and set S-D:   curpassidx = " << curpassidx << endl;
	/*
	cout << "start shuffle SminusD" << endl;
	unsigned SminusDseed = chrono::system_clock::now().time_since_epoch().count();
	shuffle(SminusD.begin(), SminusD.end(), default_random_engine(SminusDseed));
	cout << "end shuffle SminusD" << endl;
	*/

	cout << "start sorting SminusD" << endl;
	sort(SminusD.begin(), SminusD.end(), ismorefrequent);
	cout << "end sorting SminusD" << endl;

	/*
	cout << "start writing set S-D and set D into a file" << endl;

	fout2 << "set S-D   set D" << endl;
	for (int i = 0; i < distinct; i++) {
	//for (int i = 8388608; i<= 57418913; i++) {
		fout2 << i << "  " << SminusD[i][1] << "  " << Dset[SminusD[i][0]] << endl;
	}
	cout << "end writing set S-D and set D into a file" << endl;
	*/


	cout << "start computing lowerbounds" << endl;
	double hfunc = 0;
	double gfunc = 0;
	double percentage_of_guessed_passwords = 0.0;
	double delta = 0.01;

	
	double delta1;
	double delta2;
	double t1;
	double t2;

	int min_t_idx = -1;
	double min_t = -1;
	/////////////////////////////////////////
	/*
	//find the best parameters t1,t2,delta1, delta2 to minimize n/(double)d*t2+t1.
	for (int i = 1; i <= 9; i++) {
		delta1 = delta*0.1*i;
		delta2 = delta - delta1;
		t1 = sqrt(-1.0 / 2.0*N*log(delta1));
		t2 = sqrt(-1.0 / 2.0*d*log(delta2));
		double cur_t = (double)N / (double)d *t2 + t1;
		if (min_t_idx == -1) {
			min_t_idx = i;
			min_t = cur_t;
		}
		else if (cur_t < min_t) {
			min_t_idx = i;
			min_t = cur_t;
		}
	}
	delta1 = delta*0.1*min_t_idx;
	delta2 = delta - delta1;
	*/
	/////////////////////fix delta1
	delta1 = 0.00009;
	delta2 = delta - delta1;
	//////////////////////////////////###########2021.08.09 temperately added, need to be removed###############################
	// delta *= 5;
	// delta1 *= 5;
	// delta2 *= 5;
	//////////////////////////////////##########################################
	t1 = sqrt(-1.0 / 2.0*N*log(delta1));
	t2 = sqrt(-1.0 / 2.0*d*log(delta2));
	cout << "N = " << N << "  d = " << d << "  distinct = " << distinct << endl;
	mylog << "N = " << N << "  d = " << d << "  distinct = " << distinct << endl;
	cout << "delta = " << delta << "  delta1 = " << delta1 << "  delta2 = " << delta2 << endl;
	mylog << "delta = " << delta << "  delta1 = " << delta1 << "  delta2 = " << delta2 << endl;
	cout << "t1 = " << t1 << "  t2 = " << t2 << endl;
	mylog << "t1 = " << t1 << "  t2 = " << t2 << endl;
	fout << "%" << outputfilename << endl;
	fout << "%1 <= G <= distinct  " << "delta = " << delta << "delta1 = " << delta1 << "  delta2 = " << delta2 << endl;
	fout << "\\addplot coordinates {";
	G = 1;
	bool flag = false;
	int hfunc_idx = 0;
	//ofstream mytestlog("mytestlog_linkedin.txt");
	while (G <= distinct && flag == false) {
		gfunc = 0;
		for (hfunc_idx; hfunc_idx < G; hfunc_idx++) {
			if (SminusD[hfunc_idx][1] == 0) {
				G = hfunc_idx;
				flag = true;
				break;
			}
			hfunc += Dset[SminusD[hfunc_idx][0]]; // in set D, count the number of passwords that are G most frequent in set S-D
			/*
			if (G >= 8388608 && Dset[SminusD[hfunc_idx][0]] != 0) {
				mytestlog << "G = " << G << "  SminusD[hfunc_idx][0] = " << SminusD[hfunc_idx][0]
					<< "  SminusD[hfunc_idx][1] = " << SminusD[hfunc_idx][1]
					<< "  Dset[SminusD[hfunc_idx][0]] = " << Dset[SminusD[hfunc_idx][0]] << endl;
			}
			*/
		}
		if (output == "lambda_G") gfunc = (double)N / (double)d * (hfunc - t2);
		else if (output == "lambda(S,G)") gfunc = (double)N / (double)d * (hfunc - t2) - t1; // the lowerbound of the number of cracked passwords
		else { cout << "ERROR: output == " << output << endl; cin.get(); }
		percentage_of_guessed_passwords = (double)gfunc / (double)N * 100;
		fout << "(" << G << "," << percentage_of_guessed_passwords << ") ";
		cout << "G = " << G << "  hfunc = " << hfunc << "  gfunc = " << gfunc << endl;
		mylog << "G = " << G << "  hfunc = " << hfunc << "  gfunc = " << gfunc << endl;
		if (G <distinct && (G << 1) > distinct) G = distinct;
		else G = (G << 1);
	}
	fout << "};" << endl;
	cout << "end computing lowerbounds" << endl;
	//cin.get();
	//cin.get();
	fout.close();
	//fout2.close();
	mylog.close();
	return;
}

void experiment_newlowerbound2(string dname, string output) {
	if (output != "lambda_G" && output != "lambda(S,G)") {
		cout << "ERROR: incorrect input parameter outout = " << output << endl;
		cin.get();
		return;
	}
	string datasetname;

	//unordered_map<string, int> distinct_25k_map;
	//distinct_25k_map["000webhost"] = 24304;
	//distinct_25k_map["neopets"] = 24116;

	string inputfilename;
	string inputtestfilename;

	if (dname == "rockyou") {
		datasetname = "myrockyou";
		inputfilename = "D:/Purdue/CS590 PWD/dataset/myrockyou/my_rockyou-withcount.txt";
		inputtestfilename = "D:/Purdue/CS590 PWD/dataset/myrockyou/rockyou25k.txt";
	}
	else {
		datasetname = dname; // "neopets"; // "000webhost";
		inputfilename = datasetfilemap[datasetname];
		inputtestfilename = "D:/Purdue/CS590 PWD/dataset/Jeremiah/datasets/" + datasetname + "25k.withcount";
	}
	string remainingsamplefilename = datasetname + "_samples_remaining.txt";
	string testsamplefilname = datasetname + "_samples_25k.txt";

	ifstream fin_all(inputfilename);
	ifstream fin_test(inputtestfilename);


	int N = 0; // N_map[datasetname];
	int distinct;
	if (dname == "rockyou") distinct = distinct_map["rockyou"];
	else distinct = distinct_map[datasetname];

	//int Nd_divisor = 2;
	int d = 25000;

	unordered_map<string, int> testsetmp;
	string password = "";
	int count = 0;
	int N_test = 0;
	int totalnum_test = 0;
	cout << "start reading " << inputtestfilename << endl;

	string linestr = "";
	while (getline(fin_test, linestr)) {
		if (linestr.size() == 0) {
			cout << "totalnum_test = " << totalnum_test << endl;
			cout << "fin_test  linestr.size() == 0" << endl;
			cin.get();
			continue;
		}
		password = "";
		count = 0;
		int tmpidx1 = 0, tmpidx2 = 0;
		while (tmpidx1 < linestr.size() && linestr[tmpidx1] == ' ') tmpidx1++;
		if (tmpidx1 == linestr.size()) {
			cout << "totalnum_test = " << totalnum_test << endl;
			cout << "fin_test  tmpidx1 == linestr.size()" << endl;
			cin.get();
			continue;
		}
		tmpidx2 = tmpidx1;
		while (tmpidx2 < linestr.size() && linestr[tmpidx2] != ' ') tmpidx2++;
		count = stoi(linestr.substr(tmpidx1, tmpidx2 - tmpidx1));
		password = linestr.substr(tmpidx2 + 1);
		linestr = "";
		totalnum_test++;
		N_test += count;
		testsetmp[password] = count;
	}

	/*
	while (!fin_test.eof()) {
		password = "";
		count = 0;
		fin_test >> count >> password;
		if (count == 0) {
			cout << "totalnum_test = " << totalnum_test << endl;
			cout << "fin_test  count = " << count << "  password = " << password << endl;
			cin.get();
			continue;
		}
		
	}
	*/
	cout << "end reading " << inputtestfilename << endl;
	cout << "N_test = " << N_test << "  totalnum_test = " << totalnum_test << endl;

	vector<vector<int>> SminusD(distinct, vector<int>(2, 0));
	for (int i = 0; i < distinct; i++) SminusD[i][0] = i;
	vector<int> Dset(distinct, 0);

	N = 0;
	int idx = 0;
	cout << "start reading " << inputfilename << endl;
	linestr = "";
	int tmpcounttest = 0;
	while (getline(fin_all, linestr)) {
		if (linestr.size() == 0) {
			cout << "idx = " << idx << endl;
			cout << "fin_all  linestr.size() == 0" << endl;
			cin.get();
			continue;
		}
		password = "";
		count = 0;
		int tmpidx1 = 0, tmpidx2 = 0;
		while (tmpidx1 < linestr.size() && linestr[tmpidx1] == ' ') tmpidx1++;
		if (tmpidx1 == linestr.size()) {
			cout << "idx = " << idx << endl;
			cout << "fin_all  tmpidx1 == linestr.size()" << endl;
			cin.get();
			continue;
		}
		tmpidx2 = tmpidx1;
		while (tmpidx2 < linestr.size() && linestr[tmpidx2] != ' ') tmpidx2++;
		count = stoi(linestr.substr(tmpidx1, tmpidx2 - tmpidx1));
		password = linestr.substr(tmpidx2 + 1);
		if (testsetmp.find(password) != testsetmp.end()) {
			SminusD[idx][1] = count - testsetmp[password];
			Dset[idx] = testsetmp[password];
			tmpcounttest++;
		}
		else {
			SminusD[idx][1] = count;
			Dset[idx] = 0;
		}
		N += count;
		idx++;
		linestr = "";
	}
	/*
	while (!fin_all.eof()) {
		password = "";
		count = 0;
		fin_all >> count >> password;
		if (count == 0) {
			cout << "fin_all  count == 0" << endl;
			continue;
		}
		
		if (testsetmp.find(password) != testsetmp.end()) {
			SminusD[idx][1] = count - testsetmp[password];
			Dset[idx] = testsetmp[password];
		}
		else {
			SminusD[idx][1] = count;
			Dset[idx] = 0;
		}
		N += count;
		idx++;
	}
	*/
	cout << "end reading " << inputfilename << endl;
	if (idx != distinct) {
		cout << "ERROR: idx != distinct    idx = " << idx << "  distinct = " << distinct << endl;
		cin.get();
		exit(-1);
	}
	cout << "tmpcounttest = " << tmpcounttest << "  totalnum_test = " << totalnum_test << endl;
	cout << "N = " << N << "  distinct = " << distinct << "  idx = " << idx << endl;

	fin_all.close();
	fin_test.close();
	
	cout << "start shuffle SminusD" << endl;
	unsigned SminusDseed = chrono::system_clock::now().time_since_epoch().count();
	shuffle(SminusD.begin(), SminusD.end(), default_random_engine(SminusDseed));
	cout << "end shuffle SminusD" << endl;
	

	cout << "start sorting SminusD" << endl;
	sort(SminusD.begin(), SminusD.end(), ismorefrequent);
	cout << "end sorting SminusD" << endl;

	
	cout << "start writing set S-D and set D into files" << endl;
	ofstream fout_SminusD(remainingsamplefilename);
	ofstream fout_Dset(testsamplefilname);
	for (int i = 0; i < distinct; i++) {
		fout_SminusD << i << " " << SminusD[i][1] << endl;
		fout_Dset << SminusD[i][0] << " " << Dset[SminusD[i][0]] << endl;
	}
	cout << "end writing set S-D and set D into files" << endl;
	


	int G = 1;
	//ifstream fin_SminusD(remainingsamplefilename);
	//ifstream fin_Dset(testsamplefilname);
	string outputfilename = output + "-newlowerbound-d=" + to_string(d) + "-" + datasetname + "_plots.txt";
	ofstream fout(outputfilename);

	//ofstream fout2("newlowerbound-d=" + to_string(d) + "-" + datasetname + "_S-D&Dfrequencies.txt");
	ofstream mylog(output + "-" + datasetname + "-d = " + to_string(d) + "_logfile.txt");
	


	cout << "start computing lowerbounds" << endl;
	double hfunc = 0;
	double gfunc = 0;
	double percentage_of_guessed_passwords = 0.0;
	double delta = 0.01;


	double delta1;
	double delta2;
	double t1;
	double t2;

	int min_t_idx = -1;
	double min_t = -1;

	/*
	///////find the best parameters t1,t2,delta1, delta2 to minimize n/(double)d*t2+t1.
	for (int i = 1; i <= 9; i++) {
		delta1 = delta*0.1*i;
		delta2 = delta - delta1;
		t1 = sqrt(-1.0 / 2.0*N*log(delta1));
		t2 = sqrt(-1.0 / 2.0*d*log(delta2));
		double cur_t = (double)N / (double)d *t2 + t1;
		if (min_t_idx == -1) {
			min_t_idx = i;
			min_t = cur_t;
		}
		else if (cur_t < min_t) {
			min_t_idx = i;
			min_t = cur_t;
		}
	}
	delta1 = delta*0.1*min_t_idx;
	delta2 = delta - delta1;
	*/
	//////assign value to delta1 and delta2 instread of finding the best parameters
	delta1 = 0.00009; // 0.001;
	delta2 = delta - delta1;
	/////////////////////////
	t1 = sqrt(-1.0 / 2.0*N*log(delta1));
	t2 = sqrt(-1.0 / 2.0*d*log(delta2));
	cout << "N = " << N << "  d = " << d << "  distinct = " << distinct << endl;
	mylog << "N = " << N << "  d = " << d << "  distinct = " << distinct << endl;
	cout << "delta = " << delta << "  delta1 = " << delta1 << "  delta2 = " << delta2 << endl;
	mylog << "delta = " << delta << "  delta1 = " << delta1 << "  delta2 = " << delta2 << endl;
	cout << "t1 = " << t1 << "  t2 = " << t2 << endl;
	mylog << "t1 = " << t1 << "  t2 = " << t2 << endl;
	fout << "%" << outputfilename << endl;
	fout << "%1 <= G <= distinct  " << "delta = " << delta << "delta1 = " << delta1 << "  delta2 = " << delta2 << endl;
	fout << "\\addplot coordinates {";
	G = 1;
	bool flag = false;
	int hfunc_idx = 0;
	while (G <= distinct && flag == false) {
		gfunc = 0;
		for (hfunc_idx; hfunc_idx < G; hfunc_idx++) {
			if (SminusD[hfunc_idx][1] == 0) {
				G = hfunc_idx;
				flag = true;
				break;
			}
			hfunc += Dset[SminusD[hfunc_idx][0]]; // in set D, count the number of passwords that are G most frequent in set S-D
		}
		if (output == "lambda_G") gfunc = (double)N / (double)d * (hfunc - t2);
		else if (output == "lambda(S,G)") gfunc = (double)N / (double)d * (hfunc - t2) - t1; // the lowerbound of the number of cracked passwords
		else { cout << "ERROR: output = " << output << endl; cin.get(); }
		percentage_of_guessed_passwords = (double)gfunc / (double)N * 100;
		fout << "(" << G << "," << percentage_of_guessed_passwords << ") ";
		cout << "G = " << G << "  hfunc = " << hfunc << "  gfunc = " << gfunc << endl;
		mylog << "G = " << G << "  hfunc = " << hfunc << "  gfunc = " << gfunc << endl;
		if (G <distinct && (G << 1) > distinct) G = distinct;
		else G = (G << 1);
	}
	fout << "};" << endl;
	cout << "end computing lowerbounds" << endl;
	//cin.get();
	//cin.get();
	//fout2.close();
	mylog.close();
	return;
}

void experiment_newlowerbound3() {
	string datasetname = "linkedinsmall"; 

	unordered_map<string, int> distinct_30k_map;
	distinct_30k_map["linkedinsmall"] = 29990;


	string inputfilename = datasetfilemap[datasetname];
	string inputtestfilename = "D:/Purdue/CS590 PWD/dataset/Datasets-master/linkedin subsample - PGS/linkedin30k_markov.txt";
	string remainingsamplefilename = datasetname + "_samples_remaining.txt";
	string testsamplefilname = datasetname + "_samples_30k.txt";

	ifstream fin_all(inputfilename);
	ifstream fin_test(inputtestfilename);




	int N = 0; // N_map[datasetname];
	int distinct = distinct_map[datasetname];

	//int Nd_divisor = 2;
	int d = 30000;

	unordered_map<string, int> testsetmp;
	string password = "";
	int count = 0;
	int N_test = 0;
	int totalnum_test = 0;
	cout << "start reading " << inputtestfilename << endl;

	string linestr = "";
	while (getline(fin_test, linestr)) {
		if (linestr.size() == 0) {
			cout << "totalnum_test = " << totalnum_test << endl;
			cout << "fin_test  linestr.size() == 0" << endl;
			cin.get();
			continue;
		}
		password = "";
		int tmpidx1 = linestr.size() - 1;
		while (tmpidx1 >=0 && linestr[tmpidx1] == '\t') tmpidx1--;
		if (tmpidx1 < 0) {
			cout << "totalnum_test = " << totalnum_test << endl;
			cout << "fin_test  tmpidx1 < 0" << endl;
			cin.get();
			exit(-1);
		}
		while (tmpidx1 >= 0 && linestr[tmpidx1] != '\t') tmpidx1--;
		if (tmpidx1 <= 0) {
			cout << "totalnum_test = " << totalnum_test << endl;
			cout << "fin_test  tmpidx1 <= 0" << endl;
			cin.get();
			exit(-1);
		}
		password = linestr.substr(0, tmpidx1);
		linestr = "";
		totalnum_test++;
		N_test ++;
		testsetmp[password]++;
		if (testsetmp[password] > 1) {
			cout << "password = " << password << "  testsetmp[password] = " << testsetmp[password] << endl;
		}
	}

	cout << "end reading " << inputtestfilename << endl;
	cout << "N_test = " << N_test << "  totalnum_test = " << totalnum_test << endl;
	cout << "testsetmp.size() = " << testsetmp.size() << endl;

	cin.get();
	cin.get();
	

	vector<vector<int>> SminusD(distinct, vector<int>(2, 0));
	for (int i = 0; i < distinct; i++) SminusD[i][0] = i;
	vector<int> Dset(distinct, 0);

	N = 0;
	int idx = 0;
	cout << "start reading " << inputfilename << endl;
	linestr = "";
	int tmpcounttest = 0;
	while (getline(fin_all, linestr)) {
		if (linestr.size() == 0) {
			cout << "idx = " << idx << endl;
			cout << "fin_all  linestr.size() == 0" << endl;
			cin.get();
			continue;
		}
		password = "";
		count = 0;
		int tmpidx1 = 0;
		while (tmpidx1 < linestr.size() && linestr[tmpidx1] != '\t') tmpidx1++;
		if (tmpidx1 == 0) {
			cout << "idx = " << idx << endl;
			cout << "ERRROR: fin_all tmpidx1 == 0    linestr = " << linestr << endl;
			cin.get();
			exit(-1);
		}
		else if (tmpidx1+1 >= linestr.size()) {
			cout << "idx = " << idx << endl;
			cout << "ERRROR: fin_all tmpidx1+1 >= linestr.size()    linestr = " << linestr << endl;
			cin.get();
			exit(-1);
		}
		count = stoi(linestr.substr(0, tmpidx1));
		password = linestr.substr(tmpidx1 + 1);
		if (testsetmp.find(password) != testsetmp.end()) {
			SminusD[idx][1] = count - testsetmp[password];
			Dset[idx] = testsetmp[password];
			tmpcounttest++;
			testsetmp.erase(password);
		}
		else {
			SminusD[idx][1] = count;
			Dset[idx] = 0;
		}
		N += count;
		idx++;
		linestr = "";
	}
	cout << "end reading " << inputfilename << endl;
	if (idx != distinct) {
		cout << "ERROR: idx != distinct    idx = " << idx << "  distinct = " << distinct << endl;
		cin.get();
		exit(-1);
	}
	cout << "tmpcounttest = " << tmpcounttest << "  totalnum_test = " << totalnum_test << endl;
	cout << "N = " << N << "  distinct = " << distinct << "  idx = " << idx << endl;

	for (auto &m : testsetmp) {
		cout << "password = " << m.first << "  count = " << m.second << endl;
	}

	fin_all.close();
	fin_test.close();

	cin.get();
	cin.get();
	return;

	cout << "start shuffle SminusD" << endl;
	unsigned SminusDseed = chrono::system_clock::now().time_since_epoch().count();
	shuffle(SminusD.begin(), SminusD.end(), default_random_engine(SminusDseed));
	cout << "end shuffle SminusD" << endl;


	cout << "start sorting SminusD" << endl;
	sort(SminusD.begin(), SminusD.end(), ismorefrequent);
	cout << "end sorting SminusD" << endl;


	cout << "start writing set S-D and set D into files" << endl;
	ofstream fout_SminusD(remainingsamplefilename);
	ofstream fout_Dset(testsamplefilname);
	for (int i = 0; i < distinct; i++) {
		fout_SminusD << i << " " << SminusD[i][1] << endl;
		fout_Dset << SminusD[i][0] << " " << Dset[SminusD[i][0]] << endl;
	}
	cout << "end writing set S-D and set D into files" << endl;



	int G = 1;
	//ifstream fin_SminusD(remainingsamplefilename);
	//ifstream fin_Dset(testsamplefilname);
	string outputfilename = "newlowerbound-d=" + to_string(d) + "-" + datasetname + "_plots.txt";
	ofstream fout(outputfilename);

	ofstream fout2("newlowerbound-d=" + to_string(d) + "-" + datasetname + "_S-D&Dfrequencies.txt");
	ofstream mylog(datasetname + "-d = " + to_string(d) + "_logfile.txt");



	cout << "start computing lowerbounds" << endl;
	double hfunc = 0;
	double gfunc = 0;
	double percentage_of_guessed_passwords = 0.0;
	double delta = 0.01;


	double delta1;
	double delta2;
	double t1;
	double t2;

	int min_t_idx = -1;
	double min_t = -1;

	//find the best parameters t1,t2,delta1, delta2 to minimize n/(double)d*t2+t1.
	for (int i = 1; i <= 9; i++) {
		delta1 = delta*0.1*i;
		delta2 = delta - delta1;
		t1 = sqrt(-1.0 / 2.0*N*log(delta1));
		t2 = sqrt(-1.0 / 2.0*d*log(delta2));
		double cur_t = (double)N / (double)d *t2 + t1;
		if (min_t_idx == -1) {
			min_t_idx = i;
			min_t = cur_t;
		}
		else if (cur_t < min_t) {
			min_t_idx = i;
			min_t = cur_t;
		}
	}
	delta1 = delta*0.1*min_t_idx;
	delta2 = delta - delta1;
	t1 = sqrt(-1.0 / 2.0*N*log(delta1));
	t2 = sqrt(-1.0 / 2.0*d*log(delta2));
	cout << "N = " << N << "  d = " << d << "  distinct = " << distinct << endl;
	mylog << "N = " << N << "  d = " << d << "  distinct = " << distinct << endl;
	cout << "delta = " << delta << "  delta1 = " << delta1 << "  delta2 = " << delta2 << endl;
	mylog << "delta = " << delta << "  delta1 = " << delta1 << "  delta2 = " << delta2 << endl;
	cout << "t1 = " << t1 << "  t2 = " << t2 << endl;
	mylog << "t1 = " << t1 << "  t2 = " << t2 << endl;
	fout << "%" << outputfilename << endl;
	fout << "%1 <= G <= distinct  " << "delta = " << delta << "delta1 = " << delta1 << "  delta2 = " << delta2 << endl;
	fout << "\\addplot coordinates {";
	G = 1;
	bool flag = false;
	int hfunc_idx = 0;
	while (G <= distinct && flag == false) {
		gfunc = 0;
		for (hfunc_idx; hfunc_idx < G; hfunc_idx++) {
			if (SminusD[hfunc_idx][1] == 0) {
				G = hfunc_idx;
				flag = true;
				break;
			}
			hfunc += Dset[SminusD[hfunc_idx][0]]; // in set D, count the number of passwords that are G most frequent in set S-D
		}
		gfunc = (double)N / (double)d * (hfunc - t2) - t1; // the lowerbound of the number of cracked passwords
		percentage_of_guessed_passwords = (double)gfunc / (double)N * 100;
		fout << "(" << G << "," << percentage_of_guessed_passwords << ") ";
		cout << "G = " << G << "  hfunc = " << hfunc << "  gfunc = " << gfunc << endl;
		mylog << "G = " << G << "  hfunc = " << hfunc << "  gfunc = " << gfunc << endl;
		if (G <distinct && (G << 1) > distinct) G = distinct;
		else G = (G << 1);
	}
	fout << "};" << endl;
	cout << "end computing lowerbounds" << endl;
	cin.get();
	cin.get();
	fout2.close();
	mylog.close();
	return;
}

void generatePGSresultfile() {
	string datasetname = "rockyou";

	string input25ksamplename = "D:/Purdue/CS590 PWD/dataset/myrockyou/rockyou25k.txt";
	ifstream fin(input25ksamplename);
	int d = 25000;

	unordered_map<string, int> testsetmp;
	
	string password = "";
	int count = 0;
	int N_test = 0;
	int totalnum_test = 0;
	cout << "start reading " << input25ksamplename << endl;
	string linestr = "";
	while (getline(fin, linestr)) {
		if (linestr.size() == 0) {
			cout << "totalnum_test = " << totalnum_test << endl;
			cout << "fin_test  linestr.size() == 0" << endl;
			cin.get();
			continue;
		}
		password = "";
		count = 0;
		int tmpidx1 = 0, tmpidx2 = 0;
		while (tmpidx1 < linestr.size() && linestr[tmpidx1] == ' ') tmpidx1++;
		if (tmpidx1 == linestr.size()) {
			cout << "totalnum_test = " << totalnum_test << endl;
			cout << "fin_test  tmpidx1 == linestr.size()" << endl;
			cin.get();
			continue;
		}
		tmpidx2 = tmpidx1;
		while (tmpidx2 < linestr.size() && linestr[tmpidx2] != ' ') tmpidx2++;
		count = stoi(linestr.substr(tmpidx1, tmpidx2 - tmpidx1));
		password = linestr.substr(tmpidx2 + 1);
		linestr = "";
		totalnum_test++;
		N_test += count;
		testsetmp[password] = count;
	}

	cout << "end reading " << input25ksamplename << endl;
	cout << "N_test = " << N_test << "  totalnum_test = " << totalnum_test << endl;


	for (int i = 0; i < PGSattacknames.size(); i++) {
		string attackname = PGSattacknames[i];
		ifstream fin_PGS("D:/Purdue/CS590 PWD/dataset/myrockyou/PGSresults/rockyou25k_" + attackname);
		ofstream fout_PGS("D:/Purdue/CS590 PWD/dataset/myrockyou/attackresults/rockyou25kresults_" + attackname + ".txt");
		unordered_map<string, double> PGSresult_map;
		
		cout << "start reading " << attackname << endl;
		password = "";
		double guessingnum = 0;
		linestr = "";
		int total_PGSpwd = 0;
		while (getline(fin_PGS, linestr)) {
			if (linestr.size() == 0) {
				cout << "total_PGSpwd = " << total_PGSpwd << endl;
				cout << "fin_PGS  linestr.size() == 0" << endl;
				cin.get();
				continue;
			}
			password = "";
			guessingnum = 0;
			int tmpidx1 = linestr.size() - 1;
			while (tmpidx1 >= 0 && linestr[tmpidx1] == '\t') tmpidx1--;
			if (tmpidx1 < 0) {
				cout << "total_PGSpwd = " << total_PGSpwd << endl;
				cout << "fin_PGS  tmpidx1 < 0" << endl;
				cin.get();
				exit(-1);
			}
			while (tmpidx1 >= 0 && linestr[tmpidx1] != '\t') tmpidx1--;
			if (tmpidx1 <= 0) {
				cout << "total_PGSpwd = " << total_PGSpwd << endl;
				cout << "fin_PGS  tmpidx1 <= 0" << endl;
				cin.get();
				exit(-1);
			}
			password = linestr.substr(0, tmpidx1);
			guessingnum = stod(linestr.substr(tmpidx1+1));
			PGSresult_map[password] = guessingnum;
			total_PGSpwd++;
			linestr = "";
		}
		cout << "end reading " << attackname << endl;
		cout << "total_PGSpwd = " << total_PGSpwd << endl;
		cout << "PGSresult_map.size() = " << PGSresult_map.size() << endl;

		vector<pair<string, double>> outputform(totalnum_test, pair<string, double>("", -5));
		int idx = 0;
		for (auto &v : testsetmp) {
			if (idx > outputform.size()) {
				cout << "ERROR: idx > outputform.size()" << endl;
				cin.get();
			}
			outputform[idx].first = v.first;
			if (PGSresult_map.find(v.first) == PGSresult_map.end()) outputform[idx].second = -5;
			else outputform[idx].second = PGSresult_map[v.first]; //guessing number
			idx++;
		}

		sort(outputform.begin(), outputform.end(), isearlierguessed); //sort by guessing number
		double presum = 0;
		for (int i = 0; i < outputform.size(); i++) {
			if (outputform[i].second == -5) continue;
			password = outputform[i].first;
			for (int j = 0; j < testsetmp[password]; j++) {
				presum += 1 / (double)d * 100;
				fout_PGS << outputform[i].second << "\t" << outputform[i].first << "\t" << presum << endl;
			}
		}

		fin_PGS.close();
		fout_PGS.close();
	}
	fin.close();
	return;
}

void experiment_newlowerbound4(string dname, string output) {
	if (output != "lambda_G" && output != "lambda(S,G)") {
		cout << "ERROR: incorrect input parameter outout = " << output << endl;
		cin.get();
		return;
	}

	string datasetname;

	//unordered_map<string, int> distinct_25k_map;
	//distinct_25k_map["000webhost"] = 24304;
	//distinct_25k_map["neopets"] = 24116;

	string inputfilename;
	string inputtestfilename;

	if (dname == "rockyou") {
		datasetname = "myrockyou";
		inputfilename = "D:/Purdue/CS590 PWD/dataset/myrockyou/my_rockyou-withcount.txt";
		inputtestfilename = "D:/Purdue/CS590 PWD/dataset/myrockyou/rockyou25k.txt";
	}
	else {
		datasetname = dname; // "neopets"; // "000webhost";
		inputfilename = datasetfilemap[datasetname];
		inputtestfilename = "D:/Purdue/CS590 PWD/dataset/Jeremiah/datasets/" + datasetname + "25k.withcount";
	}
	string remainingsamplefilename = datasetname + "_samples_remaining.txt";
	string testsamplefilname = datasetname + "_samples_25k.txt";
	

	ifstream fin_all(inputfilename);
	ifstream fin_test(inputtestfilename);


	int N = 0; // N_map[datasetname];
	int distinct;
	if (dname == "rockyou") distinct = distinct_map["rockyou"];
	else distinct = distinct_map[datasetname];

	//int Nd_divisor = 2;
	int d = 25000;

	unordered_map<string, int> testsetmp;
	string password = "";
	int count = 0;
	int N_test = 0;
	int totalnum_test = 0;
	cout << "start reading " << inputtestfilename << endl;

	string linestr = "";
	
	while (getline(fin_test, linestr)) {
		if (linestr.size() == 0) {
			cout << "totalnum_test = " << totalnum_test << endl;
			cout << "fin_test  linestr.size() == 0" << endl;
			cin.get();
			continue;
		}
		password = "";
		count = 0;
		int tmpidx1 = 0, tmpidx2 = 0;
		while (tmpidx1 < linestr.size() && linestr[tmpidx1] == ' ') tmpidx1++;
		if (tmpidx1 == linestr.size()) {
			cout << "totalnum_test = " << totalnum_test << endl;
			cout << "fin_test  tmpidx1 == linestr.size()" << endl;
			cin.get();
			continue;
		}
		tmpidx2 = tmpidx1;
		while (tmpidx2 < linestr.size() && linestr[tmpidx2] != ' ') tmpidx2++;
		count = stoi(linestr.substr(tmpidx1, tmpidx2 - tmpidx1));
		password = linestr.substr(tmpidx2 + 1);
		linestr = "";
		totalnum_test++;
		N_test += count;
		testsetmp[password] = count;
	}
	
	cout << "end reading " << inputtestfilename << endl;
	cout << "N_test = " << N_test << "  totalnum_test = " << totalnum_test << endl;

	vector<vector<int>> SminusD(distinct, vector<int>(2, 0));
	for (int i = 0; i < distinct; i++) SminusD[i][0] = i;
	vector<int> Dset(distinct, 0);
	unordered_map<string, int> passidxmp;

	N = 0;
	int idx = 0;
	cout << "start reading " << inputfilename << endl;
	linestr = "";
	int tmpcounttest = 0;
	
	while (getline(fin_all, linestr)) {
		if (linestr.size() == 0) {
			cout << "idx = " << idx << endl;
			cout << "fin_all  linestr.size() == 0" << endl;
			cin.get();
			continue;
		}
		password = "";
		count = 0;
		int tmpidx1 = 0, tmpidx2 = 0;
		while (tmpidx1 < linestr.size() && linestr[tmpidx1] == ' ') tmpidx1++;
		if (tmpidx1 == linestr.size()) {
			cout << "idx = " << idx << endl;
			cout << "fin_all  tmpidx1 == linestr.size()" << endl;
			cin.get();
			continue;
		}
		tmpidx2 = tmpidx1;
		while (tmpidx2 < linestr.size() && linestr[tmpidx2] != ' ') tmpidx2++;
		count = stoi(linestr.substr(tmpidx1, tmpidx2 - tmpidx1));
		password = linestr.substr(tmpidx2 + 1);
		passidxmp[password] = idx; //map the password string to the index of Dset
		if (testsetmp.find(password) != testsetmp.end()) {
			SminusD[idx][1] = count - testsetmp[password];
			Dset[idx] = testsetmp[password];
			tmpcounttest++;
		}
		else {
			SminusD[idx][1] = count;
			Dset[idx] = 0;
		}
		N += count;
		idx++;
		linestr = "";
	}
	
	cout << "end reading " << inputfilename << endl;
	if (idx != distinct) {
		cout << "ERROR: idx != distinct    idx = " << idx << "  distinct = " << distinct << endl;
		cin.get();
		exit(-1);
	}
	cout << "tmpcounttest = " << tmpcounttest << "  totalnum_test = " << totalnum_test << endl;
	cout << "N = " << N << "  distinct = " << distinct << "  idx = " << idx << endl;

	fin_all.close();
	fin_test.close();

	cout << "start shuffle SminusD" << endl;
	unsigned SminusDseed = chrono::system_clock::now().time_since_epoch().count();
	shuffle(SminusD.begin(), SminusD.end(), default_random_engine(SminusDseed));
	cout << "end shuffle SminusD" << endl;


	cout << "start sorting SminusD" << endl;
	sort(SminusD.begin(), SminusD.end(), ismorefrequent);
	cout << "end sorting SminusD" << endl;
	
	/*
	cout << "start writing set S-D and set D into files" << endl;
	ofstream fout_SminusD(remainingsamplefilename);
	ofstream fout_Dset(testsamplefilname);
	for (int i = 0; i < distinct; i++) {
		fout_SminusD << i << " " << SminusD[i][1] << endl;
		fout_Dset << SminusD[i][0] << " " << Dset[SminusD[i][0]] << endl;
	}
	cout << "end writing set S-D and set D into files" << endl;
	*/


	
	string outputfilename = output + "-G_geq_distinct_newlowerbound-d=" + to_string(d) + "-" + datasetname + "_plots.txt";
	ofstream fout(outputfilename);

	//ofstream fout2("G_geq_distinct_newlowerbound-d=" + to_string(d) + "-" + datasetname + "_S-D&Dfrequencies.txt");
	ofstream mylog(output + "-G_geq_distinct_" + datasetname + "-d = " + to_string(d) + "_logfile.txt");



	cout << "start computing first lowerbounds" << endl;
	double hfunc = 0;
	double gfunc = 0;
	double percentage_of_guessed_passwords = 0.0;
	double delta = 0.01;


	double delta1;
	double delta2;
	double t1;
	double t2;

	int min_t_idx = -1;
	double min_t = -1;
	/*
	///////find the best parameters t1,t2,delta1, delta2 to minimize n/(double)d*t2+t1.
	for (int i = 1; i <= 9; i++) {
		delta1 = delta*0.1*i;
		delta2 = delta - delta1;
		t1 = sqrt(-1.0 / 2.0*N*log(delta1));
		t2 = sqrt(-1.0 / 2.0*d*log(delta2));
		double cur_t = (double)N / (double)d *t2 + t1;
		if (min_t_idx == -1) {
			min_t_idx = i;
			min_t = cur_t;
		}
		else if (cur_t < min_t) {
			min_t_idx = i;
			min_t = cur_t;
		}
	}
	delta1 = delta*0.1*min_t_idx;
	delta2 = delta - delta1;
	*/
	//////assign value to delta1 and delta2 instread of finding the best parameters
	delta1 = 0.00009; // 0.001;
	delta2 = delta - delta1; // 0.009;
	/////////////////////////
	t1 = sqrt(-1.0 / 2.0*N*log(delta1));
	t2 = sqrt(-1.0 / 2.0*d*log(delta2));
	cout << "N = " << N << "  d = " << d << "  distinct = " << distinct << endl;
	mylog << "N = " << N << "  d = " << d << "  distinct = " << distinct << endl;
	cout << "delta = " << delta << "  delta1 = " << delta1 << "  delta2 = " << delta2 << endl;
	mylog << "delta = " << delta << "  delta1 = " << delta1 << "  delta2 = " << delta2 << endl;
	cout << "t1 = " << t1 << "  t2 = " << t2 << endl;
	mylog << "t1 = " << t1 << "  t2 = " << t2 << endl;
	fout << "%" << outputfilename << endl;
	fout << "%delta = " << delta << "delta1 = " << delta1 << "  delta2 = " << delta2 << endl;

	double G = 0;
	//first use Set SminusD to guess Dset
	for (int i = 0; i < SminusD.size(); i++) {
		if (SminusD[i][1] == 0) {
			break;
		}
		else {
			hfunc += Dset[SminusD[i][0]]; // in set D, count the number of passwords that are G most frequent in set S-D
			G = G+1;
		}
	}
	cout << "end computing lowerbounds" << endl;


	//Then use an empirical attack to guess Dset
	string prefix;
	vector<vector<string>> attackresults;
	if (dname == "rockyou") {
		prefix = "D:/Purdue/CS590 PWD/dataset/myrockyou/attackresults/rockyou25kresults_";
		attackresults = {
			{prefix + "Hashcat_wordlist-best64-generated2.txt", "Hashcat: wordlist-best64-generated2" },
			{prefix + "Markov_wordlist-order5-smoothed.txt", "Markov: wordlist-order5-smoothed"},
			{prefix + "PCFG_wordlist-2015.txt", "PCFG: wordlist-2015"},
			{prefix + "NN_neural.txt", "Neural Network: neural"},
		};
	}
	else {
		prefix = "D:/Purdue/CS590 PWD/dataset/Datasets-master/smaller datasets/monte/" + datasetname + "/" + datasetname;
		attackresults = {
			//{ prefix + "_perfect_result.txt", "Perfect Knowledge" },
			{ prefix + "_4gram_result.txt", "Markov: 4-gram" },
			{ prefix + "_backoff_result.txt", "Markov: Backoff" },
			{ prefix + "_omen_result.txt", "Markov: OMEN" },
			{ prefix + "_jtr_result.txt", "JtR: Original" },
			{ prefix + "_jtr_opt_result.txt", "JtR: Reordered" },
			{ prefix + "_jtr_extended_opt_result.txt", "JtR: Extended" },
			{ prefix + "_hc_extended_result.txt", "Hashcat: Extended" },
			{ prefix + "_hc_result.txt", "Hashcat" },
			{ prefix + "_pcfg_result.txt", "PCFG: 2009" },
			{ prefix + "_saranga_result.txt", "PCFG: 2016" },
			{ prefix + "_rnn_result.txt", "Neural Network" }//,
			//{datasetname + "_minguessingnumber.txt", "minguessingnumber" },
			//{ datasetname + "_minguessingnumber(2times)-markov4gram-rnn.txt", "(2times)minguessingnumber-markov4gram-rnn" },
			//{ datasetname + "_minguessingnumber(3times)-markov4gram-rnn-pcfg2009.txt", "(3times)minguessingnumber-markov4gram-rnn-pcfg2009" }
		};
	}
	vector<bool> guessed(distinct, false); // guessed[i] = true iff the password with index=1 in Dset has been guessed i.e. the password is in SminusD
	for (int i = 0; i < G; i++) {
		if (SminusD[i][1] == 0) {
			cout << "ERROR: SminusD[i][1] == 0!!" << endl;
		}
		guessed[SminusD[i][0]] = true;
	}
	double baseguessingnum = G;
	double basehfunc = hfunc;
	double minG = baseguessingnum;
	double maxG = pow(10, 16);
	fout << "%" << minG << " <= G <= " << maxG << endl;
	cout << "baseguessingnum = " << baseguessingnum << endl;
	//ofstream fouttest("./000webhost_fortesting");
	for (int i = 0; i < attackresults.size(); i++) {
		ifstream fin(attackresults[i][0]);
		fout << "%" << attackresults[i][1] << endl;
		fout << "%" << attackresults[i][0] << endl;
		fout << "\\addplot coordinates {";
		cout << "start plotting " << attackresults[i][1] << endl;
		cout << attackresults[i][0] << endl;
		mylog << "%" << attackresults[i][1] << endl;
		double guessingnumber, nextguenum, totalguessingnum;
		//double percentage, nextpercentage;
		double dupguessnum = 0;
		idx = 0;
		int tabidx1, tabidx2;
		linestr = "";
		guessingnumber = 0;
		//percentage = 0;
		G = baseguessingnum;
		hfunc = basehfunc;
		int passguenum = -1;
		string prepwd = "";
		while (getline(fin, linestr)) {
			if (linestr.size() == 0) {
				cout << "idx = " << idx << endl;
				cout << "linestr.size() == 0" << endl;
				continue;
			}
			idx++;
			nextguenum = 0;
			//nextpercentage = 0;
			password = "";
			tabidx1 = linestr.find_first_of('\t');
			tabidx2 = linestr.find_last_of('\t');
			nextguenum = stod(linestr.substr(0, tabidx1 - 0));
			password = linestr.substr(tabidx1 + 1, tabidx2 - tabidx1 - 1);

			//cout << "linestr = " << linestr << endl;
			//cout << "password = " << password << "  nextguenum = " << nextguenum << endl;
			//cin.get();
			//if (idx%100000 == 0)cout << tabidx1 << "  " << tabidx2 << "  " << nextguenum << "  " << password << endl;
			//nextpercentage = stod(linestr.substr(tabidx2 + 1, linestr.size() - tabidx2 - 1));
			linestr = "";
			if (passidxmp.find(password) == passidxmp.end()) {
				cout << "ERROR: passidxmp.find(password) == passidxmp.end()" << endl;
				cout << "password = " << password << endl 
					<< "  linestr = " << linestr 
					<< tabidx1 << "  " << tabidx2 << "  " << nextguenum << "  " << password << endl;
				cin.get();
			}
			if (guessed[passidxmp[password]] == true) {
				if (prepwd != password) dupguessnum++;
				prepwd = password;
				continue;
			}
			prepwd = password;
			//cout << "new password!!" << endl; cin.get();
			if (nextguenum != guessingnumber && guessingnumber - dupguessnum + baseguessingnum >= G) {
				totalguessingnum = guessingnumber - dupguessnum + baseguessingnum;
				gfunc = 0;
				if (output == "lambda_G") gfunc = (double)N / (double)d * (hfunc - t2);
				else if (output == "lambda(S,G)") gfunc = (double)N / (double)d * (hfunc - t2) - t1; // the lowerbound of the number of cracked passwords
				else { cout << "ERROR: output = " << output << endl; cin.get(); }
				percentage_of_guessed_passwords = (double)gfunc / (double)N * 100;
				fout << "(" << totalguessingnum << "," << percentage_of_guessed_passwords << ") ";
				cout << "G = " << G << "  totalguessingnum = " << totalguessingnum << "  hfunc = " << hfunc << "  gfunc = " << gfunc << endl;
				mylog << "G = " << G << "totalguessingnum = " << totalguessingnum << "  hfunc = " << hfunc << "  gfunc = " << gfunc << endl;

				while (G <= totalguessingnum) {
					if (G < maxG && G*2 > maxG) {
						G = maxG;
						break;
					}
					else G = G*2;
				}
				if (G > maxG) break;
			}
			hfunc++;
			guessingnumber = nextguenum;
		}
		//NOTE: till now we haven't plotted the last (guessingnumber, percentage)
		//then plot it
		if (guessingnumber <= maxG) {
			totalguessingnum = guessingnumber - dupguessnum + baseguessingnum;
			gfunc = 0;
			gfunc = (double)N / (double)d * (hfunc - t2) - t1; // the lowerbound of the number of cracked passwords
			percentage_of_guessed_passwords = (double)gfunc / (double)N * 100;
			fout << "(" << totalguessingnum << "," << percentage_of_guessed_passwords << ") ";
			cout << "G = " << G << "  totalguessingnum = " << totalguessingnum << "  hfunc = " << hfunc << "  gfunc = " << gfunc << endl;
			mylog << "G = " << G << "totalguessingnum = " << totalguessingnum << "  hfunc = " << hfunc << "  gfunc = " << gfunc << endl;
		}
		fout << "};" << endl;
		fin.close();
	}
	//cin.get();
	//cin.get();
	fout.close();
	//fout2.close();
	mylog.close();
	return;
}

void recoversamples(string inputfilename, string outputfilename) {
	cout << "recoversamples() start" << endl;
	ifstream fin;
	ofstream fout;
	fin.open(inputfilename);
	fout.open(outputfilename);
	
	int frequency;
	int count;
	string password;

	int N = 0;
	int distinct = 0;
	// A way to list all samples with less space: assign an interval of indices to each distinct password
	// The form of each line:  passwordname firstindex firstindex+frequency-1 
	int begin = 0;
	while (!fin.eof()) {
		frequency = 0;
		count = 0;
		fin >> frequency;
		fin >> count;
		if (count == 0) continue; // means reading the last redundant line
		N += frequency * count;
		for (int i = 1; i <= count; i++) {
			distinct++;
			password = to_string(frequency) + "--" + to_string(i);
			fout << password << " " << begin << " " << begin + frequency - 1 << endl;
			begin += frequency;
		}
	}

	cout << "N = " << N << "  begin = " << begin << "  distinct = " << distinct << endl;

	/*
	//This is the straightforward way to list all samples: assign each distinct password a name, and print it "frequency" times in the output file.
	int N1 = 0, N2 = 0;
	while (!fin.eof()) {
		frequency = 0;
		count = 0;
		fin >> frequency;
		fin >> count;
		N1 += frequency*count;
		if (count == 0) continue; // means reading the last redundant line
		for (int i = 1; i <= count; i++) {
			password = to_string(frequency) + "--" + to_string(i);
			for (int j = 0; j < frequency; j++) {
				fout << password << endl;
				N2++;
			}
		}
	}
	cout << "N1 = " << N1 << "   N2 = " << N2 << endl;
	*/
	fin.close();
	fout.close();
	cout << "recoversamples() end" << endl;
	//cin.get();
	//cin.get();

	return;
}

void recoversamples_shuffled(string dataset) {
	if (datasetfilemap.find(dataset) == datasetfilemap.end()) {
		cout << "ERROR: dataset does not exist!" << endl;
		cin.get();
		exit(-1);
	}
	cout << "recoversamples_shuffled() start" << endl;
	ifstream fin(datasetfilemap[dataset]);
	ofstream fout(dataset+"_samples_shuffled.txt");

	int frequency;
	int count;
	string password;

	int N = 0;
	int distinct = 0;
	vector<pair<string, int>> samples(distinct_map[dataset], { "",0 });
	// A way to list all samples with less space: assign an interval of indices to each distinct password
	// The form of each line:  passwordname firstindex firstindex+frequency-1 
	
	cout << "start reading inputfile" << endl;
	while (!fin.eof()) {
		frequency = 0;
		count = 0;
		fin >> frequency;
		fin >> count;
		if (count == 0) continue; // means reading the last redundant line
		N += frequency * count;
		for (int i = 1; i <= count; i++) {
			password = to_string(frequency) + "--" + to_string(i);
			samples[distinct].first = password;
			samples[distinct].second = frequency;
			distinct++;
		}
	}
	cout << "end reading inputfile" << endl;
	if (N != N_map[dataset]) {
		cout << "ERROR: N != N_map[dataset]" << endl;
		cin.get();
		exit(-1);
	}
	if (distinct != distinct_map[dataset]) {
		cout << "ERROR: distinct != distinct_map[dataset]" << endl;
		cin.get();
		exit(-1);
	}
	cout << "start shufflng samples" << endl;
	unsigned samplesDseed = chrono::system_clock::now().time_since_epoch().count();
	shuffle(samples.begin(), samples.end(), default_random_engine(samplesDseed));
	cout << "end shufflng samples" << endl;

	cout << "start writing to outputfile" << endl;
	int begin = 0;
	for (int i = 0; i < samples.size(); i++) {
		fout << samples[i].first << " " << begin << " " << begin + samples[i].second - 1 << endl;
		begin += samples[i].second;
	}
	
	cout << "end writing to outputfile" << endl;
	cout << "N = " << N << "  begin = " << begin << "  distinct = " << distinct << endl;

	fin.close();
	fout.close();
	cout << "recoversamples_shuffled() end" << endl;
	//cin.get();
	//cin.get();

	return;
}

void testifsamplevalid(string filename) {
	ifstream fin(filename);
	int frequency = 0;
	string password = "";
	string tmp = "";
	int N = 0;
	while (!fin.eof()) {
		fin >> tmp;
		N++;
		if (tmp == "") {
			cout << "tmp = ""  N = " << N << endl;
			continue;
		}
		if (tmp == password) frequency++;
		else {
			if (password == "") {
				frequency = 1;
				password = tmp;
				cout << "password = " << password << endl;
			}
			else {
				int end = password.find("--");
				if (to_string(frequency) != password.substr(0, end)) {
					cout << "ERROR: password = " << password << "  tmp = " << tmp << "  frequency = " << frequency << endl;
					cin.get();
					exit(-1);
				}
				else {
					frequency = 1;
					password = tmp;
					cout << "password = " << password << endl;
				}
			}
		}
	}
	cout << "N = " << N << endl;
	cin.get();
	cin.get();
	return;
}

bool ismorefrequent(vector<int> &a, vector<int> &b) {
	if (a[1] > b[1]) return true;
	else return false;
}

bool ismorefrequent_pair(pair<string, int> &a, pair<string, int> &b) {
	if (a.second > b.second) return true;
	else return false;
}

bool isearlierguessed(pair<string, double> &a, pair<string, double> &b) {
	if (a.second < b.second) return true;
	else return false;
}

bool isPGSstr(string &s) {
	for (int i = 0; i < s.size(); i++) {
		if ((int)s[i] < 32 || (int)s[i] > 126) return false;
	}
	return true;
}

bool hassmallerguessingnumber(pair<string, double> &a, pair<string, double> &b) {
	if (a.second < b.second) return true;
	else return false;
}

int countdistinctpasswords(string inputfilename) {
	cout << "countdistinctpasswords() start" << endl;
	ifstream fin(inputfilename);

	string password;
	int begin, end;
	int distinct = 0;
	int N = 0;
	while (!fin.eof()) {
		password = "";
		begin = end = 0;
		fin >> password >> begin >> end;
		if (password == "") {
			cout << "current distinct = " << distinct << endl;
			continue;
		}
		distinct++;
		N += end - begin + 1;
	}
	cout << "distinct = " << distinct << "  N = " << N << endl;
	cout << "countdistinctpasswords() end" << endl;
	//cin.get();
	return distinct;
}

void countmostfrequentpasswords(string output, vector<string> resourcenames, string foutname, double delta1, bool usePinGlist) {
//////void countmostfrequentpasswords(string output) {
	if (output != "lambda_G" && output != "lambda(S,G)") {
		cout << "ERROR: incorrect input parameter outout = " << output << endl;
		cin.get();
		return;
	}
	//changed on 2023-01-23 set delta1 as an input parameter of this function
	// double delta1 = 0.00009; // 0.01;// 0.05; // 0.00009*5;
	
	cout << "compute the upper bound of the percentage of guessed passwords" << endl;
	
	// vector<string> resourcenames = { "linkedin", "yahoo", "rockyou", "000webhost", "neopets", "bfield", "brazzers", "clixsense" , "csdn" };
	// string outputfilename = output + "-upperboundplots.txt";
	
	// vector<string> resourcenames = { "yahoo10000", "yahoo100000", "yahoo1000000", "yahoo10000000" };
	// string outputfilename = output + "-delta1=" + to_string(delta1) + "-yahoosubsamples-upperboundplots.txt";

	// vector<string> resourcenames = { "PIN4digit-rockyou", "PIN6digit-rockyou" };
	// string outputfilename = output + "-delta1=" + to_string(delta1) + "-PIN-upperboundplots.txt";

	// vector<string> resourcenames = { "yahoo-nonereq", "yahoo-6charmin" };
	// string outputfilename = output + "-delta1=" + to_string(delta1) + "-yahooPCP-upperboundplots.txt";

	// vector<string> resourcenames = { "yahoo-0y", "yahoo-1y", "yahoo-2y", "yahoo-3y", "yahoo-4y", "yahoo-5-10y" };
	// string outputfilename = output + "-delta1=" + to_string(delta1) + "-yahooTenure-upperboundplots.txt";

	// vector<string> resourcenames = { "yahoo-female", "yahoo-male" };
	// string outputfilename = output + "-delta1=" + to_string(delta1) + "-yahooGender-upperboundplots.txt";

	// vector<string> resourcenames = { "yahoo-reset0", "yahoo-reset1", "yahoo-reset_1", "yahoo-resetGeq5" };
	//string outputfilename = output + "-delta1=" + to_string(delta1) + "-yahooReset-upperboundplots.txt";

	string outputfilename = output + "-delta1=" + to_string(delta1) + "-" + foutname + "-upperboundplots.txt";
	
	ofstream fout(outputfilename);
	for (int i = 0; i < resourcenames.size(); i++) {
		string datasetname = resourcenames[i];
		cout << "start computing the upper bounds for " << datasetname << "dataset" << endl;
		string inputfilename;
		//if (datasetname == "000webhost" || datasetname == "neopets") inputfilename = datasetfilemap[datasetname+"-freq"];
		if (datasetfilemap.find(datasetname + "-freq") != datasetfilemap.end()) inputfilename = datasetfilemap[datasetname + "-freq"];
		else inputfilename = datasetfilemap[datasetname];
		ifstream fin(inputfilename);
		int N = N_map[datasetname];
		double epsilon1 = sqrt(-log(delta1) / (2.0*(double)N));
		int distinct = distinct_map[datasetname];
		vector<pair<int, int>> Glist; //for each pair: first element: G second element: count_of_Gmostfrequentpasswords
		int G;
		if (usePinGlist == false) {
			for (int i = 1; i < distinct; i=(i << 1)) {
				Glist.push_back({ i, 0 });
			}
			if (Glist[Glist.size() - 1].first < distinct) Glist.push_back({ distinct,0 });
		}
		else { // for PIN Glist
			int nextG = 1;
			while (nextG < distinct) {
				Glist.push_back({ nextG, 0 });
				nextG = ceil(nextG * pow(10, 0.1));
			}
			Glist.push_back({ distinct,0 });
		}
		
		int frequency, count;
		int totaldistinct = 0;
		int Gidx = 0;
		cout << "start reading file" << endl;
		while (!fin.eof()) {
			frequency = 0;
			count = 0;
			fin >> frequency >> count;
			if (frequency == 0) {
				cout << "frequency == 0" << endl;
				cin.get();
				continue;
			}
			if (totaldistinct + count <= Glist[Gidx].first) {
				Glist[Gidx].second += frequency*count;
			}
			else {
				if (Gidx + 1 >= Glist.size()) {
					cout << "ERROR: G can be greater than the number of distinct passwords!!" << endl;
					cin.get();
					cin.get();
					exit(-1);
				}
				int tmp = Glist[Gidx].first - totaldistinct;
				Glist[Gidx].second += frequency*tmp;
				int lefttmp = tmp;
				while (tmp < count) {
					++Gidx;
					tmp = tmp + min(Glist[Gidx].first - Glist[Gidx - 1].first, count - tmp);
					Glist[Gidx].second = Glist[Gidx - 1].second + (tmp - lefttmp) * frequency;
					lefttmp = tmp;
				}
			}
			totaldistinct += count;
		}
		cout << "end reading file" << endl;
		fout << "%" << datasetname << "; delta1 = " << delta1 << "; epsilon1 = " << epsilon1 << endl;
		fout << "\\addplot coordinates {";
		double percentage_of_Gmostfreqentpasswords;
		for (int i = 0; i < Glist.size(); i++) {
			cout << "Glist[" << i << "] = {" << Glist[i].first << ", " << Glist[i].second << "}" << endl;
			percentage_of_Gmostfreqentpasswords = (double)Glist[i].second / (double)N;
			if (output == "lambda_G") percentage_of_Gmostfreqentpasswords += epsilon1;
			percentage_of_Gmostfreqentpasswords *= 100;
			fout << "(" << Glist[i].first << "," << percentage_of_Gmostfreqentpasswords << ") ";
		}
		fout << "};" << endl;
		cout << "end computing the upper bounds for " << datasetname << "dataset" << endl;
	}
	fout.close();
	//cin.get();
	//cin.get();
	return;
}

void countmostfrequentpasswords2() {
	cout << "compute the upper bound of the percentage of guessed passwords" << endl;
	vector<string> resourcenames = { "linkedinsmall"};
	string outputfilename = "linkedinsmall_upperboundplots.txt";
	
	ofstream fout(outputfilename);
	for (int i = 0; i < resourcenames.size(); i++) {
		string datasetname = resourcenames[i];
		cout << "start computing the upper bounds for " << datasetname << "dataset" << endl;
		string inputfilename = datasetfilemap[datasetname];
		ifstream fin(inputfilename);
		int N = N_map[datasetname];
		int distinct = distinct_map[datasetname];
		vector<pair<int, int>> Glist; //for each pair: first element: G second element: count_of_Gmostfrequentpasswords
		int G;
		for (int i = 1; i < distinct; i = (i << 1)) {
			Glist.push_back({ i, 0 });
		}
		if (Glist[Glist.size() - 1].first < distinct) Glist.push_back({ distinct,0 });
		int frequency, count;
		int totaldistinct = 0;
		int Gidx = 0;
		string linestr = "";
		stringstream ss;
		string tmpstr = "";
		cout << "start reading file" << endl;
		while (getline(fin, linestr)) {
			if (linestr.size() == 0) {
				cout << "totaldistinct = " << totaldistinct << endl;
				cout << "linestr.size() == 0" << endl;
				continue;
			}
			frequency = 0;
			tmpstr = "";
			ss << linestr;
			ss >> frequency;
			ss.clear();
			ss.str("");
			linestr = "";
			if (frequency == 0) {
				cout << "frequency == 0" << endl;
				continue;
			}
			if (totaldistinct + 1 < Glist[Gidx].first) {
				Glist[Gidx].second += frequency;
			}
			else if (totaldistinct + 1 == Glist[Gidx].first) {
				Glist[Gidx].second += frequency;
				if (totaldistinct + 1 < distinct) {
					++Gidx;
					Glist[Gidx].second = Glist[Gidx - 1].second + frequency;
				}
			}
			else {
				//if (Gidx + 1 >= Glist.size()) {
					//cout << "ERROR: G can be greater than the number of distinct passwords!!" << endl;
					cout << "ERROR: totaldistinct + 1 > Glist[Gidx].first!!" << endl;
					cin.get();
					cin.get();
					exit(-1);
				//}
			}
			totaldistinct++;
		}
		cout << "end reading file" << endl;
		fout << "%" << datasetname << endl;
		fout << "\\addplot coordinates {";
		double percentage_of_Gmostfreqentpasswords;
		for (int i = 0; i < Glist.size(); i++) {
			cout << "Glist[" << i << "] = {" << Glist[i].first << ", " << Glist[i].second << "}" << endl;
			percentage_of_Gmostfreqentpasswords = (double)Glist[i].second / (double)N * 100;
			fout << "(" << Glist[i].first << "," << percentage_of_Gmostfreqentpasswords << ") ";
		}
		fout << "};" << endl;
		cout << "end computing the upper bounds for " << datasetname << "dataset";
	}
	fout.close();
	cin.get();
	cin.get();
	return;
}

void experiment_plotguessingcurves2(string dname) {
	string datasetname;
	if (dname == "rockyou") { datasetname = "myrockyou"; }
	else { datasetname = dname; }
	// ofstream fout(datasetname + "_existingresults_plots.txt");
	ofstream fout(datasetname + "_mingussingnumber_plots.txt");

	string prefix;
	vector<vector<string>> attackresults;

	if (dname == "rockyou") {
		prefix = "D:/Purdue/CS590 PWD/dataset/myrockyou/attackresults/rockyou25kresults_";
		attackresults = {
			{ prefix + "Hashcat_wordlist-best64-generated2.txt", "Hashcat: wordlist-best64-generated2" },
			{ prefix + "Markov_wordlist-order5-smoothed.txt", "Markov: wordlist-order5-smoothed" },
			{ prefix + "PCFG_wordlist-2015.txt", "PCFG: wordlist-2015" },
			{ prefix + "NN_neural.txt", "Neural Network: neural" },
		};
	}
	else {
		prefix = "D:/Purdue/CS590 PWD/dataset/Datasets-master/smaller datasets/monte/" + datasetname + "/" + datasetname;
		attackresults = {
			/*
			{ prefix + "_perfect_result.txt", "Perfect Knowledge" },
			{ prefix + "_4gram_result.txt", "Markov: 4-gram" },
			{ prefix + "_backoff_result.txt", "Markov: Backoff" },
			{ prefix + "_omen_result.txt", "Markov: OMEN" },
			{ prefix + "_jtr_result.txt", "JtR: Original" },
			{ prefix + "_jtr_opt_result.txt", "JtR: Reordered" },
			{ prefix + "_jtr_extended_opt_result.txt", "JtR: Extended" },
			{ prefix + "_hc_extended_result.txt", "Hashcat: Extended" },
			{ prefix + "_hc_result.txt", "Hashcat" },
			{ prefix + "_pcfg_result.txt", "PCFG: 2009" },
			{ prefix + "_saranga_result.txt", "PCFG: 2016" },
			{ prefix + "_rnn_result.txt", "Neural Network" },
			*/
			{ "D:/Purdue/CS590 PWD/PasswordResults/PasswordResults/" + datasetname + "_minguessingnumber.txt", "MinGuessingNumber" },
		};
	}

	int distinct;
	if (dname == "rockyou") distinct = distinct_map["rockyou"];
	else distinct = distinct_map[datasetname];

	fout << "%1 <= G <= distinct = " << distinct << endl;
	for (int i = 0; i < attackresults.size(); i++) {
		ifstream fin(attackresults[i][0]);
		fout << "%" << attackresults[i][1] << endl;
		fout << "%" << attackresults[i][0] << endl;
		fout << "\\addplot coordinates {";
		cout << "start plotting " << attackresults[i][1] << endl;
		cout << attackresults[i][0] << endl;
		double guessingnumber, nextguenum;
		double percentage, nextpercentage;
		int idx = 0;
		string linestr = "";
		stringstream ss;
		string tmpstr = "";
		guessingnumber = 0;
		percentage = 0;
		long long G = 1;
		double xaxis_max;
		//xaxis_max = distinct; //only consider G <= distinct
		xaxis_max = pow(10, 16);
		while (getline(fin, linestr)) {
			if (linestr.size() == 0) {
				cout << "idx = " << idx << endl;
				cout << "linestr.size() == 0" << endl;
				continue;
			}
			nextguenum = 0;
			nextpercentage = 0;
			tmpstr = "";
			ss << linestr;
			ss >> nextguenum;
			while (ss >> tmpstr) {};
			nextpercentage = stod(tmpstr);
			ss.clear();
			ss.str("");
			linestr = "";
			if (nextguenum != guessingnumber && guessingnumber >= G) {
				fout << "(" << guessingnumber << "," << percentage << ") ";
				cout << "G = " << G << "  guessingnumber = " << guessingnumber << "  percentage = " << percentage << endl;
				  
				while (G <= guessingnumber) {
					if (G < xaxis_max && (G << 1) > xaxis_max) {
						G = xaxis_max;
						break;
					}
					else G = (G << 1);
				}
				if (G > xaxis_max) break;
				
				while (G <= guessingnumber) G = (G << 1);
			}
			guessingnumber = nextguenum;
			percentage = nextpercentage;
		}
		//NOTE: till now we haven't plotted the last (guessingnumber, percentage)
		//then plot it
		if (guessingnumber <= xaxis_max) { 
			fout << "(" << guessingnumber << "," << percentage << ") ";
			cout << "G = " << G << "  guessingnumber = " << guessingnumber << "  percentage = " << percentage << endl;
		}
		
		fout << "};" << endl;
		fin.close();
	}
	fout.close();
	//cin.get();
	return;
}

void experiment_editdistance(string dname) {
	string datasetname = dname; // "000webhost"; //"neopets";

	unordered_map<string, int> unique_map;
	unique_map["000webhost"] = 9006529;
	unique_map["neopets"] = 21509860;

	string inputfilename = datasetfilemap[datasetname];
	string outputfilename = "./editdistanceresult/" + datasetname + "-editdistance=1.txt";
	//string outputfilename = "./editdistanceresult/" + datasetname + "appendnumfrom0to99.txt";
	ifstream fin_all(inputfilename);
	ofstream fout(outputfilename);
	int N = 0; // N_map[datasetname];
	int distinct = distinct_map[datasetname];

	int unique = unique_map[datasetname];

	vector<string> learningset(distinct-unique, "");
	unordered_set<string> searchlearningset;
	unordered_set<string> testingset;

	string password = "";
	int count = 0;
	string linestr = "";
	N = 0;
	int idx = 0;
	cout << "start reading " << inputfilename << endl;

	while (getline(fin_all, linestr)) {
		if (linestr.size() == 0) {
			cout << "idx = " << idx << endl;
			cout << "fin_all  linestr.size() == 0" << endl;
			cin.get();
			continue;
		}
		password = "";
		count = 0;
		int tmpidx1 = 0, tmpidx2 = 0;
		while (tmpidx1 < linestr.size() && linestr[tmpidx1] == ' ') tmpidx1++;
		if (tmpidx1 == linestr.size()) {
			cout << "idx = " << idx << endl;
			cout << "fin_all  tmpidx1 == linestr.size()" << endl;
			cin.get();
			continue;
		}
		tmpidx2 = tmpidx1;
		while (tmpidx2 < linestr.size() && linestr[tmpidx2] != ' ') tmpidx2++;
		count = stoi(linestr.substr(tmpidx1, tmpidx2 - tmpidx1));
		password = linestr.substr(tmpidx2 + 1);

		if (count > 1) {
			learningset[idx] = password;
			searchlearningset.insert(password);
		}
		else testingset.insert(password);

		N += count;
		idx++;
		linestr = "";
	}
	cout << "end reading " << inputfilename << endl;

	int guessingnumber = 0;
	int guessedcount = 0;
	string guessingpass = "";
	int repeat = 0;
	cout << "start guessing " << endl;
	for (int i = 0; i < learningset.size(); i++) {
		
		//remove 1 character
		repeat = 0;
		for (int j = 0; j < learningset[i].size(); j++) {
			guessingpass = "";
			guessingpass = learningset[i].substr(0, j) + learningset[i].substr(j + 1, learningset[i].size() - j - 1);
			if (searchlearningset.find(guessingpass) != searchlearningset.end()) {
				repeat++;
				continue;
			}
			else if (testingset.find(guessingpass) != testingset.end()) {
				guessedcount++;
				//cout << "guessingpass = " << guessingpass << "  learningset[i] = " << learningset[i] << endl;
				testingset.erase(guessingpass);
			}
		}
		guessingnumber += (learningset[i].size() - repeat);

		//add 1 character
		repeat = 0;
		for (int j = 0; j < learningset[i].size()+1; j++) {
			for (int k = 32; k <= 126; k++) { //ASCII code
				guessingpass = "";
				guessingpass = learningset[i].substr(0, j) + (char)k;
				if (j < learningset[i].size()) guessingpass += learningset[i].substr(j, learningset[i].size()-j);
				if (searchlearningset.find(guessingpass) != searchlearningset.end()) {
					repeat++;
					continue;
				}
				else if (testingset.find(guessingpass) != testingset.end()) {
					guessedcount++;
					//cout << "guessingpass = " << guessingpass << "  learningset[i] = " << learningset[i] << endl;
					testingset.erase(guessingpass);
				}
			}
		}
		guessingnumber += ((learningset[i].size()+1)*(126-32+1) - repeat);
		
		/*
		//append a number from 0~99
		repeat = 0;
		for (int j = 0; j < 99; j++) {
			guessingpass = "";
			guessingpass = learningset[i] + to_string(j);
			if (searchlearningset.find(guessingpass) != searchlearningset.end()) {
				repeat++;
				continue;
			}
			else if (testingset.find(guessingpass) != testingset.end()) {
				guessedcount++;
				//cout << "guessingpass = " << guessingpass << "  learningset[i] = " << learningset[i] << endl;
				testingset.erase(guessingpass);
			}
		}
		guessingnumber += (99 - repeat);
		*/
		if (i % 100000 == 0) {
			cout << "guessingnumber = " << guessingnumber << "   guessedcount = " << guessedcount
				<< "   %guessed = " << guessedcount / (double)N * 100.0 << endl;
			fout << "guessingnumber = " << guessingnumber << "   guessedcount = " << guessedcount
				<< "   %guessed = " << guessedcount / (double)N * 100.0 << endl;
		}
	}
	cout << "end guessing" << endl;
	cout << "guessingnumber = " << guessingnumber << "   %guessed = " << guessedcount / (double)N * 100.0 << endl;
	fout << "end guessing" << endl;
	fout << "guessingnumber = " << guessingnumber << "   %guessed = " << guessedcount / (double)N * 100.0 << endl;
	//cin.get();
	//cin.get();
	fin_all.close();
	fout.close();
	return;
}

void experiment_plotunseenguessingcurves() {
	//vector<string> rnames = { "rockyou_min", "rockyou_max", "yahoo_min", "yahoo_max", "linkedin_min", "linkedin_max" };
	vector<string> rnames = { "yahootest" };
	//string outputfilename = "./unseenestimationplots.txt";
	string outputfilename = "./unseentestplot.txt";
	ofstream fout(outputfilename);
	for (int i = 0; i < rnames.size(); i++) {
		string resultname = rnames[i];
		string datasetname = resultname.substr(0, resultname.size() - 4);

		string inputfilename = "D:/Purdue/Research/Password Reseach/unseencode/" + resultname + "result.txt";
		
		ifstream fin(inputfilename);
		long N = N_map[datasetname];
		vector<double> xscale = { 1,2,5 };
		vector<double> xpoints;
		for (double j = 1; j < N; j = j * 10.0) {
			for (int k = 0; k < xscale.size(); k++) {
				if (j*xscale[k] > N) break;
				else xpoints.push_back(j*xscale[k]);
			}
		}
		for (double j = N; j < pow(10.0, 17.0); j = j * 10.0) {
			for (int k = 0; k < xscale.size(); k++) {
				if (j*xscale[k] > pow(10.0, 17.0)) break;
				else xpoints.push_back(j*xscale[k]);
			}
		}
		double probability = 0.0;
		double count = 0;
		cout << "start reading " << inputfilename << endl;
		double G = 0;
		double rate = 0.0;
		int idx = 0;
		int xi = 0;
		fout << "%unseen estimation " << resultname << endl;
		fout << "\\addplot coordinates { (0,0) ";
		while (!fin.eof()) {
			probability = 0.0;
			count = 0;
			fin >> count;
			fin >> probability;
			if (count == 0) {
				cout << "count == 0" << endl;
				continue;
			}

			while (G + count >= xpoints[xi]) {
				double tmp = xpoints[xi] - G;
				G += tmp;
				rate += tmp*probability;
				fout << "(" << G << ", " << rate * 100 << ") ";
				cout << "(" << G << ", " << rate * 100 << ") " << "probability = " << probability << endl;
				xi++;
				count -= tmp;
				if (xi >= xpoints.size()) break;
			}
			G += count;
			rate += count*probability;

			if (xi >= xpoints.size()) break;
			/*
			if (idx % 100 == 0 || count > 10000) {
				fout << "(" << G << ", " << rate * 100 << ") ";
			}
			*/
			idx++;
		}
		fout << "(" << G << ", " << rate * 100 << ") ";
		fout << "};" << endl;
		cout << "end reading " << inputfilename << endl;
		fin.close();
	}
	fout.close();
	return;
}

void minguessingnumber() {
	string datasetname = "000webhost";
	// "000webhost", "neopets", "bfield", "brazzers", "clixsense", "csdn"
	// unordered_map<string, int> distinct_25k_map;
	// distinct_25k_map["000webhost"] = 24304;
	// distinct_25k_map["neopets"] = 24116;

	string inputtestfilename = "D:/Purdue/CS590 PWD/dataset/Jeremiah/datasets/" + datasetname + "25k.withcount";
	ifstream fin_test(inputtestfilename);

	int distinct_25k = distinct_25k_map[datasetname];

	unordered_map<string, int> testsetmp;
	string password = "";
	int count = 0;
	int N_test = 0;
	int totalnum_test = 0;
	cout << "start reading " << inputtestfilename << endl;

	string linestr = "";

	while (getline(fin_test, linestr)) {
		if (linestr.size() == 0) {
			cout << "totalnum_test = " << totalnum_test << endl;
			cout << "fin_test  linestr.size() == 0" << endl;
			cin.get();
			continue;
		}
		password = "";
		count = 0;
		int tmpidx1 = 0, tmpidx2 = 0;
		while (tmpidx1 < linestr.size() && linestr[tmpidx1] == ' ') tmpidx1++;
		if (tmpidx1 == linestr.size()) {
			cout << "totalnum_test = " << totalnum_test << endl;
			cout << "fin_test  tmpidx1 == linestr.size()" << endl;
			cin.get();
			continue;
		}
		tmpidx2 = tmpidx1;
		while (tmpidx2 < linestr.size() && linestr[tmpidx2] != ' ') tmpidx2++;
		count = stoi(linestr.substr(tmpidx1, tmpidx2 - tmpidx1));
		password = linestr.substr(tmpidx2 + 1);
		linestr = "";
		totalnum_test++;
		N_test += count;
		testsetmp[password] = count;
	}

	cout << "end reading " << inputtestfilename << endl;
	cout << "N_test = " << N_test << "  totalnum_test = " << totalnum_test << endl;




	ofstream fout(datasetname + "_minguessingnumber.txt");
	//ofstream fout(datasetname + "_minguessingnumber-markov4gram-rnn-pcfg2009.txt");
	//ofstream fout(datasetname + "_minguessingnumber-markov4gram-rnn.txt");
	string prefix = "D:/Purdue/CS590 PWD/dataset/Datasets-master/smaller datasets/monte/" + datasetname + "/" + datasetname;
	vector<vector<string>> attackresults = {
		//{ prefix + "_perfect_result.txt", "Perfect Knowledge" },
		{ prefix + "_4gram_result.txt", "Markov: 4-gram" },
		// { prefix + "_backoff_result.txt", "Markov: Backoff" },
		// { prefix + "_omen_result.txt", "Markov: OMEN" },
		// { prefix + "_jtr_result.txt", "JtR: Original" },
		// { prefix + "_jtr_opt_result.txt", "JtR: Reordered" },
		{ prefix + "_jtr_extended_opt_result.txt", "JtR: Extended" },
		// { prefix + "_hc_extended_result.txt", "Hashcat: Extended" },
		{ prefix + "_hc_result.txt", "Hashcat" },
		{ prefix + "_pcfg_result.txt", "PCFG: 2009" },
		// { prefix + "_saranga_result.txt", "PCFG: 2016" },
		{ prefix + "_rnn_result.txt", "Neural Network" }
	};
	unordered_map<string, double> minguessingnumber;
	for (int i = 0; i < attackresults.size(); i++) {
		ifstream fin(attackresults[i][0]);
		cout << "start scanning " << attackresults[i][1] << endl;
		cout << attackresults[i][0] << endl;
		double guessingnumber, nextguenum;
		double percentage, nextpercentage;
		int idx = 0;
		linestr = "";
		guessingnumber = 0;
		percentage = 0;
		double xaxis_max;
		int tabidx1, tabidx2;
		string password = "";
		//xaxis_max = distinct; //only consider G <= distinct
		xaxis_max = pow(10, 16);
		while (getline(fin, linestr)) {
			if (linestr.size() == 0) {
				cout << "idx = " << idx << endl;
				cout << "linestr.size() == 0" << endl;
				continue;
			}
			nextguenum = 0;
			nextpercentage = 0;
			tabidx1 = linestr.find_first_of('\t');
			tabidx2 = linestr.find_last_of('\t');
			nextguenum = stod(linestr.substr(0, tabidx1 - 0));
			password = linestr.substr(tabidx1 + 1, tabidx2 - tabidx1 - 1);
			nextpercentage = stod(linestr.substr(tabidx2 + 1, linestr.size() - tabidx2 - 1));
			linestr = "";

			if (minguessingnumber.find(password) == minguessingnumber.end() || (minguessingnumber[password] > nextguenum)) {
				minguessingnumber[password] = nextguenum;
			}
				
			/*
			if (nextguenum != guessingnumber && guessingnumber >= G) {
				fout << "(" << guessingnumber << "," << percentage << ") ";
				cout << "G = " << G << "  guessingnumber = " << guessingnumber << "  percentage = " << percentage << endl;

				while (G <= guessingnumber) {
					if (G < xaxis_max && (G << 1) > xaxis_max) {
						G = xaxis_max;
						break;
					}
					else G = (G << 1);
				}
				if (G > xaxis_max) break;

				while (G <= guessingnumber) G = (G << 1);
			}
			
			guessingnumber = nextguenum;
			percentage = nextpercentage;
			*/
		}
		fin.close();
	}
	vector<pair<string, double>> passlistmin(distinct_25k, { "",-1 });
	int idx1 = 0;
	for (auto &v : minguessingnumber) {
		if (idx1 >= distinct_25k) {
			cout << "ERROR: idx1++ >= distinct_25k" << endl;
			cout << "idx1 = " << idx1 << "  distinct_25k = " << distinct_25k
				<< "  minguessingnumber.size() = " << minguessingnumber.size() << endl;
			cin.get();
		}
		passlistmin[idx1].first = v.first;
		passlistmin[idx1].second = v.second;
		idx1++;
	}

	sort(passlistmin.begin(), passlistmin.end(), hassmallerguessingnumber);
	double curpercentage = 0.0;
	double curcrackednum = 0;
	for (int i = 0; i < passlistmin.size(); i++) {
		for (int j = 0; j < testsetmp[passlistmin[i].first]; j++) {
			curcrackednum++;
			curpercentage = curcrackednum * 100 / 25000;
			fout << passlistmin[i].second << "\t" << passlistmin[i].first << "\t" << curpercentage << endl;
		}
	}

	fout.close();
	fin_test.close();
	cin.get();
	return;
}


void basicinfo(string dname) {
	// ifstream fin("D:/Purdue/CS590 PWD/dataset/my_rockyouFreq.txt");
	// ifstream fin(datasetfilemap["yahoo10000000"]);
	// ifstream fin("D:/Purdue/CS590 PWD/dataset/yahoo_password_frequencies_corpus/yahoo-reg-basic-v2.txt");
	ifstream fin(datasetfilemap[dname]);

	long long N = 0;
	long long distinct = 0;



	long frequency, count;
	while (!fin.eof()) {
		frequency = 0;
		count = 0;
		fin >> frequency;
		fin >> count;
		//cout << frequency << endl;
		//cout << count << endl;
		if ((N + frequency * count) < 0 || (N + frequency * count) < N) {
			cout << "Error: the value of N exceeds the maximum value of a long interger!!!" << endl;
			cin.get();
		}
		N += frequency * count;
		distinct += count;
	}
	cout << "N = " << N << "   distinct = " << distinct << endl;
}


void subsample(string dname, int d) {
	if (dname != "rockyou") {
		cout << "ERROR: dataset not available!" << endl;
		cin.get();
	}
	ifstream fin("D:/Purdue/CS590 PWD/dataset/myrockyou/my_rockyou-withcount.txt");
	ofstream fout_withcount("D:/Purdue/CS590 PWD/dataset/myrockyou/rockyou" + to_string(d) + ".txt");
	ofstream fout_withoutcount("D:/Purdue/CS590 PWD/dataset/myrockyou/rockyou" + to_string(d) + "_withoutcount.txt");

	int N = N_map["rockyou"];
	int distinct = distinct_map["rockyou"];
	int seed = 123456;
	default_random_engine e(seed);
	uniform_int_distribution<unsigned> u1(0, N - 1);
	vector<bool> samplelist(N, false);
	int randidx;
	cout << "start generating d different random indices" << endl;
	for (int i = 0; i < d; i++) {
		randidx = u1(e);
		while (samplelist[randidx] == true) randidx = u1(e);
		samplelist[randidx] = true;
		if (randidx >= N-5) {
			cout << "randidx >= N-5   randidx = " << randidx << endl;
			cin.get();
		}
	}
	////////////subsample extra passwords//////////////////////
	int idx_extraPGS = 0;
	int total_extraPGS = 20;
	vector<pair<string, int>> extraPGSpwd(total_extraPGS, pair<string, int>("", 0));
	vector<bool> samplelist_extraPGS(N, false); //subsample extra 16 passwords that satisfy PGS requirement
	vector<int> randpwd_idx(total_extraPGS, -1);
	for (int i = 0; i < total_extraPGS; i++) {
		randidx = u1(e);
		while (samplelist[randidx] == true || samplelist_extraPGS[randidx]) randidx = u1(e);
		samplelist_extraPGS[randidx] = true;
		randpwd_idx[i] = randidx;
		if (randidx >= N - 5) {
			cout << "randidx >= N-5   randidx = " << randidx << endl;
			cin.get();
		}
	}
	////////////end subsample extra passwords//////////////////////
	cout << "end generating d different random indices" << endl;


	//vector<pair<string, int>> SminusD(distinct, pair<string,int>("", 0));
	//for (int i = 0; i < distinct; i++) SminusD[i][0] = i;
	//vector<int> Dset(distinct, 0);
	vector<pair<string, int>> Dset(distinct, pair<string, int>("", 0));

	string linestr = "";
	string password = "";
	int count = 0;
	int startidx = 0;
	int idx = 0;
	int tmp_N = 0;
	cout << "start constructing set D" << endl;
	
	int tmpcounttest = 0;
	while (getline(fin, linestr)) {
		if (linestr.size() == 0) {
			cout << "idx = " << idx << endl;
			cout << "fin  linestr.size() == 0" << endl;
			cin.get();
			continue;
		}
		password = "";
		count = 0;
		int tmpidx1 = 0, tmpidx2 = 0;
		while (tmpidx1 < linestr.size() && linestr[tmpidx1] == ' ') tmpidx1++;
		if (tmpidx1 == linestr.size()) {
			cout << "idx = " << idx << endl;
			cout << "fin  tmpidx1 == linestr.size()" << endl;
			cin.get();
			continue;
		}
		tmpidx2 = tmpidx1;
		while (tmpidx2 < linestr.size() && linestr[tmpidx2] != ' ') tmpidx2++;
		count = stoi(linestr.substr(tmpidx1, tmpidx2 - tmpidx1));
		password = linestr.substr(tmpidx2 + 1);

		Dset[idx].first = password;
		for (int i = startidx; i < startidx + count; i++) {
			if (samplelist[i] == true) Dset[idx].second++;
		}
		////////////subsample extra passwords//////////////////////
		for (int i = startidx; i < startidx + count; i++) {
			if (samplelist_extraPGS[i] == true) {
				extraPGSpwd[idx_extraPGS].first = password;
				extraPGSpwd[idx_extraPGS].second = i;
				idx_extraPGS++;
			}
		}
		////////////end subsample extra passwords//////////////////////
		startidx += count;
		tmp_N += count;
		idx++;
		linestr = "";
	}
	cout << "tmp_N = " << tmp_N << "  N = " << N << endl;
	if (tmp_N != N) {
		cout << "ERROR: tmp_N != N" << endl;
		cin.get();
	}
	cout << "end constructing set D "<< endl;

	////////////subsample extra passwords//////////////////////
	ofstream fout_extraPGS("D:/Purdue/CS590 PWD/dataset/myrockyou/rockyou_extraPGS.txt");
	for (int i = 0; i < total_extraPGS; i++) {
		fout_extraPGS << randpwd_idx[i] << "  ";
	}
	fout_extraPGS << endl;
	for (int i = 0; i < total_extraPGS; i++) {
		fout_extraPGS << extraPGSpwd[i].second << " " << extraPGSpwd[i].first << endl;
	}
	fout_extraPGS.close();
	////////////end subsample extra passwords//////////////////////

	cout << "start sorting Dset" << endl;
	sort(Dset.begin(), Dset.end(), ismorefrequent_pair);
	cout << "end sorting Dset" << endl;

	int nonPGSdistinct = 0;
	int nonPGStotal = 0;
	int distinct_d = 0;
	for (int i = 0; i < Dset.size(); i++) {
		if (Dset[i].second > 0) {
			distinct_d++;
			fout_withoutcount << Dset[i].first << "\n";
			fout_withcount << Dset[i].second << " " << Dset[i].first << "\n";
			if (!isPGSstr(Dset[i].first)) {
				nonPGSdistinct++;
				nonPGStotal += Dset[i].second;
			}
		}
	}
	cout << "d = " << d << "  distinct_d = " << distinct_d << endl;
	cout << "nonPGSdistinct = " << nonPGSdistinct << "  nonPGStotal = " << nonPGStotal << endl;
	cout << "nonPGSdistinct/distinct_d = " << (double)nonPGSdistinct / (double)distinct_d * 100 
		<< "%  nonPGStotal/d = " << (double)nonPGStotal / (double)d * 100 << "%" << endl;
	fout_withoutcount.close();
	fout_withcount.close();
}

void countPGSpasswords() {
	string dname = "rockyou";
	//ifstream fin("D:/Purdue/CS590 PWD/dataset/myrockyou/my_rockyou-withcount.txt");
	ifstream fin("D:/Purdue/CS590 PWD/dataset/myrockyou/rockyou25k.txt");
	int N; // = N_map[dname];
	int distinct; // = distinct_map[dname];
	int nonPGSdistinct = 0;
	int nonPGStotal = 0;


	int tmp_N = 0;
	int tmp_distinct = 0;
	string linestr = "";
	string password = "";
	int count = 0;
	int idx = 0;
	while (getline(fin, linestr)) {
		if (linestr.size() == 0) {
			cout << "idx = " << idx << endl;
			cout << "fin  linestr.size() == 0" << endl;
			cin.get();
			continue;
		}
		password = "";
		count = 0;
		int tmpidx1 = 0, tmpidx2 = 0;
		while (tmpidx1 < linestr.size() && linestr[tmpidx1] == ' ') tmpidx1++;
		if (tmpidx1 == linestr.size()) {
			cout << "idx = " << idx << endl;
			cout << "fin  tmpidx1 == linestr.size()" << endl;
			cin.get();
			continue;
		}
		tmpidx2 = tmpidx1;
		while (tmpidx2 < linestr.size() && linestr[tmpidx2] != ' ') tmpidx2++;
		count = stoi(linestr.substr(tmpidx1, tmpidx2 - tmpidx1));

		password = linestr.substr(tmpidx2 + 1);

		if (!isPGSstr(password)) {
			nonPGSdistinct++;
			nonPGStotal += count;
			//cout << password << endl;
			cout << idx+1 << "  " << linestr << endl;
		}

		tmp_N += count;
		idx++;
		tmp_distinct++;
		linestr = "";
	}
	/*
	cout << "tmp_N = " << tmp_N << "  N = " << N << "  tmp_distinct = " << tmp_distinct << "  distinct = " << distinct << endl;
	if (tmp_N != N || tmp_distinct != distinct) {
		cout << "ERROR: tmp_N != N || tmp_distinct != distinct" << endl;
		cin.get();
	}
	*/
	N = tmp_N;
	distinct = tmp_distinct;
	cout << "N = " << N << "  distinct = " << distinct << endl;
	cout << "number of passwords that do not sastify PGS's requirement:" << endl;
	cout << "nonPGSdistinct = " << nonPGSdistinct << "  nonPGStotal = " << nonPGStotal << endl;
	cout << "nonPGSdistinct/distinct = " << (double)nonPGSdistinct / (double)distinct * 100 << "%  nonPGStotal/N = " << (double)nonPGStotal / (double)N * 100 << "%" << endl;
}


void CDFzipflaw() {
	double y = 0.037433;
	double r = 0.187227;
	//y = 0.0374; r = 0.1872; //rockyou
	//y = 0.03315; r = 0.1811; //yahoo
	//y = 0.0059; r = 0.2816; //000webhost
	//y = 0.0103; r = 0.2949; //bfield
	//y = 0.0588; r = 0.1486; //CSDN

	//y = 0.037433; r = 0.187227; //rockyou
	//y = 0.03315; r = 0.1811; //yahoo
	//y = 0.005858; r = 0.281557; //000webhost
	//y = 0.010298; r = 0.294932; //bfield
	y = 0.058799; r = 0.148573; //CSDN

	double lambda_t = -1;
	string dname = "csdn"; // "bfield"; // "000webhost"; // "rockyou";  //"yahoo";
	ofstream fout("CDFzipf-" + dname + ".txt");
	fout << "%" << dname << ",  CDFzipf: " << "y = " << y << "  r = " << r << endl;
	fout << "\\addplot coordinates {";
	for (long long t = 1; t < pow(10, 16); t = t * 2) {
		lambda_t = y*pow(t, r);
		fout << " (" << t << ", " << lambda_t * 100 << ") ";
		if (lambda_t > 1) break;
	}
	fout << "};";
	fout.close();
}

void subsample_frequencypair(string dname, long Nsub) {
	ifstream fin(datasetfilemap[dname]);
	ofstream fout(dname + "_subsample_size=" + to_string(Nsub) + ".txt");
	int N = N_map[dname];
	if (Nsub >= N) {
		cout << "ERROR: Nsub >= N" << endl;
		cin.get();
		return;
	}
	if (Nsub <= 0) {
		cout << "ERROR: Nsub <= 0" << endl;
		cin.get();
		return;
	}
	int seed = 123456;
	default_random_engine e(seed);
	uniform_int_distribution<unsigned> u1(0, N - 1);
	vector<bool> samplelist(N, false);
	int randidx;
	cout << "start generating Nsub = " << Nsub << " different random indices" << endl;
	for (int i = 0; i < Nsub; i++) {
		randidx = u1(e);
		while (samplelist[randidx] == true) randidx = u1(e);
		samplelist[randidx] = true;
	}
	cout << "end generating Nsub different random indices" << endl;

	cout << "start constructing subsample set" << endl;
	long frequency, count, sample_count;
	long curidx = 0;
	vector<long> freq_count(N+1, 0); //index: frequency, value: count
	long tmp = -1;
	while (!fin.eof()) {
		frequency = 0;
		count = 0;
		fin >> frequency;
		fin >> count;
		if (tmp == frequency) {
			cout << "tmp = " << tmp << "  frequency = " << frequency << endl;
			cin.get();
		}
		for (int i = 0; i < count; i++) {
			sample_count = 0;
			for (int j = curidx; j < curidx + frequency; j++) {
				if (samplelist[j]) { sample_count++; }
			}
			curidx += frequency;
			freq_count[sample_count]++;
		}
		tmp = frequency;
	}
	cout << "end constructing subsample set" << endl;
	cout << "start writing subsample set to file" << endl;
	long count_check = 0;
	for (int i = N; i >= 1; i--) {
		if (freq_count[i] > 0) {
			fout << i << " " << freq_count[i] << endl;
			count_check += i*freq_count[i];
		}
	}
	if (count_check == Nsub) {
		cout << "count_check == Nsub == " << count_check << endl;
	}
	else {
		cout << "ERROR: count_check != Nsub, count_check = " << count_check << "  Nsub = " << Nsub << endl;
		cin.get();
		return;
	}
	cout << "end writing subsample set to file" << endl;
	return;
}

void perfectknowledgeattack() {
		ofstream fout("./mytest.txt");
		string datasetname = "clixsense_test";
		cout << "start computing the upper bounds for " << datasetname << "dataset" << endl;
		ifstream fin_test("C:/Users/ms_green/Desktop/baiattack/clixsense_test.csv");
		ifstream fin_full(datasetfilemap["clixsense"]);
		string line;
		int N_test = 25000;
		int distinct_test = 23721;
		int frequency, count;
		string linestr = "";
		unordered_map<string, int> testlist;
		string tmpstr = "";

		cout << "start reading test file" << endl;
		while (getline(fin_test, linestr)) {
			frequency = 0;
			tmpstr = "";
			if (linestr == "") {
				cout << "linestr is empty" << endl;
				cin.get();
				continue;
			}
			istringstream readstr(linestr);
			getline(readstr, tmpstr, '\t');
			string strfreq = "";
			getline(readstr, strfreq, '\t');
			frequency = stod(strfreq);
			testlist[tmpstr] = frequency;
		}
		cout << "end reading test file" << endl;

		long G = 1;
		long guessed = 0;
		long distinct = distinct_map["clixsense"];
		vector<pair<int, int>> Glist; //for each pair: first element: G second element: count_of_Gmostfrequentpasswords
		for (int i = 1; i < distinct; i = (i << 1)) {
			Glist.push_back({ i, 0 });
		}
		if (Glist[Glist.size() - 1].first < distinct) Glist.push_back({ distinct,0 });
		long Gidx = 0;
		cout << "start reading full file" << endl;
		while (getline(fin_full, linestr)) {
			frequency = 0;
			tmpstr = "";
			if (linestr == "") {
				cout << "linestr is empty" << endl;
				cin.get();
				continue;
			} 
			int idx = 0;
			while (idx < linestr.size() && linestr[idx] == ' ') { idx++; continue; } // omit the spaces at the beginning of the line
			while (idx < linestr.size() && linestr[idx] != ' ') { idx++; continue; }
			if (idx >= linestr.size()) { cout << "ERROR: idx >= linestr.size()"; cin.get(); }
			frequency = stod(linestr.substr(0, idx));
			tmpstr = linestr.substr(idx + 1);
			if (testlist.find(tmpstr) != testlist.end()) {
				guessed += testlist[tmpstr];
				testlist.erase(tmpstr);
			}
			if (G == Glist[Gidx].first) {
				Glist[Gidx].second = guessed;
				Gidx++;
			}
			G++;
		}
		cout << "end reading full file" << endl;

		for (auto &v : testlist) {
			cout << v.first << "\t" << v.second << endl;
		}
		cin.get();
		
		fout << "%" << datasetname << endl;
		fout << "\\addplot coordinates {";
		double percentage_of_Gmostfreqentpasswords;
		for (int i = 0; i < Glist.size(); i++) {
			cout << "Glist[" << i << "] = {" << Glist[i].first << ", " << Glist[i].second << "}" << endl;
			percentage_of_Gmostfreqentpasswords = (double)Glist[i].second / (double)N_test * 100;
			fout << "(" << Glist[i].first << "," << percentage_of_Gmostfreqentpasswords << ") ";
		}
		fout << "};" << endl;
		cout << "end computing the upper bounds for " << datasetname << "dataset";
	
	fout.close();
	cin.get();
	cin.get();
	return;
}

void generatefrequencycountpairs(string dname) {
	ifstream fin(datasetfilemap[dname]);
	ofstream fout("./" + dname + "-freq.txt");

	string linestr;
	stringstream ss;
	long frequency;
	unordered_map<long, long> freqcountmap;
	long N = 0;
	cout << "start reading" << endl;
	while (getline(fin, linestr)) {
		frequency = 0;
		ss << linestr;
		ss >> frequency;
		ss.clear();
		ss.str("");
		linestr = "";
		freqcountmap[frequency]++;
		N++;
	}
	cout << "N = " << N << endl;
	cout << "end reading" << endl;
	vector<pair<long, long>> freqcountlist(freqcountmap.size(), { 0,0 });
	int i = 0;
	for (auto &mp : freqcountmap) {
		if (i >= freqcountmap.size()) {
cout << "ERROR: i >= freqcountmap.size(), the sizes of freqcountlist and freqcountmap don't match. i = "
<< i << "  freqcountmap.size() = " << freqcountmap.size() << endl;
cin.get();
		}
		else freqcountlist[i++] = mp;
	}
	cout << "start sorting" << endl;
	sort(freqcountlist.begin(), freqcountlist.end(), ismorefreqent_pair_long_long);
	cout << "start writing" << endl;
	for (int i = 0; i < freqcountlist.size(); i++) {
		fout << freqcountlist[i].first << " " << freqcountlist[i].second << endl;
	}
	cout << "end writing" << endl;
	fin.close();
	fout.close();
	return;
}

void replacedelimiter(string dname, char dilim) {
	ifstream fin(datasetfilemap[dname]);
	ofstream fout("./" + dname + "-dilimiter" + to_string((int)dilim) + ".txt");

	string linestr;
	long distinct = 0;
	cout << "start reading" << endl;
	while (getline(fin, linestr)) {
		int idx = 0;
		while (idx < linestr.size() && linestr[idx] == ' ') { idx++; }
		while (idx < linestr.size() && linestr[idx] != ' ') { idx++; }
		if (idx >= linestr.size()) {
			cout << "ERROR: idx >= linestr.size()" << endl;
			cin.get();
		}
		linestr[idx] = dilim;
		fout << linestr << endl;
		distinct++;
	}
	cout << "end reading" << endl;
	cout << "distinct = " << distinct << "  " << distinct_map[dname] << endl;
	fin.close();
	fout.close();
	return;
}

void rawPIN_to_formattedrawPIN(string dname, int digit) {
	string prefix = "D:/Purdue/Research/Datasets/PIN/";
	ifstream fin(prefix + dname + ".txt");
	ofstream fout(prefix + dname + "-formatted.txt");
	string line;
	long long N = 0;
	while (getline(fin, line)) {
		if (line == "") {
			cout << "line is empty" << endl;
			continue;
		}
		if (line.size() < digit) {
			string prezero(digit - line.size(), '0');
			line = prezero + line;
		}
		fout << line << endl;
		N++;
	}

	fin.close();
	fout.close();
	return;
}

void rawPIN_to_frequencylist(string dname) {
	string prefix = "D:/Purdue/Research/Datasets/PIN/amitay/subsample/";
	ifstream fin(prefix + dname + ".txt");
	ofstream fout(prefix + dname + "-Freq.txt");
	ofstream fout2(prefix + dname + "-PINFreq.txt");
	string line;
	unordered_map<string, int> mp;
	long long N = 0;
	while (getline(fin, line)) {
		if (line == "") {
			cout << "line is empty" << endl;
			continue;
		}
		mp[line]++;
N++;
	}
	unordered_map<int, int> freq_map;
	for (auto &v : mp) {
		freq_map[v.second]++;
	}
	vector<vector<int>> FreqCountPairs;
	for (auto &v : freq_map) {
		FreqCountPairs.push_back({ v.second, v.first }); // {count, frequency}
	}
	sort(FreqCountPairs.begin(), FreqCountPairs.end(), ismorefrequent);
	long long N2 = 0;
	for (int i = 0; i < FreqCountPairs.size(); i++) {
		fout << FreqCountPairs[i][1] << "\t" << FreqCountPairs[i][0] << endl;
		N2 += FreqCountPairs[i][0] * FreqCountPairs[i][1];
	}
	if (N != N2) cout << "ERROR: ";
	cout << "N = " << N << "  N2 = " << N2 << endl;

	vector<pair<string, int>> PINFreqPairs;
	for (auto &v : mp) {
		PINFreqPairs.push_back(v);
	}
	sort(PINFreqPairs.begin(), PINFreqPairs.end(), ismorefrequent_pair);
	for (int i = 0; i < PINFreqPairs.size(); i++) {
		fout2 << PINFreqPairs[i].first << "\t" << PINFreqPairs[i].second << endl;
	}

	fin.close();
	fout.close();
	fout2.close();
	return;
}


void experiment_lowerboundsbydictionaryattack(string dname, string dictName, string output) {
	if (output != "lambda_G" && output != "lambda(S,G)") {
		cout << "ERROR: incorrect input parameter outout = " << output << endl;
		cin.get();
		return;
	}
	string inputfilename = datasetfilemap[dname + "-PINFreq"];
	string dictfilename = dictfilemap[dictName];

	ifstream fin_dataset(inputfilename);
	ifstream fin_dict(dictfilename);

	vector<string> dict;
	string password = "";
	int N_dict = 0;
	cout << "start reading " << dictfilename << endl;

	string linestr = "";

	while (getline(fin_dict, linestr)) {
		if (linestr.size() == 0) {
			cout << "N_dict = " << N_dict << endl;
			cout << "fin_dict  linestr.size() == 0" << endl;
			cin.get();
			continue;
		}
		//remove possible "\r\n" at the end of the string. These lines are not needed in Windows OS 
		while (!linestr.empty() && (linestr[linestr.size() - 1] == '\r' || linestr[linestr.size() - 1] == '\n')) {
			linestr.erase(linestr.size() - 1);
		}
		password = linestr;
		dict.push_back(password);
		N_dict++;
	}
	cout << "end reading " << dictfilename << endl;
	cout << "N_dict = " << N_dict << endl;
	fin_dict.close();

	int N = 0; // N_map[datasetname];
	int distinct = distinct_map[dname];
	int count = 0;
	int ind = 0;
	unordered_map<string, int> datasetmp;
	cout << "start reading " << inputfilename << endl;
	linestr = "";
	while (getline(fin_dataset, linestr)) {
		if (linestr.size() == 0) {
			cout << "ind = " << ind << endl;
			cout << "fin_dataset  linestr.size() == 0" << endl;
			cin.get();
			continue;
		}

		password = "";
		count = 0;
		int tmpidx = linestr.size() - 1;
		while (tmpidx >= 0 && linestr[tmpidx] != ' ' && linestr[tmpidx] != '\t') tmpidx--;
		if (tmpidx == 0 || tmpidx == linestr.size() - 1) {
			cout << "ind = " << ind << endl;
			cout << "fin_dataset  tmpidx == 0 || tmpidx == linestr.size()-1;  tmpidx = " << tmpidx << endl;
			cin.get();
			continue;
		}
		count = stoi(linestr.substr(tmpidx + 1));
		password = linestr.substr(0, tmpidx);
		// only for dataset with only 4-digit PIN numbers!!!!
		while (password.size() < 4) {
			password = "0" + password;
		}
		datasetmp[password] = count;
		N += count;
		ind++;
		linestr = "";
	}
	cout << "end reading " << inputfilename << endl;
	if (ind != distinct) {
		cout << "ERROR: ind != distinct    ind = " << ind << "  distinct = " << distinct << endl;
		cin.get();
		exit(-1);
	}
	if (N != N_map[dname]) {
		cout << "ERROR: N != N_map[dname]    N = " << N << "  N_map[dname] = " << N_map[dname] << endl;
		cin.get();
		exit(-1);
	}
	cout << "N = " << N << "  distinct = " << distinct << endl;
	fin_dataset.close();


	double delta = 0.01; // 0.1; // 0.01; // 0.1;
	string outputfilename = output + "-lowerboundbydict-dict=" + dictName + "-delta=" + to_string(delta) + "-" + dname + "_plots.txt";
	ofstream fout(outputfilename);

	cout << "start computing lowerbounds" << endl;
	
	double t = sqrt(-1.0 / 2.0*N*log(delta));
	cout << "N = " << N << "  distinct = " << distinct << endl;
	cout << "delta = " << delta << endl;
	cout << "t = " << t << endl;
	cout << "e = t/N = " << t/(double)N << endl;
	fout << "%" << outputfilename << endl;
	fout << "%1 <= G <= distinct  " << "delta = " << delta << "t = " << t << "e = t/N = " << t / (double)N << endl;
	fout << "N = " << N << "  distinct = " << distinct << endl;
	fout << "\\addplot coordinates {";
	int G = 1;
	int i = 0;
	double gfunc = 0;
	double guessed_passwords = 0.0;
	double lambda = 0;
	int Gind = 1;
	while (G <= N_dict) {
		for (; i < G; i++) {
			guessed_passwords += datasetmp[dict[i]];
		}
		cout << "G = " << G << "  guessed_passwords/N*100 = " << guessed_passwords / (double)N * 100 << endl;
		if (output == "lambda_G") lambda =  (guessed_passwords - t) / (double)N;
		else if (output == "lambda(S,G)") lambda = guessed_passwords / (double)N; // the lowerbound of the number of cracked passwords
		else { cout << "ERROR: output = " << output << endl; cin.get(); }
		fout << "(" << G << "," << lambda * 100 << ") ";
		while (G == ceil(pow(10, 0.1*Gind))) Gind++;
		if (G < N_dict && ceil(pow(10, 0.1*Gind)) > N_dict) G = N_dict;
		else G = ceil(pow(10,0.1*Gind));
		Gind++;
	}
	fout << "};" << endl;
	cout << "end computing lowerbounds" << endl;
	//cin.get();
	//cin.get();
	return;
}

void experiment_frequencyattack_frequencylist(string input_dir, string dname, string surfix) {
	string input_path = input_dir + dname + surfix + ".txt";
	vector<int> metadata = get_metadata(input_path);
	int N = metadata[0];
	int distinct = metadata[1];
	ifstream fin(input_path);
	ofstream fout("./" + dname + "-frequency-plot.txt");

	vector<pair<int, int>> Glist; //for each pair: first element: G, second element: count_of_Gmostfrequentpasswords
	int G;
	if (distinct <= 10000) {
		int nextG = 1;
		while (nextG < distinct) {
			Glist.push_back({ nextG, 0 });
			nextG = ceil(nextG * pow(10, 0.1));
		}
		Glist.push_back({ distinct, 0 });
	}
	else {
		for (int i = 1; i < distinct; i = (i << 1)) {
			Glist.push_back({ i, 0 });
		}
		if (Glist[Glist.size() - 1].first < distinct) Glist.push_back({ distinct,0 });
	}

	int frequency, count;
	int totaldistinct = 0;
	int Gidx = 0;
	cout << "start reading file" << endl;
	while (!fin.eof()) {
		frequency = 0;
		count = 0;
		fin >> frequency >> count;
		if (frequency == 0) {
			cout << "frequency == 0" << endl;
			cin.get();
			continue;
		}
		if (totaldistinct + count <= Glist[Gidx].first) {
			Glist[Gidx].second += frequency * count;
		}
		else {
			if (Gidx + 1 >= Glist.size()) {
				cout << "ERROR: G can be greater than the number of distinct passwords!!" << endl;
				cin.get();
				cin.get();
				exit(-1);
			}
			int tmp = Glist[Gidx].first - totaldistinct;
			Glist[Gidx].second += frequency * tmp;
			int lefttmp = tmp;
			while (tmp < count) {
				++Gidx;
				tmp = tmp + min(Glist[Gidx].first - Glist[Gidx - 1].first, count - tmp);
				Glist[Gidx].second = Glist[Gidx - 1].second + (tmp - lefttmp) * frequency;
				lefttmp = tmp;
			}
		}
		totaldistinct += count;
	}
	cout << "end reading file" << endl;
	fout << "%" << dname << endl;
	fout << "\\addplot coordinates {";
	double percentage_of_Gmostfreqentpasswords;
	for (int i = 0; i < Glist.size(); i++) {
		cout << "Glist[" << i << "] = {" << Glist[i].first << ", " << Glist[i].second << "}" << endl;
		percentage_of_Gmostfreqentpasswords = (double)Glist[i].second / (double)N;
		// if (output == "lambda_G") percentage_of_Gmostfreqentpasswords += epsilon1;
		percentage_of_Gmostfreqentpasswords *= 100;
		fout << "(" << Glist[i].first << "," << percentage_of_Gmostfreqentpasswords << ") ";
	}
	fout << "};" << endl;
	cout << "end generate the frequency plot for " << dname << "dataset" << endl;
	fout.close();
}

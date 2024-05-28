#include "smallset.h"

void subsample_rawdata_to_pwdfreq(string input_dir, string output_dir, string dname, int d, char delimiter) {
	string input_path = input_dir + dname + ".txt";
	string output_path_Freq = output_dir + dname + "-subsample" + to_string(d) + "-Freq.txt";
	string output_path_PwdFreq = output_dir + dname + "-subsample" + to_string(d) + "-PwdFreq.txt";
	ifstream fin(input_path);
	ofstream fout_Freq(output_path_Freq);
	ofstream fout_PwdFreq(output_path_PwdFreq);
	string line;
	int N = 0;
	vector<string> dataset;
	while (getline(fin, line)) {
		if (line.size() == 0) {
			cout << "idx = " << N << endl;
			cout << "fin  line.size() == 0" << endl;
			cin.get();
			continue;
		}
		N++;
		dataset.push_back(line);
	}
	cout << "N = " << N << endl;
	if (N < d) {
		cout << "ERROR: N < d! N = " << N << "; d = " << d << endl;
	}
	int seed = 123456;
	// default_random_engine e(seed);
	// uniform_int_distribution<unsigned> u1(0, N - 1);
	shuffle(dataset.begin(), dataset.end(), default_random_engine(seed));
	unordered_map<string, int> PwdFreqMap;
	for (int i = 0; i < d; i++) {
		PwdFreqMap[dataset[i]]++;
	}
	// output to PwdFreq
	vector<pair<string, int>> sampledSet;
	for (auto v : PwdFreqMap) {
		sampledSet.push_back(v);
	}
	auto cmp = [](pair<string, int>& a, pair<string, int>& b) {return a.second > b.second; };
	sort(sampledSet.begin(), sampledSet.end(), cmp);
	for (int i = 0; i < sampledSet.size(); i++) {
		fout_PwdFreq << sampledSet[i].second << delimiter << sampledSet[i].first << '\n';
	}
	// output to Freq
	unordered_map<int, int> FreqMap; // (freq, count)
	for (auto &v : PwdFreqMap) {
		FreqMap[v.second]++;
	}
	vector<pair<int, int>> sampledSetFreq;
	for (auto v : FreqMap) {
		sampledSetFreq.push_back(v);
	}
	auto cmp2 = [](pair<int, int>& a, pair<int, int>& b) {return a.first > b.first; };
	sort(sampledSetFreq.begin(), sampledSetFreq.end(), cmp2);
	for (int i = 0; i < sampledSetFreq.size(); i++) {
		fout_Freq << sampledSetFreq[i].first << delimiter << sampledSetFreq[i].second << '\n';
	}
	fin.close();
	fout_PwdFreq.close();
	fout_Freq.close();
}

void convert_guessing_curve_to_guessing_number(string dir, string dname, char delimiter) {
	string attack_name = "rnn";
	string filename = dname + "_" + attack_name + "_result";
	string input_path = dir + dname + "/" + filename + ".txt";
	string output_path = dir + "guessingnumber/" + filename + "-guessingnumber.txt";
	ifstream fin(input_path);
	ofstream fout(output_path);
	string line;
	int N = 0;
	double guessing_number = -1;
	string password = "";
	vector<string> dataset;
	while (getline(fin, line)) {
		if (line.size() == 0) {
			cout << "idx = " << N << endl;
			cout << "fin  line.size() == 0" << endl;
			cin.get();
			continue;
		}
		N++;
		int tabidx1 = line.find_first_of(delimiter);
		int tabidx2 = line.find_last_of(delimiter);
		guessing_number = stod(line.substr(0, tabidx1 - 0));
		string new_password = line.substr(tabidx1 + 1, tabidx2 - tabidx1 - 1);
		if (new_password != password) {
			fout << to_string(guessing_number) << "\t" << new_password << "\n";
		}
		password = new_password;
	}
	fin.close();
	fout.close();
}

void checkBlocklist(string blocklist_name, string dname, int k, bool export_to_file, string output_path) {
	ifstream fin_blocklist(blocklist_name);
	ifstream fin_data(dname);
	ofstream fout(output_path); // used only if export_to_file=true
	cout << "output path = " << output_path << endl;

	unordered_set<string> blocklist;
	string line;
	int N_data = 0, N_blocklist = 0;
	// read block list
	while (getline(fin_blocklist, line)) {
		if (line.size() == 0) {
			cout << "idx (blocklist) = " << N_blocklist << endl;
			cout << "fin_blocklist  line.size() == 0" << endl;
			cin.get();
			continue;
		}
		blocklist.insert(line);
		N_blocklist++;
		if (N_blocklist >= k && k >= 0) break;
	}
	cout << "Should block top k = " << k << " passwords/PINs in the blocklist" << endl;
	cout << "Selected blocklist size N_blocklist = " << N_blocklist << endl;
	// read dataset
	while (getline(fin_data, line)) {
		if (line.size() == 0) {
			cout << "idx (dataset) = " << N_blocklist << endl;
			cout << "fin_data  line.size() == 0" << endl;
			cin.get();
			continue;
		}
		N_data++;
		if (blocklist.find(line) != blocklist.end()) {
			// cout << "Line " << N_data << " hit the block list " << line << endl;
			if (export_to_file == false) {
				cin.get();
			}
		}
		else {
			if (export_to_file == true) {
				fout << line << "\n";
			}
		}
	}
	fin_blocklist.close();
	fin_data.close();
	fout.close();
}

void subsample_raw_data_to_raw_data(string input_dir, string output_dir, string dname, int d) {
	string input_path = input_dir + dname + ".txt";
	string output_path = output_dir + dname + "-subsample" + to_string(d) + ".txt";
	ifstream fin(input_path);
	ofstream fout(output_path);
	string line;
	int N = 0;
	vector<string> dataset;
	while (getline(fin, line)) {
		if (line.size() == 0) {
			cout << "idx = " << N << endl;
			cout << "fin  line.size() == 0" << endl;
			cin.get();
			continue;
		}
		N++;
		dataset.push_back(line);
	}
	cout << "N = " << N << endl;
	if (N < d) {
		cout << "ERROR: N < d! N = " << N << "; d = " << d << endl;
	}
	int seed = 123456;
	shuffle(dataset.begin(), dataset.end(), default_random_engine(seed));
	for (int i = 0; i < d; i++) {
		fout << dataset[i] << "\n";
	}
	fin.close();
	fout.close();
}

vector<int> get_metadata(string input_path) {
	ifstream fin(input_path);
	string line;
	int N = 0;
	int distinct = 0;
	int frequency, count;
	stringstream ss;
	while (getline(fin, line)) {
		if (line.size() == 0) {
			cout << "idx = " << N << endl;
			cout << "fin  line.size() == 0" << endl;
			cin.get();
			continue;
		}
		ss << line;
		ss >> frequency;
		ss >> count;
		ss.clear();
		ss.str("");
		line = "";

		if ((N + frequency) < 0 || (N + frequency) < N) {
			cout << "Error: the value of N exceeds the maximum value of a long interger!!!" << endl;
			cin.get();
		}
		N += frequency * count;
		distinct += count;
	}
	cout << "N = " << N << "  distinct = " << distinct << endl;
	return vector<int>({ N, distinct });
} 

void freqpwd_to_frequencylist(string dname, string input_path, string output_dir) {
	ifstream fin(input_path);
	ofstream fout_Freq(output_dir + dname + "-Freq.txt");
	ofstream fout_PwdFreq(output_dir + dname + "-PwdFreq.txt");

	string line = "";
	int N = 0;
	unordered_map<int, int> FreqMap; // (freq, count)
	while (getline(fin, line)) {
		if (line.size() == 0) {
			cout << "current N = " << N << endl;
			cout << "fin  lin.size() == 0" << endl;
			cin.get();
			continue;
		}
		string password = "";
		int frequency = 0;
		int tmpidx1 = 0, tmpidx2 = 0;
		while (tmpidx1 < line.size() && line[tmpidx1] == ' ') tmpidx1++;
		if (tmpidx1 == line.size()) {
			cout << "current N = " << N << endl;
			cout << "fin  tmpidx1 == fin.size()" << endl;
			cin.get();
			continue;
		}
		tmpidx2 = tmpidx1;
		while (tmpidx2 < line.size() && line[tmpidx2] != ' ') tmpidx2++;
		frequency = stoi(line.substr(tmpidx1, tmpidx2 - tmpidx1));
		password = line.substr(tmpidx2 + 1);
		line = "";
		// output to PwdFreq
		fout_PwdFreq << password << "\t" << frequency << "\n";
		N += frequency;
		FreqMap[frequency]++;
	}
	cout << "N = " << N << endl;

	vector<pair<int, int>> FreqList;
	for (auto v : FreqMap) {
		FreqList.push_back(v);
	}
	auto cmp = [](pair<int, int>& a, pair<int, int>& b) {return a.first > b.first; };
	sort(FreqList.begin(), FreqList.end(), cmp);
	for (int i = 0; i < FreqList.size(); i++) {
		fout_Freq << FreqList[i].first << "\t" << FreqList[i].second << "\n";
	}
	fin.close();
	fout_Freq.close();
	fout_PwdFreq.close();
}
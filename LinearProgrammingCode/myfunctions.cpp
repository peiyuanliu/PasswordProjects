#include "myfunctions.h"


unordered_map<string, string> datasetfilemap{
	{ "mytestyahoo", "D:/Purdue/CS590 PWD/dataset/yahoo_password_frequencies_corpus/yahoo-all.txt" },
	{ "linkedin", "D:/Purdue/CS590 PWD/dataset/linkedin_dataset/full.out" },
	{ "yahoo", "D:/Purdue/CS590 PWD/dataset/yahoo_password_frequencies_corpus/yahoo-all.txt" },
	{ "rockyou", "D:/Purdue/CS590 PWD/dataset/rockyouFreq.txt" },
	{ "000webhost", "D:/Purdue/CS590 PWD/dataset/000webhostFreq.txt" },
	{ "neopets", "D:/Purdue/CS590 PWD/dataset/neopetsFreq.txt" },
	{ "bfield", "D:/Purdue/CS590 PWD/dataset/bfieldFreq.txt" },
	{ "brazzers", "D:/Purdue/CS590 PWD/dataset/brazzersFreq.txt" },
	{ "clixsense", "D:/Purdue/CS590 PWD/dataset/clixsenseFreq.txt" },
	{ "csdn", "D:/Purdue/CS590 PWD/dataset/csdnFreq.txt" }
};


unordered_map<string, string> PINorPWD{
	{ "UserStudy_first-choice_4-digit", "4-digit"},
	{ "PIN4digit-amitay-dp", "4-digit"},
	{ "PIN4digit-rockyou", "4-digit" },
	{ "PIN6digit-rockyou", "6-digit" },
	{ "linkedin", "PWD" },
	{ "yahoo", "PWD" },
	{ "rockyou", "PWD" },
	{ "000webhost", "PWD" },
	{ "neopets", "PWD" },
	{ "bfield", "PWD" },
	{ "brazzers", "PWD" },
	{ "clixsense", "PWD" },
	{ "csdn", "PWD" },
};

unordered_map<string, int> N_map{
	{ "UserStudy_first-choice_4-digit", 851},
	{ "PIN4digit-amitay-dp", 204445},
	{ "PIN4digit-rockyou", 1780587 },
	{ "PIN6digit-rockyou", 2758490 },
	{ "linkedin", 174292189 },
	{ "yahoo", 69301337 },
	{ "rockyou", 32603388 },
	{ "000webhost", 15268903 },
	{ "neopets", 68345757 },
	{ "bfield", 541016 },
	{ "brazzers", 925614 },
	{ "clixsense", 2222529 },
	{ "csdn", 6428449 },
	{ "yahoo10000", 10000 },
	{ "yahoo100000", 100000 },
	{ "yahoo1000000", 1000000 },
	{ "yahoo10000000", 10000000 },
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
};

unordered_map<string, int> distinct_map{
	{ "UserStudy_first-choice_4-digit", 722 },
	{ "PIN4digit-amitay-dp", 9885},
	{ "PIN4digit-rockyou", 10000 },
	{ "PIN6digit-rockyou", 448185 },
	{ "linkedin", 57431283 },
	{ "yahoo", 33895873 },
	{ "rockyou", 14344391 },
	{ "000webhost", 10592935 },
	{ "neopets", 27987227 },
	{ "bfield", 416130 },
	{ "brazzers", 587934 },
	{ "clixsense", 1628577 },
	{ "csdn", 4037749 },
	{ "yahoo10000", 9583 },
	{ "yahoo100000", 88110 },
	{ "yahoo1000000", 764307 },
	{ "yahoo10000000", 6135968 },
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
};

double sparseP = 0.0;
double sparseguessingnumber = 0.0;
ofstream fout;





double binopdf(long x, long n, double p) {
	if (x > n || x < 0) return 0;
	double q = 1 - p;
	double res = 1;
	if (x == 0) {
		res = res * pow(q, n);
	}
	else {
		long step = floor((n - x) / x);
		for (int i = 0; i<x; i++) {
			res = res * p * pow(q, step) * (double)(n - i) / (double)(x - i);
			//if (x == 1) cout << "i = " << i << "  pow(" << q << ", " << step << ") = " << pow(q, step) << endl;
		}
		res = res * pow(q, n - x - step*x);
	}
	return res;
}

double binocdf(long x1, long x2, long n, double p) {
	double cdf = 0.0;
	for (int i = x1; i <= x2; i++) {
		cdf += binopdf(i, n, p);
	}
	return cdf;
}






void generatefrequencycountpairs() {
	unordered_map<string, string> dataset_addr = {
		{ "000webhost", "D:/Purdue/CS590 PWD/dataset/Jeremiah/09_perfect/000webhost_shuf_clean-withcount.txt" },
		{ "neopets", "D:/Purdue/CS590 PWD/dataset/Jeremiah/09_perfect/neopets_shuf_clean-withcount.txt" } };

	string datasetname = "neopets"; // "000webhost";
	ifstream fin(dataset_addr[datasetname]);
	ofstream fout("D:/Purdue/CS590 PWD/dataset/" + datasetname + "Freq.txt");

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
	sort(freqcountlist.begin(), freqcountlist.end(), ismorefreqent);
	cout << "start writing" << endl;
	for (int i = 0; i < freqcountlist.size(); i++) {
		fout << freqcountlist[i].first << " " << freqcountlist[i].second << endl;
	}
	cout << "end writing" << endl;
	fin.close();
	fout.close();
	return;
}
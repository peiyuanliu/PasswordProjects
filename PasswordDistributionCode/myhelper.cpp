#include "myhelper.h"

string prefix = "C:/Users/ms_green/Desktop/baiattack/";

void experiment_samplingLB3(string dname, string output) {
	if (output != "lambda_G" && output != "lambda(S,G)") {
		cout << "ERROR: incorrect input parameter outout = " << output << endl;
		cin.get();
		return;
	}
	unordered_map<string, int> thisfunc_N_map{
		{ "clixsense", 2222529 },
	};
	unordered_map<string, int> thisfunc_distinct_map{
		{ "clixsense", 1628577 },
	};
	unordered_map<string, int> thisfunc_distinct_test_map {
		{ "clixsense", 23721 },
	};
	unordered_map<string, string> thisfunc_datasetfilemap{
		{ "clixsense", "D:/Purdue/CS590 PWD/dataset/Jeremiah/09_perfect/clixsense_shuf_clean-withcount.txt" },
	};
	unordered_map<string, string> thisfunc_datasetfile_test_map{
		{ "clixsense", prefix + "clixsense/clixsense_test.csv" },
	};
		
	string datasetname = dname;
	string inputfilename = thisfunc_datasetfilemap[datasetname];
	string inputtestfilename = thisfunc_datasetfile_test_map[datasetname];

	// string remainingsamplefilename = datasetname + "_samples_remaining.txt";
	// string testsamplefilname = datasetname + "_samples_25k.txt";

	ifstream fin_all(inputfilename);
	ifstream fin_test(inputtestfilename);


	int N = 0; // thisfunc_N_map[datasetname];
	int distinct = thisfunc_distinct_map[datasetname];

	int d = 25000;

	unordered_map<string, int> testsetmp;
	string password = "";
	int count = 0;
	int N_test = 0;
	int totalnum_test = 0;
	string linestr = "";

	cout << "start reading " << inputtestfilename << endl;
	while (getline(fin_test, linestr)) {
		count = 0;
		password = "";
		if (linestr == "") {
			cout << "linestr is empty" << endl;
			cin.get();
			continue;
		}
		istringstream readstr(linestr);
		getline(readstr, password, '\t');
		string strfreq = "";
		getline(readstr, strfreq, '\t');
		count = stod(strfreq);
		testsetmp[password] = count;
		totalnum_test++;
		N_test += count;
	}
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
	sort(SminusD.begin(), SminusD.end(), VectorIntDecreasingOrderComp);
	cout << "end sorting SminusD" << endl;

	int G = 1;
	string outputfilename = "othertest-" + output + "-SamplingLB-d=" + to_string(d) + "-" + datasetname + "_plots.txt";
	ofstream fout(outputfilename);
	ofstream mylog("othertest-" + output + "-" + datasetname + "-d = " + to_string(d) + "_logfile.txt");

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
	mylog.close();
	return;
}


void experiment_ExtendedLB3(string dname, string output) {
	if (output != "lambda_G" && output != "lambda(S,G)") {
		cout << "ERROR: incorrect input parameter outout = " << output << endl;
		cin.get();
		return;
	}
	unordered_map<string, int> thisfunc_N_map{
		{ "clixsense", 2222529 },
	};
	unordered_map<string, int> thisfunc_distinct_map{
		{ "clixsense", 1628577 },
	};
	unordered_map<string, int> thisfunc_distinct_test_map{
		{ "clixsense", 23721 },
	};
	unordered_map<string, string> thisfunc_datasetfilemap{
		{ "clixsense", "D:/Purdue/CS590 PWD/dataset/Jeremiah/09_perfect/clixsense_shuf_clean-withcount.txt" },
	};

	unordered_map<string, string> thisfunc_datasetfile_test_map{
		{ "clixsense", prefix + "clixsense/clixsense_test.csv" },
	};

	string datasetname = dname;
	string inputfilename = thisfunc_datasetfilemap[datasetname];
	string inputtestfilename = thisfunc_datasetfile_test_map[datasetname];

	// string remainingsamplefilename = datasetname + "_samples_remaining.txt";
	// string testsamplefilname = datasetname + "_samples_25k.txt";

	ifstream fin_all(inputfilename);
	ifstream fin_test(inputtestfilename);


	int N = 0; // thisfunc_N_map[datasetname];
	int distinct = thisfunc_distinct_map[datasetname];

	int d = 25000;

	unordered_map<string, int> testsetmp;
	string password = "";
	int count = 0;
	int N_test = 0;
	int totalnum_test = 0;
	string linestr = "";

	cout << "start reading " << inputtestfilename << endl;
	while (getline(fin_test, linestr)) {
		count = 0;
		password = "";
		if (linestr == "") {
			cout << "linestr is empty" << endl;
			cin.get();
			continue;
		}
		istringstream readstr(linestr);
		getline(readstr, password, '\t');
		string strfreq = "";
		getline(readstr, strfreq, '\t');
		count = stod(strfreq);
		testsetmp[password] = count;
		totalnum_test++;
		N_test += count;
	}
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
	unordered_map<string, int> passidxmp;
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
	sort(SminusD.begin(), SminusD.end(), VectorIntDecreasingOrderComp);
	cout << "end sorting SminusD" << endl;

	string outputfilename = "othertest-" + output + "-G_geq_distinct_newlowerbound-d=" + to_string(d) + "-" + datasetname + "_plots.txt";
	ofstream fout(outputfilename);
	ofstream mylog("othertest-" + output + "-G_geq_distinct_" + datasetname + "-d = " + to_string(d) + "_logfile.txt");



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
			G = G + 1;
		}
	}
	cout << "end computing lowerbounds" << endl;

	//Then use an empirical attack to guess Dset
	vector<vector<string>> attackresults;
	string attackprefix = prefix + datasetname + "/";
	attackresults = {
		//{ prefix + "_perfect_result.txt", "Perfect Knowledge" },
		{ attackprefix + "2-gram_guess.txt", "2-gram" },
		{ attackprefix + "3-gram_guess.txt", "3-gram" },
		{ attackprefix + "4-gram_guess.txt", "4-gram" },
		{ attackprefix + "5-gram_guess.txt", "5-gram" },
		{ attackprefix + "Backoff_guess.txt", "Backoff" },
		{ attackprefix + "PCFG_guess.txt", "PCFG" },
		{ attackprefix + "rnn_guess.txt", "rnn" },
		{ attackprefix + "transformer_guess.txt", "transformer" },
	};
	
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
		ifstream fin_attack(attackresults[i][0]);
		fout << "%" << attackresults[i][1] << endl;
		fout << "%" << attackresults[i][0] << endl;
		fout << "\\addplot coordinates {";
		cout << "start plotting " << attackresults[i][1] << endl;
		cout << attackresults[i][0] << endl;
		mylog << "%" << attackresults[i][1] << endl;
		vector<pwdguess> pwdattacklist;
		double guessingnumber = 0;
		linestr = "";
		G = baseguessingnum;
		hfunc = basehfunc;
		int passguenum = -1;
		string prepwd = "";
		while (getline(fin_attack, linestr)) {
			count = 0;
			password = "";
			if (linestr == "") {
				cout << "linestr is empty" << endl;
				cin.get();
				continue;
			}
			istringstream readstr(linestr);
			getline(readstr, password, '\t');
			string tempstr = "";
			getline(readstr, tempstr, '\t');
			if (tempstr == "nan") continue; // nan means the password is not guessed by the attack
			guessingnumber = stod(tempstr);
			getline(readstr, tempstr, '\t');
			count = stod(tempstr);
			pwdguess tmpstruct = { password, guessingnumber, count };
			pwdattacklist.push_back(tmpstruct);
		}
		sort(pwdattacklist.begin(), pwdattacklist.end(), StructPwdguessIncreasingOrderCompt);
		vector<pair<double, double>> Glist; //for each pair: first element: G second element: percentage of cracked passwords
		Glist.push_back({ G,0 });
		double starti = 1;
		while (starti <= G) { starti *= 2; }
		for (double j = starti; j < pow(10,16); j *= 2) {
			Glist.push_back({ j, 0 });
		}
		int Gidx = 0;
		double duplicateguess = 0;
		for (int j = 0; j < pwdattacklist.size() && Gidx < Glist.size(); j++) {
			while (Gidx < Glist.size() && (pwdattacklist[j].guessnum + baseguessingnum - duplicateguess) > Glist[Gidx].first) {
				gfunc = 0;
				if (output == "lambda_G") gfunc = (double)N / (double)d * (hfunc - t2);
				else if (output == "lambda(S,G)") gfunc = (double)N / (double)d * (hfunc - t2) - t1; // the lowerbound of the number of cracked passwords
				else { cout << "ERROR: output = " << output << endl; cin.get(); }
				percentage_of_guessed_passwords = (double)gfunc / (double)N * 100;
				Glist[Gidx].second = percentage_of_guessed_passwords;
				Gidx++;
			}
			if (passidxmp.find(pwdattacklist[j].pwd) == passidxmp.end()) {
				cout << "ERROR: passidxmp.find(pwdattacklist[j].pwd) == passidxmp.end()" << endl;
				cout << "password = " << pwdattacklist[j].pwd << endl;
				cin.get();
				continue;
			}
			if (guessed[passidxmp[pwdattacklist[j].pwd]] == true) { // duplicate guess
				duplicateguess += 1;
			}
			else {
				hfunc += pwdattacklist[j].freq;
			}
		}
		if (Gidx < Glist.size()) {
			gfunc = 0;
			if (output == "lambda_G") gfunc = (double)N / (double)d * (hfunc - t2);
			else if (output == "lambda(S,G)") gfunc = (double)N / (double)d * (hfunc - t2) - t1; // the lowerbound of the number of cracked passwords
			else { cout << "ERROR: output = " << output << endl; cin.get(); }
			percentage_of_guessed_passwords = (double)gfunc / (double)N * 100;
			Glist[Gidx].second = percentage_of_guessed_passwords;
		}

		double percentage_of_Gmostfreqentpasswords;
		for (int j = 0; j < Glist.size(); j++) {
			cout << "Glist[" << j << "] = {" << Glist[j].first << ", " << Glist[j].second << "}" << endl;
			fout << "(" << Glist[j].first << "," << Glist[j].second << ") ";
		}
		fout << "};" << endl;
		fin_attack.close();
	}
	//cin.get();
	//cin.get();
	fout.close();
	//fout2.close();
	mylog.close();
	return;
}

void experiment_plotguessingcurves3(string dname) {
	string datasetname = dname; 
	ofstream fout("othertest-" + datasetname + "_existingresults_plots.txt");
	unordered_map<string, int> thisfunc_distinct_test_map{
		{ "clixsense", 23721 },
	};
	vector<vector<string>> attackresults;
	string attackprefix = prefix + datasetname + "/";
	attackresults = {
		{ attackprefix + "2-gram_guess.txt", "2-gram" },
		{ attackprefix + "3-gram_guess.txt", "3-gram" },
		{ attackprefix + "4-gram_guess.txt", "4-gram" },
		{ attackprefix + "5-gram_guess.txt", "5-gram" },
		{ attackprefix + "Backoff_guess.txt", "Backoff" },
		{ attackprefix + "PCFG_guess.txt", "PCFG" },
		{ attackprefix + "rnn_guess.txt", "rnn" },
		{ attackprefix + "transformer_guess.txt", "transformer" },
	};
	int distinct = thisfunc_distinct_test_map[datasetname];
	int N = 25000;

	fout << "%1 <= G <= distinct = " << distinct << endl;
	for (int i = 0; i < attackresults.size(); i++) {
		ifstream fin(attackresults[i][0]);
		fout << "%" << attackresults[i][1] << endl;
		fout << "%" << attackresults[i][0] << endl;
		fout << "\\addplot coordinates {";
		cout << "start plotting " << attackresults[i][1] << endl;
		cout << attackresults[i][0] << endl;
		vector<pwdguess> pwdattacklist;
		double guessingnumber = 0;
		string linestr = "";
		int passguenum = -1;
		double count;
		string password;
		string prepwd = "";
		int total = 0;
		while (getline(fin, linestr)) {
			count = 0;
			password = "";
			if (linestr == "") {
				cout << "linestr is empty" << endl;
				cin.get();
				continue;
			}
			istringstream readstr(linestr);
			getline(readstr, password, '\t');
			string tempstr = "";
			getline(readstr, tempstr, '\t');
			if (tempstr == "nan") continue; // not guessed by this attack
			else guessingnumber = stod(tempstr);
			getline(readstr, tempstr, '\t');
			count = stod(tempstr);
			pwdguess tmpstruct = { password, guessingnumber, count };
			pwdattacklist.push_back(tmpstruct);
			total += count;
		}
		cout << "total = " << total << endl;
		sort(pwdattacklist.begin(), pwdattacklist.end(), StructPwdguessIncreasingOrderCompt);

		ofstream fouttmp("./tmptest-" + attackresults[i][1] + ".txt");
		for (int j = 0; j < pwdattacklist.size(); j++) {
			fouttmp << pwdattacklist[j].guessnum << "\t" << pwdattacklist[j].pwd << "\t" << pwdattacklist[j].freq << endl;
		}
		vector<pair<double, double>> Glist; //for each pair: first element: G second element: percentage of cracked passwords
		for (double j = 1; j < pow(10, 16); j *= 2) {
			Glist.push_back({ j, 0 });
		}
		int Gidx = 0;
		double guessedcount = 0;
		int j;
		for (j = 0; j < pwdattacklist.size() && Gidx < Glist.size(); j++) {
			while (Gidx < Glist.size() && pwdattacklist[j].guessnum > Glist[Gidx].first) {
				Glist[Gidx].second = guessedcount/(double)N * 100;
				Gidx++;
			}
			guessedcount += pwdattacklist[j].freq;
		}
		cout << "next password: " << "j = " << j << "  guessingnumber = " << pwdattacklist[j].guessnum << "  pwd = " << pwdattacklist[j].pwd << endl;
		if (Gidx < Glist.size()) {
			Glist[Gidx].second = guessedcount /(double)N * 100;
		}

		for (int j = 0; j < Glist.size(); j++) {
			cout << "Glist[" << j << "] = {" << Glist[j].first << ", " << Glist[j].second << "}" << endl;
			fout << "(" << Glist[j].first << "," << Glist[j].second << ") ";
		}
		fout << "};" << endl;
		fin.close();
	}
	fout.close();
	return;
}

bool VectorIntDecreasingOrderComp(const vector<int> &a, const vector<int> &b) {
	if (a[1] > b[1]) return true;
	else return false;
}
bool StructPwdguessIncreasingOrderCompt(const pwdguess &a, const pwdguess &b) {
	if (a.guessnum < b.guessnum) return true;
	else return false;
}



void MonteCarloCounterExample() {
	string inputaddr = "D:/Purdue/CS590 PWD/dataset/yahoo_password_frequencies_corpus/yahoo-all.txt";
	ifstream fin(inputaddr);
	string line;
	vector<int> frequencies, counts;
	int frequency, count;
	int len = 0,N=0,distinct=0;
	cout << "start reading: " << inputaddr << endl;
	while (!fin.eof()) {
		frequency = 0;
		count = 0;
		fin >> frequency >> count;
		if (frequency == 0) {
			cout << "frequency == 0" << endl;
			cin.get();
			continue;
		}
		frequencies.push_back(frequency);
		counts.push_back(count);
		len++;
		N += count*frequency;
		distinct += count;
	}
	cout << "start calculating variance" << endl;
	double Var = 0;
	double sum = 0;
	double deltasize = 0;
	for (int i = 0; i < len-1; i++) {
		sum += 1.0 / (frequencies[i] / (double)N)*counts[i];
		deltasize += (double)counts[i];
	}
	double n = pow(10, 5) * 6;
	Var = (sum - deltasize*deltasize) / n;
	cout << "Var = " << Var << "  deltasize = " << deltasize << endl;
	cout << "sqrt(Var)/deltasize*100 = " << sqrt(Var) / deltasize * 100 << "%" << endl;
	cout << "sqrt(Var)/N*100 = " << sqrt(Var) / N * 100 << "%" << endl;
}
#include "pcp.h"

vector<string> PCPitems = { "min", "lower", "upper", "digit", "symbol" };


void experiment_extractpasswordswithPCPs(string dname) {
	if (dname != "neopets" && dname != "rockyou") {
		cout << "ERROR: invalid dataset " << dname << endl;
	}

	unordered_map<string, string> sourcemap = {
		// { "neopets", "D:/Purdue/CS590 PWD/dataset/Jeremiah/09_perfect/neopets_shuf_clean-withcount.txt" },
		{ "neopets", "/home/liu2039/PasswordDataset/Jeremiah/09_perfect/neopets_shuf_clean-withcount.txt" },
		{ "rockyou", "/home/liu2039/PasswordDataset/rockyou-withcount.txt/rockyou-withcount.txt" },
	};
	string daddr = sourcemap[dname];
	vector<vector<vector<int>>> PCPlist = { // {minchar, lower, upper, digit, symbol}
		// {{ 8,0,0,0,0 }},
		// {{ 8,1,1,1,1 }},
		// {{ 16,0,0,0,0 }},
		// {{ 8,1,1,1,0 }},
		// {{ 8,0,1,1,0 }},
		{ { 8,0,1,0,0 } },
		{ { 12,0,0,0,0 } },
		{ { 15,0,0,0,0 },{ 8,1,0,1,0 } },
		{ { 14,0,0,0,0 }, {0,0,0,0,2}, { 8,0,1,1,0 } },
	};
	for (int i = 0; i < PCPlist.size(); i++) {
		vector<unordered_map<string, int>> PCP(PCPlist[i].size(), unordered_map<string, int>());
		for (int j = 0; j < PCPlist[i].size(); j++) {
			for (int k = 0; k < PCPlist[i][j].size(); k++) {
				PCP[j][PCPitems[k]] = PCPlist[i][j][k];
			}
		}
		ExtractSubsetWithPCP(dname, daddr, PCP);
	}
	
}

void experiment_manuallyAmendpasswordswithPCPs(string dname) {
	if (dname != "neopets") {
	// if (dname != "neopets" && dname != "rockyou") {
		cout << "ERROR: invalid dataset " << dname << endl;
	}
	unordered_map<string, string> sourcemap = {
		{ "neopets", "D:/Purdue/CS590 PWD/dataset/Jeremiah/09_perfect/neopets_shuf_clean-withcount.txt" },
		// { "neopets", "/home/liu2039/PasswordDataset/Jeremiah/09_perfect/neopets_shuf_clean-withcount.txt" },
		// { "rockyou", "/home/liu2039/PasswordDataset/rockyou-withcount.txt/rockyou-withcount.txt" },
	};
	string daddr = sourcemap[dname];
	vector<vector<vector<int>>> PCPlist = { // {minchar, lower, upper, digit, symbol}
		// {{ 8,0,0,0,0 }},
		{{ 8,1,1,1,1 }},
		// {{ 16,0,0,0,0 }},
		// {{ 8,1,1,1,0 }},
		// {{ 8,0,1,1,0 }},
		// { { 8,0,1,0,0 } },
		// { { 12,0,0,0,0 } },
		// { { 15,0,0,0,0 },{ 8,1,0,1,0 } },
		// { { 14,0,0,0,0 }, {0,0,0,0,2}, { 8,0,1,1,0 } },
	};
	for (int i = 0; i < PCPlist.size(); i++) {
		vector<unordered_map<string, int>> PCP(PCPlist[i].size(), unordered_map<string, int>());
		for (int j = 0; j < PCPlist[i].size(); j++) {
			for (int k = 0; k < PCPlist[i][j].size(); k++) {
				PCP[j][PCPitems[k]] = PCPlist[i][j][k];
			}
		}
		ManuallyAmendPasswordSetToSatisfyPCP(dname, daddr, PCP, "Aa1@Aa1@");
	}

}

void ExtractSubsetWithPCP(string dname, string daddr, vector<unordered_map<string, int>>& PCP) {
	ifstream fin(daddr);
	string outputname = "./" + dname + "-";
	for (int i = 0; i < PCP.size(); i++) {
		if (i > 0) outputname += "OR";
		for (int j = 0; j < PCPitems.size(); j++) {
			if (PCP[i][PCPitems[j]] > 0) { outputname += PCPitems[j] + to_string(PCP[i][PCPitems[j]]); }
		}
	}
	outputname += ".txt";
	ofstream fout(outputname);
	string linestr;
	string freqstr, password;
	long long N = 0;
	long long distinct = 0;
	while (getline(fin, linestr)) {
		if (linestr == "") {
			cout << "linestr is empty" << endl;
			cin.get();
			continue;
		}
		istringstream readstr(linestr);
		int tmpidx1 = 0;
		while (tmpidx1 < linestr.size() && linestr[tmpidx1] == ' ') { tmpidx1++; }
		int tmpidx2 = tmpidx1;
		while (tmpidx2 < linestr.size() && linestr[tmpidx2] != ' ') { tmpidx2++; }
		freqstr = linestr.substr(tmpidx1, tmpidx2 - tmpidx1);
		password = linestr.substr(tmpidx2 + 1);
		// getline(readstr, freqstr, '\t');
		// getline(readstr, password, '\t');
		if (CheckPCP(password, PCP)) {
			fout << linestr << endl;
			distinct++;
			N += stol(freqstr);
		}
	}
	cout << "Statics of the extracted subset: " << "N = " << N << "  distinct = " << distinct << endl;
	fin.close();
	fout.close();
}

bool CheckPCP(string password, vector<unordered_map<string, int>>& PCP) {
	unordered_map<string, int> count;
	count["min"] = password.size();
	for (int i = 0; i < password.size(); i++) {
		if (password[i] >= 48 && password[i] <= 57) {
			count["digit"]++;
		}
		else if (password[i] >= 65 && password[i] <= 90) {
			count["upper"]++;
		}
		else if (password[i] >= 97 && password[i] <= 122) {
			count["lower"]++;
		}
		else if (password[i] >= 32 && password[i] <= 126) {
			count["symbol"]++;
		}
		/*
		else {
			cout << "ERROR: illegal character: " << password[i] << "with code " << (int)password[i]
				<< "in password " << password << endl;
			cin.get();
		}
		*/
	}
	for (int k = 0; k < PCP.size(); k++) {
		bool isSatisfied = true;
		for (int i = 0; i < PCPitems.size(); i++) {
			if (count[PCPitems[i]] < PCP[k][PCPitems[i]]) {
				isSatisfied = false;
				break;
			}
		}
		if (isSatisfied) return true;
	}
	return false;
}

void ManuallyAmendPasswordSetToSatisfyPCP(string dname, string daddr, vector<unordered_map<string, int>>& PCP, string append_surfix) {
	ifstream fin(daddr);
	string outputname = "./" + dname + "-";
	for (int i = 0; i < PCP.size(); i++) {
		if (i > 0) outputname += "OR";
		for (int j = 0; j < PCPitems.size(); j++) {
			if (PCP[i][PCPitems[j]] > 0) { outputname += PCPitems[j] + to_string(PCP[i][PCPitems[j]]); }
		}
	}
	outputname += "-appendSurfix=" + append_surfix + "-manually";
	outputname += ".txt";
	ofstream fout(outputname);
	string linestr;
	string freqstr, password;
	long long N = 0;
	long long distinct = 0;
	while (getline(fin, linestr)) {
		if (linestr == "") {
			cout << "linestr is empty" << endl;
			cin.get();
			continue;
		}
		istringstream readstr(linestr);
		int tmpidx1 = 0;
		while (tmpidx1 < linestr.size() && linestr[tmpidx1] == ' ') { tmpidx1++; }
		int tmpidx2 = tmpidx1;
		while (tmpidx2 < linestr.size() && linestr[tmpidx2] != ' ') { tmpidx2++; }
		freqstr = linestr.substr(tmpidx1, tmpidx2 - tmpidx1);
		password = linestr.substr(tmpidx2 + 1);
		// getline(readstr, freqstr, '\t');
		// getline(readstr, password, '\t');
		if (!CheckPCP(password, PCP)) {
			password += append_surfix;
			if (!CheckPCP(password, PCP)) {
				cout << "ERROR: wrong fix append_surfix = " << append_surfix << "; password = " << password << endl;
				cin.get();
			}
		}
		fout << freqstr << " " << password << endl;
		distinct++;
		N += stol(freqstr);
	}
	cout << "Statics of the extracted subset: " << "N = " << N << "  distinct = " << distinct << endl;
	fin.close();
	fout.close();
}
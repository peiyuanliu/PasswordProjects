/* Copyright 2020, Gurobi Optimization, LLC */

/* This example formulates and solves the following simple MIP model:

maximize    x +   y + 2 z
subject to  x + 2 y + 3 z <= 4
x +   y       >= 1
x, y, z binary
*/

//Warning: the largest sample size should be smaller than 2^31-1 (the max signed long int)
//For larger sample size, change all "long" type variables to "long long" or "double"
// also, G cannot be greater than 10^13, because we sometimes use G_scale = 1/G as coefficient in the LP task, 
//and 10^-13 is the smallest coefficient gurobi solver can deal with.

//#include "/home/liu2039/gitbranch/PasswordDistribution/UnseenGurobi/UnseenGurobi/myfunctions.h"
#include "myfunctions.h"

/*
Peiyuan's Notes: Be careful when changing the constraints in Gurobi LP tasks. 
 Some constraint parameters were rescaled to avoid numeric problems and warnings in gurobi solver.
*/

unordered_map<string, string> datasetfilemap_workbench{
	{ "UserStudy_first-choice_4-digit", "/home/liu2039/PasswordDataset/PIN/UserStudy_first-choice_4-digit-Freq.txt"},
	{ "PIN4digit-amitay-dp", "/home/liu2039/PasswordDataset/PIN/passcodeDataDP-epsilon=0.25.txt"},
	{ "PIN4digit-rockyou", "/home/liu2039/PasswordDataset/PIN/RockYou-4-digit-Freq.txt" },
	{ "PIN6digit-rockyou", "/home/liu2039/PasswordDataset/PIN/RockYou-6-digit-Freq.txt" },
	{ "mytestyahoo", "/home/liu2039/PasswordDataset/yahoo_password_frequencies_corpus/yahoo-all.txt" },
	{ "linkedin", "/home/liu2039/PasswordDataset/linkedin_dataset/full.out" },
	{ "yahoo", "/home/liu2039/PasswordDataset/yahoo_password_frequencies_corpus/yahoo-all.txt" },
	{ "rockyou", "/home/liu2039/PasswordDataset/rockyouFreq.txt" },
	{ "000webhost", "/home/liu2039/PasswordDataset/000webhostFreq.txt" },
	{ "neopets", "/home/liu2039/PasswordDataset/neopetsFreq.txt" },
	{ "bfield", "/home/liu2039/PasswordDataset/bfieldFreq.txt" },
	{ "brazzers", "/home/liu2039/PasswordDataset/brazzersFreq.txt" },
	{ "clixsense", "/home/liu2039/PasswordDataset/clixsenseFreq.txt" },
	{ "csdn", "/home/liu2039/PasswordDataset/csdnFreq.txt" },
	// { "yahoo1000", "/home/liu2039/PasswordDataset/yahoo_subsample/yahoo_subsample_size=1000.txt" },
	{ "yahoo10000", "/home/liu2039/PasswordDataset/yahoo_subsample/yahoo_subsample_size=10000.txt" },
	{ "yahoo100000", "/home/liu2039/PasswordDataset/yahoo_subsample/yahoo_subsample_size=100000.txt" },
	{ "yahoo1000000", "/home/liu2039/PasswordDataset/yahoo_subsample/yahoo_subsample_size=1000000.txt" },
	{ "yahoo10000000", "/home/liu2039/PasswordDataset/yahoo_subsample/yahoo_subsample_size=10000000.txt" },
	{ "yahoo-nonereq", "/home/liu2039/PasswordDataset/yahoo_password_frequencies_corpus/yahoo-reg-basic-v2.txt" },
	{ "yahoo-6charmin", "/home/liu2039/PasswordDataset/yahoo_password_frequencies_corpus/yahoo-reg-basic-v3.txt" },
	{ "yahoo-female", "/home/liu2039/PasswordDataset/yahoo_password_frequencies_corpus/yahoo-gender-female.txt" },
	{ "yahoo-male", "/home/liu2039/PasswordDataset/yahoo_password_frequencies_corpus/yahoo-gender-male.txt" },
	{ "yahoo-0y", "/home/liu2039/PasswordDataset/yahoo_password_frequencies_corpus/yahoo-tenure-_1y.txt" },
	{ "yahoo-1y", "/home/liu2039/PasswordDataset/yahoo_password_frequencies_corpus/yahoo-tenure-1y.txt" },
	{ "yahoo-2y", "/home/liu2039/PasswordDataset/yahoo_password_frequencies_corpus/yahoo-tenure-2y.txt" },
	{ "yahoo-3y", "/home/liu2039/PasswordDataset/yahoo_password_frequencies_corpus/yahoo-tenure-3y.txt" },
	{ "yahoo-4y", "/home/liu2039/PasswordDataset/yahoo_password_frequencies_corpus/yahoo-tenure-4y.txt" },
	{ "yahoo-5-10y", "/home/liu2039/PasswordDataset/yahoo_password_frequencies_corpus/yahoo-tenure-5-10y.txt" },
	{ "yahoo-reset0", "/home/liu2039/PasswordDataset/yahoo_password_frequencies_corpus/yahoo-activity-pw-rec-count-0.txt" },
	{ "yahoo-reset1", "/home/liu2039/PasswordDataset/yahoo_password_frequencies_corpus/yahoo-activity-pw-rec-count-1.txt" },
	{ "yahoo-reset_1", "/home/liu2039/PasswordDataset/yahoo_password_frequencies_corpus/yahoo-activity-pw-rec-count-_1.txt" },
	{ "yahoo-resetGeq5", "/home/liu2039/PasswordDataset/yahoo_password_frequencies_corpus/yahoo-activity-pw-rec-count-_5.txt" },
};

//The function running experiments described in my [SP:BloLiu23] paper with Linear Programming Tasks
//Consider the difference between the mesh values we generated and the actual mesh values
void myunseen_experiment2(string dname, string LPname);
//The Linear Programming Task 2 and 3 described in our [SP:BloLiu23] paper (the final LP -- LPlower, LPupper)
//Consider the difference between the mesh values we generated and the real probabilities
// Consider infinite probabilities
//Note: the e3s is not the same e3 parameter in myLP
int myLP2(string myobj, string dname, double & curBound, double G, long idx, double LPmass, long imax, vector<double>& e2s, vector<double>& e3s, vector<double>& xe3s, double gridFactor, long N, vector<double>& xLP, long szLPx, long unique, unordered_map<long, long>& freqcountmap);

//The Linear Programming Task 1a in our [SP:BloLiu23] paper, i.e., the intermidiate step
//Consider the real probabities perfectly match the mesh we generated
//Consider infinite probabilities
int myLP1a(string myobj, string dname, double & curBound, double G, long idx, double LPmass, long imax, vector<double>& e2s, double gridFactor, long N, vector<double>& xLP, long szLPx, long unique, unordered_map<long, long>& freqcountmap);

//The Linear Programming Task 1 in our [SP:BloLiu23] paper, i.e., the ideal case
//Consider the real probabities perfectly match the mesh we generated
//Consider finite probabilities
int myLP1(string myobj, string dname, double & curBound, double G, long idx, double LPmass, long imax, vector<double>& e2s, double gridFactor, long N, vector<double>& xLP, long szLPx, long unique, unordered_map<long, long>& freqcountmap);

//Convert bounds for lambda(S,G) to bounds for lambda_G
void lambdaSG_to_lambdaG(string dname, string LPname, double delta1);

int main()
{
	/*
	double h = 500;
	double p = h / 69301337.0;
	//cout << binopdf(h, 69301337, p) << endl;
	for (int i = h-100; i < h+100; i++) {
		cout << "i = " << i << "   cdf = " << binocdf(0, i, 69301337, p) << endl;
	}
	*/
	//vector<string> dname_list = {"yahoo", "rockyou", "000webhost", "neopets"};
	//vector<string> LPname_list = {"myLP2", "myLP1", "myLP1a"};
	//vector<string> dname_list = { "yahoo", "rockyou", "000webhost", "neopets", "bfield", "brazzers", "clixsense" , "csdn" };
	// vector<string> dname_list = { "yahoo10000", "yahoo100000", "yahoo1000000", "yahoo10000000" };
	// vector<string> dname_list = { "yahoo-nonereq", "yahoo-6charmin" };
	//vector<string> dname_list = { "yahoo-female", "yahoo-male", 
	//						"yahoo-5-10y","yahoo-0y", "yahoo-1y", "yahoo-2y", "yahoo-3y", "yahoo-4y",
	//						"yahoo-reset0", "yahoo-reset1", "yahoo-reset_1", "yahoo-resetGeq5" };
	vector<string> dname_list = { "PIN4digit-amitay-dp", "UserStudy_first-choice_4-digit" }; // { "PIN4digit-rockyou" };// { "UserStudy_first-choice_4-digit"}; //{ "PIN6digit-rockyou" };
	// vector<string> LPname_list = {"myLP2", "myLP1"};
	vector<string> LPname_list = {"myLP2"};
	for (int i=0; i<LPname_list.size(); i++) {
		for (int j=0; j<dname_list.size(); j++) {
			myunseen_experiment2(dname_list[j], LPname_list[i]);
			lambdaSG_to_lambdaG(dname_list[j], LPname_list[i], 0.00009);
		}
	}
	//myunseen_experiment2("neopets", "myLP2");
	//myunseen_experiment2("000webhost", "myLP2");
	//myunseen_experiment2("yahoo", "myLP2");
	//myunseen_experiment2("rockyou", "myLP2");
	//cin.get();
	//cin.get();
	return 0;
}

void myunseen_experiment2(string dname, string LPname) {
	//parameter setting
	// Read count, frequency from dataset
	string datasetname = dname; // "yahoo";
	ifstream fin;
	ofstream myfout;
	ofstream fout_parameter("./" + datasetname + "_parameters.txt");
	fin.open(datasetfilemap_workbench[datasetname]);
	cout << "start reading dataset " << datasetfilemap_workbench[datasetname] << endl;
	vector<long> count;
	vector<long> frequency;
	long curfreq, curcount;
	long unique = 0;
	unordered_map<long, long> freqcountmap; //key: frequency; value: count
	while (!fin.eof()) {
		curfreq = 0;
		curcount = 0;
		fin >> curfreq;
		fin >> curcount;
		if (curfreq == 0 && curcount == 0) {
			cout << "curfreq == 0 && curcount == 0" << endl;
			continue;
		}
		else {
			frequency.push_back(curfreq);
			count.push_back(curcount);
			freqcountmap[curfreq] = curcount;
			if (curfreq == 1) unique = curcount;
		}
	}

	cout << "end reading dataset " << datasetfilemap_workbench[datasetname] << endl;
	// unseen_largescale matlab code starts
	cout << "start setting parameters" << endl;
	if (count.size() != frequency.size()) {
		cout << "ERROR: count.size() != frequency.size()" << endl;
		exit(-1);
	}
	
	long k = 0;
	for (int i = 0; i<count.size(); i++) k += count[i] * frequency[i];
	cout << "k = " << k << endl;

	long cutoff = k; // 500;// 300; // 500;  //10000;
	///////// algorithm parameters /////////////
	// the grid of probabilities will be geometric, with this ratio.
	// setting this smaller may slightly increase accuracy, at the cost of speed
	double gridFactor = 1.002; // 1.005; // 1.05;
	//the allowable discrepancy between the returned solution and the "best" (overfit).
	// 0.5 worked well in all examples we tried, though the results were nearly indistinguishable 
	// for any alpha between 0.25 and 1.  Decreasing alpha increases the chances of overfitting. 
	//double alpha = 27;

	// new version of defining xLPmin; updated on 2023-01-13
	double xLPmin;
	
	if (k >= 10000) {
		xLPmin = 1.0 / (double)((double)k*(double)min((long)10000, max((long)10, k)));
	} else {
		xLPmin = 1.0 / (double)((double)k*10000.0);
	}
	/*
	// old version of defining xLPmin
	//original version, for large password dataset
	// if (min((long)10000, max((long)10, k)) != 10000) {
	//	cout << "ERROR: min((long)10000, max((long)10, k)) != 10000" << endl;
	//	cin.get();
	//	return;
	// }
	// double xLPmin = 1.0 / (double)((double)k*(double)min((long)10000, max((long)10, k)));
	
	// For small PIN dataset
	// double xLPmin = 1.0 / (double)((double)k*10000.0);
	*/

	double min_i = 0;
	while (count[min_i] <= 0) min_i++;
	if (min_i >= count.size()) {
		cout << "ERROR: min_i >= count.size()" << endl;
		exit(-1);
	}
	// minimum allowable probability. 
	// a more aggressive bound like 1/k^1.5 would make the LP slightly faster,
	// though at the cost of accuracy
	if (min_i > 1) xLPmin = min_i / (double)k;
	//////////////////////////////////////////////////
	cout << "setting parameters-1" << endl;
	// Split the fingerprint into the 'dense' portion for which we 
	// solve an LP to yield the corresponding histogram, and 'sparse' 
	// portion for which we simply use the empirical histogram
	vector<double> x_sparse, histx_sparse;
	for (int i = 0; i<frequency.size(); i++) {
		if (frequency[i] > cutoff) {
			x_sparse.push_back((double)frequency[i] / (double)k);
			histx_sparse.push_back(count[i]);
		}
	}
	cout << "setting parameters-2" << endl;
	vector<double> exp_f_emp(cutoff, 0.0);
	for (int i = 0; i<frequency.size(); i++) {
		if (frequency[i] > cutoff) {
			for (int j = 0; j<exp_f_emp.size(); j++) {
				exp_f_emp[j] += count[i] * binopdf(j + 1, k, (double)frequency[i] / (double)k);
			}
		}
	}
	cout << "setting parameters-3" << endl;
	vector<double> E_f(cutoff, 0.0);
	for (int i = 0; i<frequency.size(); i++) {
		if (frequency[i] <= cutoff) {
			E_f[frequency[i] - 1] += count[i];
		}
	}
	for (int i = 0; i<E_f.size(); i++) {
		E_f[i] -= exp_f_emp[i];
	}
	cout << "setting parameters-4" << endl;
	//Set up the first LP
	double mass_sparse = 0.0;
	for (int i = 0; i<x_sparse.size(); i++) {
		mass_sparse += x_sparse[i] * histx_sparse[i];
	}
	double LPmass = 1 - mass_sparse; // amount of probability mass in the LP region
	cout << "setting parameters-5" << endl;
	long szLPf = E_f.size();
	double xLPmax = (double)cutoff / (double)k;
	long max_exp_xLP = ceil(log(xLPmax / xLPmin) / log(gridFactor));
	//setup the mesh xLP
	vector<double> xLP(max_exp_xLP + 1, 0.0);
	for (int i = 0; i <= max_exp_xLP; i++) {
		//vector<double> xLP(max_exp_xLP - 12 + 1, 0.0);
		//for (int i = 12; i <= max_exp_xLP; i++) {
		// NOTE: in my code XLP[0] has the largest probablity
		// which is different from the unseen code!!
		// The original unseen code is xLP[i] = xLPmin * pow(gridFactor, max_exp_xLP); 
		xLP[max_exp_xLP - i] = xLPmin * pow(gridFactor, i);
		cout << "xLP[" << max_exp_xLP - i << "] = " << xLP[max_exp_xLP - i] << endl;
	}
	//cin.get();
	//cin.get();
	//xLP.push_back(pow(10.0, -30.0));
	//cout << "pow(10.0, -30.0) = " << pow(10.0, -30.0) << endl;
	long szLPx = xLP.size();
	cout << "end setting parameters" << endl;
	//unseen_largescale matlab code ends
	cout << "LPmass = " << LPmass << endl;
	cout << "start LP" << endl;
	//int status = LP_goodturing(szLPx, LPmass, k, minpguessing_idx, xLP, unique, freqcountmap);
	double sparseProb = mass_sparse;
	double sparseguessingnum = 0.0;
	for (int i = 0; i < histx_sparse.size(); i++)
		sparseguessingnum += histx_sparse[i];
	//cout << "sparseguessingnum = " << sparseguessingnum << endl; ////////no sparse, it should be zero.
	//cin.get();
	vector<string> myobj = { "min", "max" }; // min: lowerbound; max: upperbound
	int i1 = 1;

	long imax = 4;

	double e1;
	vector<double> e2s(imax+1,0.0);
	vector<double> e3s(imax+1,0.0);
	vector<double> xe3s(imax+1,0.0);
	//select the parameter for each dataset differently
	/*
	if (dname == "yahoo") {
		e1 = 0.00026;
		e2s = {0.00027,0.0005,0.00064,0.00086,0.0011}; //yahoo only
		xe3s = {7.0/(double)k, 11.0/(double)k, 14.0/(double)k, 16.5/(double)k, 19.0/(double)k};
	}
	else if (dname == "rockyou") {
		e1 = 0.00038;
		e2s = {0.00038, 0.00073, 0.000934, 0.00125, 0.00161}; //rockyou only
		xe3s = {7.0/(double)k, 11.0/(double)k, 14.0/(double)k, 16.5/(double)k, 19.0/(double)k};
	}
	else if (dname == "000webhost") {
		e1 = 0.00055;
		e2s = {0.00056, 0.00107, 0.00137, 0.00182, 0.00235}; //000webhost only
		xe3s = {7.0/(double)k, 11.0/(double)k, 13.5/(double)k, 16.0/(double)k, 18.0/(double)k};
	}
	else if (dname == "neopets") {
		e1 = 0.00027;
		e2s = {0.00027,0.00051,0.00064,0.00087,0.00111}; //neopets only
		xe3s = {7.0/(double)k, 11.0/(double)k, 14.0/(double)k, 16.0/(double)k, 18.0/(double)k};
	}
	else {cout << "ERROR: no e1 and e2s and xe3s available for dataset" + dname << endl; cin.get();}

	for (int i=0; i<imax+1; i++) {
		e3s[i] = 1/pow(gridFactor,i+1)*pow((1-xe3s[i])/(1-gridFactor*xe3s[i]),k-i) - 1;
	}
	*/

	double delta1 = 0.00009;
	vector<double> delta2s(imax+1,0.0);
	if (imax == 4) {
		delta2s = {0.00009, 0.000165, 0.00175, 0.00175, 0.0012};
		xe3s = {7.0/(double)k, 11.0/(double)k, 14.0/(double)k, 16.3/(double)k, 18.5/(double)k};
	}
	else {cout << "ERROR: no delta2s, xe3s available for imax = " << imax << endl; cin.get();}
	
	/*
	// #########temporately added to compute the bound with confidence=0.95; (08/11/21) need to be removed#########################
	delta1 *= 5;
	for (int i=0; i<delta2s.size(); i++) {
		delta2s[i] *= 5;
	}
	// #######################################################################
	*/

	e1 = sqrt(log(delta1)/((-2)*k));
	for (int i=0; i<imax+1; i++) {
		e2s[i] = sqrt(log(delta2s[i])*k*(i+1)*(i+1) / ((-2)*(k-i)*(k-i)));
		e3s[i] = 1/pow(gridFactor,i+1)*pow((1-xe3s[i])/(1-gridFactor*xe3s[i]),k-i) - 1;
	}

	cout << "e1 = " << e1 << endl; 
	fout_parameter << "e1 = " << e1 << endl; 
	for (int i=0; i<e2s.size(); i++) {
		cout << e2s[i] << " ";
		fout_parameter << e2s[i] << " ";
	}
	cout << endl;
	fout_parameter << endl;
	for (int i=0; i<e3s.size();i++) {
		cout << e3s[i] << " "; 
		fout_parameter << e3s[i] << " "; 
	}
	cout << endl;
	fout_parameter << endl;
	double exception_p = delta1;
	for (int i=0; i<imax+1; i++) {exception_p += 2*delta2s[i];}
	cout << "exception probability = " << exception_p 
		<< ",  total probbability LP holds = " <<  1 - exception_p << endl;
	fout_parameter << "exception probability = " << exception_p 
		<< ",  total probbability LP holds = " <<  1 - exception_p << endl;
	fout_parameter.close();
	//cin.get();

	if (e2s.size() != imax+1) {cout << "ERROR: e2s.size() != imax+1" << endl; cin.get();}
	//vector<double> e3s = {0.0121,0.0182,0.0222,0.0253,0.0284};
	if (e3s.size() != imax+1) {cout << "ERROR: e3s.size() != imax+1" << endl; cin.get();}
	//vector<double> xe3s = {7.0/(double)k, 11.0/(double)k, 14.0/(double)k, 16.5/(double)k, 19/(double)k};
	if (xe3s.size() != imax+1) {cout << "ERROR: xe3s.size() != imax+1" << endl; cin.get();}
	//vector<double> e2s = {0.00027,0.0005,0.00064,0.00086,0.0011}; //yahoo only
	//vector<double> e2s = {0.00038, 0.00073, 0.000934, 0.00125, 0.00161}; //rockyou only

	LPmass = 1;

	// upperbound (i1=1) and lowerbound (i1=0)
	//for (i1 = 1; i1 >= 0; i1--) {
	for (i1 = 0; i1 <= 1; i1++) {
	// for (i1 = 0; i1 <= 0; i1++) {
		//myfout.open("myLP2" + datasetname + "_" + myobj[i1] + "_cutoff=" + to_string(cutoff) + ".txt");
		myfout.open(LPname + "-" + datasetname + "_" + myobj[i1] + "_cutoff=" + to_string(cutoff) + ".txt");
		myfout << "%" << datasetname << endl;
		myfout << "\\addplot coordinates {";
		double prebound = 0.0;
		/*
		double start = 1;
		if (datasetname == "000webhost") start = pow(2, 27);
		else if (datasetname == "neopets") start = pow(2, 28);
		else if (datasetname == "bfield") start = pow(2, 22);
		else if (datasetname == "brazzers") start = pow(2, 22);
		else if (datasetname == "clixsense") start = pow(2, 24);
		else if (datasetname == "csdn") start = pow(2, 25);
		*/
		//[To DO:] add constraints to G and idx to omit running unnecessary LP
		//for (double G = 1; G < 1 / xLP[max_exp_xLP]; G = G * 2) {
		//for (double G = pow(2, 26)+2*pow(10,7); G < pow(2,27); G = G+2*pow(10,7)) {
		//for (double G = start; G <= start*8; G = G * 2) {
		/*** The original for loop condition that is used in the password distribution paper
		// for (double G = 1; G < pow(10,12); G = G * 2) {
		***/
		double maxG = pow(10,12);
		if (PINorPWD[dname] == "4-digit") {
			maxG = pow(10,4);
		} else if (PINorPWD[dname] == "6-digit") {
			maxG = pow(10,6);
		}
		auto updateG = [&dname, &maxG](double G) {
			double next = G;
			if (PINorPWD[dname] == "4-digit") {
				while (next == G) {
					next = ceil(G*pow(10,0.1));
				}
			} else if (PINorPWD[dname] == "6-digit") {
				while (next == G) {
					next = ceil(G*pow(10,0.125));
				}
			} else {
				next = G*2;
			}
			if (G < maxG && next > maxG) {
				return maxG;
			} else {
				return next;
			}
		};
		for (double G = 1; G <= maxG; G = updateG(G)) {
		// for (double G = 10000; G <= maxG; G = G*2) {
			double bound;
			if (myobj[i1] == "max") bound = -2000;
			else bound = 2000;
			long max_idx;
			if (LPname == "myLP2" || LPname == "myLP1a") max_idx = szLPx;
			else if (LPname == "myLP1") max_idx = szLPx - 1;
			else {cout << "ERROR: No available max_idx for LPname = " << LPname << endl; cin.get(); }
			//for (long idx = 0; idx <= szLPx - 1; idx++) {
			//for (long idx = 0; idx <= szLPx; idx++) {
			for (long idx = 0; idx <= max_idx; idx++) {
				double curBound = -100;
				int status;
				if (LPname == "myLP2") status = myLP2(myobj[i1], datasetname, curBound, G, idx, LPmass, imax, e2s, e3s, xe3s, gridFactor, k, xLP, szLPx, unique, freqcountmap);
				else if (LPname == "myLP1a") status = myLP1a(myobj[i1], datasetname, curBound, G, idx, LPmass, imax, e2s, gridFactor, k, xLP, szLPx, unique, freqcountmap);
				else if (LPname == "myLP1") status = myLP1(myobj[i1], datasetname, curBound, G, idx, LPmass, imax, e2s, gridFactor, k, xLP, szLPx, unique, freqcountmap);
				else {cout << "ERROR: No available LP for LPname = " << LPname << endl; cin.get(); }
				if (status == GRB_OPTIMAL) {
					if ((myobj[i1] == "max" && bound < curBound) || (myobj[i1] == "min" && bound > curBound)) {
						bound = curBound;
					}
				}
				else if (status == GRB_INFEASIBLE) {
					continue;
				}
				else {
					cout << "idx = " << idx << "ERROR: status = " << status << "  curBound = " << curBound << endl;
					//cin.get();
				}
			}
			/*
			if (LPname == "myLP1") {  //////////////just for generating guessing curves to compare with myLP2
				if (G > k && (bound-prebound)/(G/2.0) < xLPmin * (1.0001)) break;
				else prebound = bound;  
			}
			*/
			// Computing lambda(S,G)
			if (myobj[i1] == "min") myfout << " (" << G << ", " << (bound-e1) * 100 << ")" << endl;
			else myfout << " (" << G << ", " << (bound+e1) * 100 << ")" << endl;

			if ((myobj[i1] == "min" && (bound-e1)>=1) || (myobj[i1] == "max" && (bound+e1)>=1)) break;
			//if (bound * 100 > 100) break;
		}

		myfout << "};" << endl;
		myfout.close();
	}
	cout << "end LP" << endl;
}


int myLP2(string myobj, string dname, double & curBound, double G, long idx, double LPmass, long imax, vector<double>& e2s, vector<double>& e3s, vector<double>& xe3s, double gridFactor, long N, vector<double>& xLP, long szLPx, long unique, unordered_map<long, long>& freqcountmap) {
	try {
		//ofstream foutest("warningtest_" + myobj + ".log");
		//foutest << G << "  " << idx << "  " << imax << endl;
		// Create an environment
		GRBEnv env = GRBEnv(true);
		string logfilename;
		if (myobj == "min") logfilename = "LP2_" + dname + "_min.log";
		else if (myobj == "max") logfilename = "LP2_" + dname + "_max.log";
		else logfilename = "LP2_" + myobj + "_" + dname + ".log";
		env.set("LogFile", logfilename);
		env.start();

		// Create an empty model
		GRBModel model = GRBModel(env);
		//model.set("TimeLimit", "7200.0"); //Optimization terminates after 2hours
		//model.set("SolutionLimit", "1"); //Optimization terminates after finding 1 solution
		model.set("NumericFocus", "3");
		model.set("ScaleFlag", "0");
		//model.set("LogToConsole", "0");
		// Create variables
		//Hi: h_i*xLP[i], where h_i is the total number of passwords that has probability xLP[i] (histogram)
		vector<GRBVar> Hvars(szLPx);

		//Hvars represents h*x
		for (int i = 0; i < szLPx; i++) {
			string vname = "H" + to_string(i);
			//Hvars[i] = model.addVar(0.0, GRB_INFINITY, 0.0, GRB_CONTINUOUS, vname);
			Hvars[i] = model.addVar(0.0, 1.0, 0.0, GRB_CONTINUOUS, vname);
		}
		// Cvar = count*xLP[minpguessing_idx]
		//GRBVar Cvar = model.addVar(0.0, GRB_INFINITY, 0.0, GRB_CONTINUOUS, "Cvar");
		GRBVar Cvar = model.addVar(0.0, 1.0, 0.0, GRB_CONTINUOUS, "Cvar");
		//p
		GRBVar Pvar = model.addVar(0.0, 1.0, 0.0, GRB_CONTINUOUS, "Pvar");

		// Set objective: maximize x + y + 2 z
		GRBLinExpr obj = 0.0;

		for (int i = 0; i < idx; i++) { 
			obj += Hvars[i];
		}
		if (idx < szLPx || myobj == "max") obj += Cvar;
		//else: do nothing
		
		if (myobj == "min") model.setObjective(obj, GRB_MINIMIZE);
		else if (myobj == "max") model.setObjective(obj, GRB_MAXIMIZE);
		else {
			cout << "ERROR: invalid myobj = " << myobj << endl;
			cin.get();
		}

		/*
		for (int i = 0; i < szLPx; i++) {
			if (1 / xLP[i] > GRB_MAXINT) {
				double ub = GRB_MAXINT *  xLP[i];
				model.addConstr(Hvars[i] <= ub, "Hvars[i] <= GRB_MAXINT * xLP[i]");
			}
		}
		*/

		for (int i = 0; i < szLPx; i++) {
			model.addConstr(Hvars[i] >= 0.0, "Hvars["+to_string(i)+"]>=0");
			model.addConstr(Hvars[i] <= 1.0, "Hvars["+to_string(i)+"]<=1");
		}
		model.addConstr(Cvar >= 0.0, "Cvar>=0");
		model.addConstr(Pvar >= 0.0, "Pvar>=0");
		model.addConstr(Pvar <= 1.0, "Pvar<=1");
	
		//Add constraints: 0 <= Cvar <= Hvars[idx]
		if (idx < szLPx) model.addConstr(Cvar <= Hvars[idx], "Cvar<=Hvars[idx]");
		else model.addConstr(Cvar <= 1.0, "Cvar<=1.0");
		//Add constraints: LPmass == 1: 
		//for lowerbound: (1-p)/q <= \sum_i Hvars[i] <= 1-p
		//for upperbound 1-p <= \sum_i Hvars[i] <= q*(1-p)
		GRBLinExpr LPmass_constraint = 0.0;
		for (int i = 0; i<szLPx; i++) {
			LPmass_constraint += Hvars[i]; // Hvars[i] * xLP[i];
		}
		if (myobj == "min") {
			model.addConstr(LPmass_constraint <= LPmass-Pvar, "sum_Hvars[i]*xLP[i]<=LPmass-Pvar");
			model.addConstr(LPmass_constraint >= (LPmass-Pvar)/gridFactor, "sum_Hvars[i]*xLP[i]>=(LPmass-Pvar)/gridFactor");
		}
		else { // myobj == "max"
			model.addConstr(LPmass_constraint <= gridFactor*(LPmass-Pvar), "sum_Hvars[i]*xLP[i]<=gridFactor*(LPmass-Pvar)");
			model.addConstr(LPmass_constraint >= LPmass-Pvar, "sum_Hvars[i]*xLP[i]>=LPmass-Pvar");
		}
		
		//Add constraints: for small i<=imax (e.g. i=0,1,...,4),
		//(i+1)*frequency_{i+1}/(N+1) - e2 <= \sum_j Hvars[j]*binopdf(i,k,xLP[j]) <= (i+1)*frequency_{i+1}/(N+1)+e2
		// Good-Turing Approximation
		vector<GRBLinExpr> GoodTuring_constraints(imax+1, 0.0);
		for (int i = 0; i <= imax; i++) {
			for (int j = 0; j < Hvars.size(); j++) {
				double curbinopdf = binopdf(i, N, xLP[j]);
				if (curbinopdf < 0) {
					cout << "binopdf(" << i << ", " << N << ", " << xLP[j] << ") = " << curbinopdf << endl
						<< "j = " << j << endl;
					cin.get();
				}
				if (curbinopdf <= pow(10.0, -13.0)) curbinopdf = 0;
				GoodTuring_constraints[i] += Hvars[j] * curbinopdf;
			}
			//if (freqcountmap[i + 1] == 0) continue; //Is it the correct to ignore frequency_i when frequency_i=0?
			if (myobj == "min") {
				string cname1 = "goodturing-upperbound-i="+to_string(i);
				// CCS 21 version
				// if (i == 0) model.addConstr(GoodTuring_constraints[i] <= (1+e3s[i])*((i + 1)*(double)freqcountmap[i + 1] / (double)(N-i) + e2s[i]-Pvar*binopdf(i,N,xLP[szLPx-1]))+binopdf(i,N,xe3s[i]), cname1);
				// New
				if (i == 0) model.addConstr(GoodTuring_constraints[i] <= (1+e3s[i])*((i + 1)*(double)freqcountmap[i + 1] / (double)(N-i) + e2s[i]-Pvar*binopdf(i,N,gridFactor * xLP[szLPx-1]))+binopdf(i,N,xe3s[i]), cname1);
				else model.addConstr(GoodTuring_constraints[i] <= (1+e3s[i])*((i + 1)*(double)freqcountmap[i + 1] / (double)(N-i) + e2s[i])+binopdf(i,N,xe3s[i]), cname1);
				string cname2 = "goodturing-lowerbound-i="+to_string(i);
				if (i == 0) model.addConstr(GoodTuring_constraints[i] >= 1.0/ pow(gridFactor, i + 1)*((i + 1)*(double)freqcountmap[i + 1] / (double)(N-i) - e2s[i] - (i+1)/(double)(N-i) - Pvar), cname2);
				else {
					// CCS 21 version
					// double tmpbpdf = binopdf(i,N,xLP[szLPx-1]);
					// New 
					double tmpbpdf = binopdf(i,N,gridFactor * xLP[szLPx-1]);
					if (tmpbpdf <= pow(10.0, -13.0)) tmpbpdf = 0;
					// CCS 21 version
					// model.addConstr(GoodTuring_constraints[i] >= 1.0/ pow(gridFactor, i + 1)*((i + 1)*(double)freqcountmap[i + 1] / (double)(N-i) - e2s[i] - (i+1)/(double)(N-i) - tmpbpdf), cname2);
					// New
					model.addConstr(GoodTuring_constraints[i] >= 1.0/ pow(gridFactor, i + 1)*((i + 1)*(double)freqcountmap[i + 1] / (double)(N-i) - e2s[i] - (i+1)/(double)(N-i) - Pvar*tmpbpdf), cname2);
				}
			}
			else { //myobj == "max"
				string cname1 = "goodturing-upperbound-i="+to_string(i);
				if (i == 0) model.addConstr(GoodTuring_constraints[i] <= pow(gridFactor, i + 1)*((i + 1)*(double)freqcountmap[i + 1] / (double)(N-i) + e2s[i]-Pvar*binopdf(i,N,xLP[szLPx-1])), cname1);
				else model.addConstr(GoodTuring_constraints[i] <= pow(gridFactor, i + 1)*((i + 1)*(double)freqcountmap[i + 1] / (double)(N-i) + e2s[i]), cname1);
				string cname2 = "goodturing-lowerbound-i="+to_string(i);
				// CCS 21 version
				// if (i == 0) model.addConstr(GoodTuring_constraints[i] >= 1.0/(1+e3s[i]) *((i + 1)*(double)freqcountmap[i + 1] / (double)(N-i) - e2s[i] - (i+1)/(double)(N-i) - Pvar - binopdf(i,N,xe3s[i])), cname2);
				// New
				if (i == 0) model.addConstr(GoodTuring_constraints[i] >= 1.0/(1+e3s[i]) *((i + 1)*(double)freqcountmap[i + 1] / (double)(N-i) - e2s[i] - (i+1)/(double)(N-i) - Pvar - binopdf(i,N,gridFactor * xe3s[i])), cname2);
				else {
					double tmpbpdf = binopdf(i,N,xLP[szLPx-1]);
					if (tmpbpdf <= pow(10.0, -13.0)) tmpbpdf = 0;
					// CCS 21 version
					// model.addConstr(GoodTuring_constraints[i] >= 1.0/(1+e3s[i]) *((i + 1)*(double)freqcountmap[i + 1] / (double)(N-i) - e2s[i] - (i+1)/(double)(N-i) - tmpbpdf - binopdf(i,N,xe3s[i])), cname2);
					// New
					model.addConstr(GoodTuring_constraints[i] >= 1.0/(1+e3s[i]) *((i + 1)*(double)freqcountmap[i + 1] / (double)(N-i) - e2s[i] - (i+1)/(double)(N-i) - Pvar * tmpbpdf - binopdf(i,N,gridFactor * xe3s[i])), cname2);
				}
			}
		}
		
		//Add constraints: \sum_{i<idx} Hvars[i] / xLP[i] + Cvar / xLP[idx] == G
		GRBLinExpr G_constraint = 0.0;
		if (idx < szLPx) {
			double G_scale = xLP[idx]; // pow(10, -9);
			if (G * G_scale >= 1) G_scale = 1.0 / G;
			for (int i = 0; i < idx; i++) {
				double coef_tmp = G_scale / xLP[i];
				//G_constraint += Hvars[i] / xLP[i] * G_scale;
				G_constraint += Hvars[i] * coef_tmp;
				//foutest << coef_tmp << endl;
			}
			double coef_tmp = G_scale / xLP[idx];
			//G_constraint += Cvar / xLP[idx] * G_scale;
			G_constraint += Cvar * coef_tmp;
			//foutest << coef_tmp << endl;
			//foutest.close();
			if (myobj == "max") model.addConstr(G_constraint <= G * G_scale, "G_constraint");
			else model.addConstr(G_constraint >= G * G_scale, "G_constraint");
		}
		else {
			double G_scale = xLP[idx-1]; // pow(10, -9);
			if (G * G_scale >= 1) G_scale = 1.0 / G;
			for (int i = 0; i < idx; i++) {
				double coef_tmp = G_scale / xLP[i];
				//G_constraint += Hvars[i] / xLP[i] * G_scale;
				G_constraint += Hvars[i] * coef_tmp;
				//foutest << coef_tmp << endl;
			}
			if (myobj == "max") {
				double coef_tmp = G_scale / xLP[szLPx-1];
				G_constraint += Cvar * coef_tmp;
				model.addConstr(G_constraint <= G * G_scale, "G_constraint");
			}
			else model.addConstr(G_constraint <= G * G_scale, "G_constraint");
		}
		
		//Only used to test PIN digitSize-digit (4-digit, 6-digit) dataset
		if (PINorPWD.find(dname) == PINorPWD.end()) {
			cout << "Is this dataset a PIN dataset or a Password dataset?" << endl;
			cout << "Please enter \"4-digit\" or \"6-digit\" or \"PWD\": ";
			string enterPINorPWD;
			cin >> enterPINorPWD;
			while (enterPINorPWD != "4-digit" || enterPINorPWD != "6-digit" || enterPINorPWD != "PWD") {
				cout << "Please enter \"4-digit\" or \"6-digit\" or \"PWD\": ";
				cin >> enterPINorPWD;
			}
			PINorPWD[dname] = enterPINorPWD;
		}
		if (PINorPWD[dname] == "4-digit" || PINorPWD[dname] == "6-digit") {
			int digitSize;
			if (PINorPWD[dname] == "4-digit") {
				digitSize = 4;
			} else if (PINorPWD[dname] == "6-digit") {
				digitSize = 6;
			}
			//cout << "digitSize = " << digitSize << endl;
			//cin.get();
			/*
			// old one
			//Add constraints: \sum_{i} Hvars[i] / xLP[i] <= 10^digitSize
			GRBLinExpr PINDigit_constraint1 = 0.0;
			double H_scale = xLP[szLPx-1]; // pow(10, -digitSize);
			if (pow(10, digitSize) * H_scale >= 1) H_scale = 1.0 / pow(10, -digitSize);
			for (int i = 0; i<szLPx; i++) {
				double coef_tmp = H_scale / xLP[i];
				PINDigit_constraint1 += Hvars[i] * coef_tmp; 
			}
			model.addConstr(PINDigit_constraint1 <= pow(10,digitSize) * H_scale, "DigitPinConstraint1");
			
			//Add constraints: xLP[szLPx-1]*(10^digitSize-\sum_{i} Hvars[i]/xLP[i])-Pvar>=0
			GRBLinExpr PINDigit_constraint2 = 0.0;
			PINDigit_constraint2 += xLP[szLPx-1] * pow(10,digitSize);
			for (int i=0; i<szLPx; i++) {
				double coef_tmp = xLP[szLPx-1] / xLP[i];
				PINDigit_constraint2 -= Hvars[i] * coef_tmp; 
			}
			double H2_scale = 1;
			if (xLP[szLPx-1] * pow(10,digitSize) > 1) H2_scale = 1 / (xLP[szLPx-1] * pow(10,digitSize));
			model.addConstr(H2_scale * PINDigit_constraint2 >= H2_scale * Pvar, "DigitPinConstraint2");
			*/
			// 2023-01-19 new one
			//Add constraints: \sum_{i} Hvars[i] / xLP[i] <= 10^digitSize
			
			GRBLinExpr PINDigit_constraint1 = 0.0;
			double H_scale = 1.0 / (double)pow(10, digitSize+4); // use +4 to avoid warnings of scaling in gurobi
			for (int i = 0; i<szLPx; i++) {
				double coef_tmp = H_scale / xLP[i];
				PINDigit_constraint1 += Hvars[i] * coef_tmp; 
			}
			model.addConstr(PINDigit_constraint1 <= pow(10,digitSize) * H_scale, "DigitPinConstraint1");

			//Add constraints: xLP[szLPx-1]*(10^digitSize-\sum_{i} Hvars[i]/xLP[i])-Pvar>=0
			GRBLinExpr PINDigit_constraint2 = 0.0;
			PINDigit_constraint2 += 1;
			for (int i=0; i<szLPx; i++) {
				double coef_tmp = 1.0 / xLP[i] / (double)pow(10,digitSize+4); // use +4 to avoid warnings of scaling in gurobi
				PINDigit_constraint2 -= Hvars[i] * coef_tmp; 
			}
			model.addConstr(PINDigit_constraint2 >= Pvar / xLP[szLPx-1] / (double)pow(10,digitSize+4), "DigitPinConstraint2"); // use +4 to avoid warnings of scaling in gurobi
		} 
		//end Only used to test PIN digitSize (4,6)-digit dataset

		//double tolerance = pow(10.0, -4.0);
		//////model.addConstr(L1result_constraint == L1result, "L1result_constraint");
		//model.addConstr(L1result_constraint <= (1.0 + tolerance) * L1result, "L1result_constraint1");
		//model.addConstr(L1result_constraint >= (1.0 - tolerance) * L1result, "L1result_constraint2");

		//model.write("mymodel.mps");

		// Optimize model
		model.optimize();
		//double currentlimit = model.get(GRB_DoubleParam_TimeLimit);
		//cout << "GRB_DoubleParam_TimeLimit = " << currentlimit << endl;
		int status = model.get(GRB_IntAttr_Status);
		if (status == GRB_OPTIMAL) {
			cout << "The optimal objective is " << model.get(GRB_DoubleAttr_ObjVal) << endl;
			curBound = model.get(GRB_DoubleAttr_ObjVal); 
		}
		else if (status == GRB_SOLUTION_LIMIT) {
			cout << "The number of solutions found reached the value specified in the SolutionLimit parameter" << endl;
		}
		else if (status == GRB_TIME_LIMIT) {
			cout << "Optimization terminated because the time expended exceeded the value specified in the TimeLimit parameter." << endl;
		}
		else {
			cout << "Optimization was stopped with status " << status << endl;
			if (status == GRB_INFEASIBLE) {
				cout << "The model is infeasible" << endl;
			}
			else {
				cout << "The model is NOT infeasible but didn't output optimal result!" << endl;
				//exit(-1);
				//cin.get();
			}
		}
		/*
		//for debugging purpose
		if (status != GRB_INFEASIBLE) {
			ofstream testlog; 
			testlog.open("LP2_" + myobj + "_" + dname + "_testlog.txt", std::ios_base::app);
			testlog << "idx = " << idx << "  G = " << G << "  status = " << status << endl;
			int digitSize;
			if (PINorPWD[dname] == "4-digit") {
				digitSize = 4;
			} else if (PINorPWD[dname] == "6-digit") {
				digitSize = 6;
			}

			double supporth = 0.0;
			double H_scale = 1.0 / (double)pow(10, digitSize+4);
			for (int i = 0; i<szLPx; i++) {
				double coef_tmp = H_scale / xLP[i];
				supporth += Hvars[i].get(GRB_DoubleAttr_X) * coef_tmp; 
			}
			testlog << "supporth = " << supporth 
					<< "; pow(10,digitSize) * H_scale = " 
					<< pow(10,digitSize) * H_scale
					<< "; (supporth <= pow(10,digitSize) * H_scale) = "
					<< (supporth <= pow(10,digitSize) * H_scale)
					<< endl;
			double sumh_scale = 0.0;
			sumh_scale += 1.0;
			for (int i=0; i<szLPx; i++) {
				double coef_tmp = 1.0 / xLP[i] / (double)pow(10,digitSize+4);
				sumh_scale -= Hvars[i].get(GRB_DoubleAttr_X) * coef_tmp; 
			}
			testlog << "sumh_scale = " << sumh_scale
					<< ";  Pvar.get(GRB_DoubleAttr_X) / xLP[szLPx-1] / (double)pow(10,digitSize+4) = " 
					<<  Pvar.get(GRB_DoubleAttr_X) / xLP[szLPx-1] / (double)pow(10,digitSize+4)
					<< endl;
			testlog << "(sumh_scale >=  Pvar.get(GRB_DoubleAttr_X) / xLP[szLPx-1] / (double)pow(10,digitSize+4)) = "
					<< (sumh_scale >=  Pvar.get(GRB_DoubleAttr_X) / xLP[szLPx-1] / (double)pow(10,digitSize+4)) << endl;
		
			double sumh = 0.0;
			for (int i=0; i<szLPx; i++) {
				sumh += Hvars[i].get(GRB_DoubleAttr_X) / xLP[i];
				if (Hvars[i].get(GRB_DoubleAttr_X) / xLP[i] == 0.0) continue;
				testlog << "Hvars[" + to_string(i) + "].get(GRB_DoubleAttr_X) / xLP[" + to_string(i) + "] = " 
						<< Hvars[i].get(GRB_DoubleAttr_X) / xLP[i] 
						<< endl;
			}
			testlog << "sumh = " << sumh 
					<< ";  pow(10,digitSize) - sumh = " << pow(10,digitSize) - sumh
					<< ";  Pvar.get(GRB_DoubleAttr_X) / xLP[szLPx-1] = "
					<< Pvar.get(GRB_DoubleAttr_X) / xLP[szLPx-1]
					<< ";  (pow(10,digitSize) - sumh > Pvar.get(GRB_DoubleAttr_X) / xLP[szLPx-1]) = "
					<< (pow(10,digitSize) - sumh > Pvar.get(GRB_DoubleAttr_X) / xLP[szLPx-1])
					<< endl;
			testlog << "Obj: " << model.get(GRB_DoubleAttr_ObjVal) << endl;
			testlog << endl;
			testlog.close();
		}
		//end for debugging purpose
		*/
		return status;
	}
	catch (GRBException e) {
		cout << "Error code = " << e.getErrorCode() << endl;
		cout << e.getMessage() << endl;
		cin.get();
	}
	catch (...) {
		cout << "Exception during optimization" << endl;
		cin.get();
	}
	cout << "ERROR: gurobi try/catch error!!" << endl;
	cin.get();
	return -110;
}


int myLP1a(string myobj, string dname, double & curBound, double G, long idx, double LPmass, long imax, vector<double>& e2s, double gridFactor, long N, vector<double>& xLP, long szLPx, long unique, unordered_map<long, long>& freqcountmap) {
	try {
		//ofstream foutest("warningtest_" + myobj + ".log");
		//foutest << G << "  " << idx << "  " << imax << endl;
		// Create an environment
		GRBEnv env = GRBEnv(true);
		string logfilename;
		if (myobj == "min") logfilename = "LP1a_" + dname + "_min.log";
		else if (myobj == "max") logfilename = "LP1a_" + dname + "_max.log";
		else logfilename = "LP1a_" + myobj + "_" + dname + ".log";
		env.set("LogFile", logfilename);
		env.start();

		// Create an empty model
		GRBModel model = GRBModel(env);
		//model.set("TimeLimit", "7200.0"); //Optimization terminates after 2hours
		//model.set("SolutionLimit", "1"); //Optimization terminates after finding 1 solution
		model.set("NumericFocus", "3");
		//model.set("LogToConsole", "0");
		// Create variables
		//Hi: h_i*xLP[i], where h_i is the total number of passwords that has probability xLP[i] (histogram)
		vector<GRBVar> Hvars(szLPx);

		//Hvars represents h*x
		for (int i = 0; i < szLPx; i++) {
			string vname = "H" + to_string(i);
			//Hvars[i] = model.addVar(0.0, GRB_INFINITY, 0.0, GRB_CONTINUOUS, vname);
			Hvars[i] = model.addVar(0.0, 1.0, 0.0, GRB_CONTINUOUS, vname);
		}
		// Cvar = count*xLP[minpguessing_idx]
		//GRBVar Cvar = model.addVar(0.0, GRB_INFINITY, 0.0, GRB_CONTINUOUS, "Cvar");
		GRBVar Cvar = model.addVar(0.0, 1.0, 0.0, GRB_CONTINUOUS, "Cvar");
		//p
		GRBVar Pvar = model.addVar(0.0, 1.0, 0.0, GRB_CONTINUOUS, "Pvar");

		// Set objective: maximize x + y + 2 z
		GRBLinExpr obj = 0.0;

		for (int i = 0; i < idx; i++) { 
			obj += Hvars[i];
		}
		if (idx < szLPx || myobj == "max") obj += Cvar;
		//else: do nothing
		
		if (myobj == "min") model.setObjective(obj, GRB_MINIMIZE);
		else if (myobj == "max") model.setObjective(obj, GRB_MAXIMIZE);
		else {
			cout << "ERROR: invalid myobj = " << myobj << endl;
			cin.get();
		}

	
		//Add constraints: 0 <= Cvar <= Hvars[idx]
		if (idx < szLPx) model.addConstr(Cvar <= Hvars[idx], "Cvar<=Hvars[idx]");
		else model.addConstr(Cvar <= 1.0, "Cvar<=1.0");
		//Add constraints: LPmass == 1: 
		//\sum_i Hvars[i] = 1-p
		GRBLinExpr LPmass_constraint = 0.0;
		for (int i = 0; i<szLPx; i++) {
			LPmass_constraint += Hvars[i]; // Hvars[i] * xLP[i];
		}
		model.addConstr(LPmass_constraint <= LPmass-Pvar, "sum_Hvars[i]*xLP[i]<=LPmass-Pvar");
		model.addConstr(LPmass_constraint >= LPmass-Pvar, "sum_Hvars[i]*xLP[i]>=LPmass-Pvar");
		
		//Add constraints: for small i<=imax (e.g. i=0,1,...,4),
		//(i+1)*frequency_{i+1}/(N+1) - e2 <= \sum_j Hvars[j]*binopdf(i,k,xLP[j]) <= (i+1)*frequency_{i+1}/(N+1)+e2
		// Good-Turing Approximation
		vector<GRBLinExpr> GoodTuring_constraints(imax+1, 0.0);
		for (int i = 0; i <= imax; i++) {
			for (int j = 0; j < Hvars.size(); j++) {
				double curbinopdf = binopdf(i, N, xLP[j]);
				if (curbinopdf < 0) {
					cout << "binopdf(" << i << ", " << N << ", " << xLP[j] << ") = " << curbinopdf << endl
						<< "j = " << j << endl;
					cin.get();
				}
				if (curbinopdf <= pow(10.0, -13.0)) curbinopdf = 0;
				GoodTuring_constraints[i] += Hvars[j] * curbinopdf;
			}
			//if (freqcountmap[i + 1] == 0) continue; //Is it the correct to ignore frequency_i when frequency_i=0?
			
			string cname1 = "goodturing-upperbound-i="+to_string(i);
			if (i == 0) model.addConstr(GoodTuring_constraints[i] <= (i + 1)*(double)freqcountmap[i + 1] / (double)(N-i) + e2s[i]-Pvar*binopdf(i,N,xLP[szLPx-1]), cname1);
			else model.addConstr(GoodTuring_constraints[i] <= (i + 1)*(double)freqcountmap[i + 1] / (double)(N-i) + e2s[i], cname1);
			string cname2 = "goodturing-lowerbound-i="+to_string(i);
			if (i == 0) model.addConstr(GoodTuring_constraints[i] >= (i + 1)*(double)freqcountmap[i + 1] / (double)(N-i) - e2s[i] - (i+1)/(double)(N-i) - Pvar, cname2);
			else {
				double tmpbpdf = binopdf(i,N,xLP[szLPx-1]);
				if (tmpbpdf <= pow(10.0, -13.0)) tmpbpdf = 0;
				model.addConstr(GoodTuring_constraints[i] >= (i + 1)*(double)freqcountmap[i + 1] / (double)(N-i) - e2s[i] - (i+1)/(double)(N-i) - Pvar*tmpbpdf, cname2);
			}
			
		}
		
		//Add constraints: \sum_{i<idx} Hvars[i] / xLP[i] + Cvar / xLP[idx] == G
		GRBLinExpr G_constraint = 0.0;
		if (idx < szLPx) {
			double G_scale = xLP[idx]; // pow(10, -9);
			if (G * G_scale >= 1) G_scale = 1.0 / G;
			for (int i = 0; i < idx; i++) {
				double coef_tmp = G_scale / xLP[i];
				//G_constraint += Hvars[i] / xLP[i] * G_scale;
				G_constraint += Hvars[i] * coef_tmp;
				//foutest << coef_tmp << endl;
			}
			double coef_tmp = G_scale / xLP[idx];
			//G_constraint += Cvar / xLP[idx] * G_scale;
			G_constraint += Cvar * coef_tmp;
			//foutest << coef_tmp << endl;
			//foutest.close();
			if (myobj == "max") model.addConstr(G_constraint <= G * G_scale, "G_constraint");
			else model.addConstr(G_constraint >= G * G_scale, "G_constraint");
		}
		else {
			double G_scale = xLP[idx-1]; // pow(10, -9);
			if (G * G_scale >= 1) G_scale = 1.0 / G;
			for (int i = 0; i < idx; i++) {
				double coef_tmp = G_scale / xLP[i];
				//G_constraint += Hvars[i] / xLP[i] * G_scale;
				G_constraint += Hvars[i] * coef_tmp;
				//foutest << coef_tmp << endl;
			}
			if (myobj == "max") {
				double coef_tmp = G_scale / xLP[szLPx-1];
				G_constraint += Cvar * coef_tmp;
				model.addConstr(G_constraint <= G * G_scale, "G_constraint");
			}
			else model.addConstr(G_constraint <= G * G_scale, "G_constraint");
		}
		

		//double tolerance = pow(10.0, -4.0);
		//////model.addConstr(L1result_constraint == L1result, "L1result_constraint");
		//model.addConstr(L1result_constraint <= (1.0 + tolerance) * L1result, "L1result_constraint1");
		//model.addConstr(L1result_constraint >= (1.0 - tolerance) * L1result, "L1result_constraint2");

		//model.write("mymodel.mps");

		// Optimize model
		model.optimize();
		//double currentlimit = model.get(GRB_DoubleParam_TimeLimit);
		//cout << "GRB_DoubleParam_TimeLimit = " << currentlimit << endl;
		int status = model.get(GRB_IntAttr_Status);
		if (status == GRB_OPTIMAL) {
			cout << "The optimal objective is " << model.get(GRB_DoubleAttr_ObjVal) << endl;
			curBound = model.get(GRB_DoubleAttr_ObjVal); 
		}
		else if (status == GRB_SOLUTION_LIMIT) {
			cout << "The number of solutions found reached the value specified in the SolutionLimit parameter" << endl;
		}
		else if (status == GRB_TIME_LIMIT) {
			cout << "Optimization terminated because the time expended exceeded the value specified in the TimeLimit parameter." << endl;
		}
		else {
			cout << "Optimization was stopped with status " << status << endl;
			if (status == GRB_INFEASIBLE) {
				cout << "The model is infeasible" << endl;
			}
			else {
				cout << "The model is NOT infeasible but didn't output optimal result!" << endl;
				//exit(-1);
				//cin.get();
			}
		}
		return status;
	}
	catch (GRBException e) {
		cout << "Error code = " << e.getErrorCode() << endl;
		cout << e.getMessage() << endl;
		cin.get();
	}
	catch (...) {
		cout << "Exception during optimization" << endl;
		cin.get();
	}
	cout << "ERROR: gurobi try/catch error!!" << endl;
	cin.get();
	return -110;
}


int myLP1(string myobj, string dname, double & curBound, double G, long idx, double LPmass, long imax, vector<double>& e2s, double gridFactor, long N, vector<double>& xLP, long szLPx, long unique, unordered_map<long, long>& freqcountmap) {
	try {
		//ofstream foutest("warningtest_" + myobj + ".log");
		//foutest << G << "  " << idx << "  " << imax << endl;
		// Create an environment
		GRBEnv env = GRBEnv(true);
		string logfilename;
		if (myobj == "min") logfilename = "LP1_" + dname + "_min.log";
		else if (myobj == "max") logfilename = "LP1_" + dname + "_max.log";
		else logfilename = "LP1_" + myobj + "_" + dname + ".log";
		env.set("LogFile", logfilename);
		env.start();

		// Create an empty model
		GRBModel model = GRBModel(env);
		//model.set("TimeLimit", "7200.0"); //Optimization terminates after 2hours
		//model.set("SolutionLimit", "1"); //Optimization terminates after finding 1 solution
		model.set("NumericFocus", "3");
		//model.set("LogToConsole", "0");
		// Create variables
		//Hi: h_i*xLP[i], where h_i is the total number of passwords that has probability xLP[i] (histogram)
		vector<GRBVar> Hvars(szLPx);

		//Hvars represents h*x
		for (int i = 0; i < szLPx; i++) {
			string vname = "H" + to_string(i);
			//Hvars[i] = model.addVar(0.0, GRB_INFINITY, 0.0, GRB_CONTINUOUS, vname);
			Hvars[i] = model.addVar(0.0, 1.0, 0.0, GRB_CONTINUOUS, vname);
		}
		// Cvar = count*xLP[minpguessing_idx]
		//GRBVar Cvar = model.addVar(0.0, GRB_INFINITY, 0.0, GRB_CONTINUOUS, "Cvar");
		GRBVar Cvar = model.addVar(0.0, 1.0, 0.0, GRB_CONTINUOUS, "Cvar");
		

		// Set objective: maximize x + y + 2 z
		GRBLinExpr obj = 0.0;

		for (int i = 0; i < idx; i++) { 
			obj += Hvars[i];
		}
		obj += Cvar;
		
		if (myobj == "min") model.setObjective(obj, GRB_MINIMIZE);
		else if (myobj == "max") model.setObjective(obj, GRB_MAXIMIZE);
		else {
			cout << "ERROR: invalid myobj = " << myobj << endl;
			cin.get();
		}

		
		//Add constraints: 0 <= Cvar <= Hvars[idx]
		model.addConstr(Cvar <= Hvars[idx], "Cvar<=Hvars[idx]");
		
		//Add constraints: LPmass == 1: 
		//\sum_i Hvars[i] = 1
		GRBLinExpr LPmass_constraint = 0.0;
		
		for (int i = 0; i<szLPx; i++) {
			LPmass_constraint += Hvars[i]; // Hvars[i] * xLP[i];
		}
		
		model.addConstr(LPmass_constraint <= LPmass, "sum_Hvars[i]*xLP[i]<=LPmass");
		model.addConstr(LPmass_constraint >= LPmass, "sum_Hvars[i]*xLP[i]>=LPmass");
		
		//Add constraints: for small i<=imax (e.g. i=0,1,...,4),
		//(i+1)*frequency_{i+1}/(N+1) - e2 <= \sum_j Hvars[j]*binopdf(i,k,xLP[j]) <= (i+1)*frequency_{i+1}/(N+1)+e2
		// Good-Turing Approximation
		vector<GRBLinExpr> GoodTuring_constraints(imax+1, 0.0);
		for (int i = 0; i <= imax; i++) {
			for (int j = 0; j < Hvars.size(); j++) {
				double curbinopdf = binopdf(i, N, xLP[j]);
				if (curbinopdf < 0) {
					cout << "binopdf(" << i << ", " << N << ", " << xLP[j] << ") = " << curbinopdf << endl
						<< "j = " << j << endl;
					cin.get();
				}
				if (curbinopdf <= pow(10.0, -13.0)) curbinopdf = 0;
				GoodTuring_constraints[i] += Hvars[j] * curbinopdf;
			}
			//if (freqcountmap[i + 1] == 0) continue; //Is it the correct to ignore frequency_i when frequency_i=0?
			
			string cname1 = "goodturing-upperbound-i="+to_string(i);
			model.addConstr(GoodTuring_constraints[i] <= (i + 1)*(double)freqcountmap[i + 1] / (double)(N-i) + e2s[i], cname1);
			string cname2 = "goodturing-lowerbound-i="+to_string(i);
			model.addConstr(GoodTuring_constraints[i] >= (i + 1)*(double)freqcountmap[i + 1] / (double)(N-i) - e2s[i] - (i+1)/(double)(N-i), cname2);			
		}
		
		//Add constraints: \sum_{i<idx} Hvars[i] / xLP[i] + Cvar / xLP[idx] == G
		GRBLinExpr G_constraint = 0.0;
		double G_scale = xLP[idx]; // pow(10, -9);
		if (G * G_scale >= 1) G_scale = 1.0 / G;
		for (int i = 0; i < idx; i++) {
			double coef_tmp = G_scale / xLP[i];
			//G_constraint += Hvars[i] / xLP[i] * G_scale;
			G_constraint += Hvars[i] * coef_tmp;
			//foutest << coef_tmp << endl;
		}
		double coef_tmp = G_scale / xLP[idx];
		//G_constraint += Cvar / xLP[idx] * G_scale;
		G_constraint += Cvar * coef_tmp;
		//foutest << coef_tmp << endl;
		//foutest.close();
		if (myobj == "max") model.addConstr(G_constraint <= G * G_scale, "G_constraint");
		else model.addConstr(G_constraint >= G * G_scale, "G_constraint");
		
		

		//double tolerance = pow(10.0, -4.0);
		//////model.addConstr(L1result_constraint == L1result, "L1result_constraint");
		//model.addConstr(L1result_constraint <= (1.0 + tolerance) * L1result, "L1result_constraint1");
		//model.addConstr(L1result_constraint >= (1.0 - tolerance) * L1result, "L1result_constraint2");

		//model.write("mymodel.mps");
		
		// Optimize model
		model.optimize();
		//double currentlimit = model.get(GRB_DoubleParam_TimeLimit);
		//cout << "GRB_DoubleParam_TimeLimit = " << currentlimit << endl;
		int status = model.get(GRB_IntAttr_Status);
		if (status == GRB_OPTIMAL) {
			cout << "The optimal objective is " << model.get(GRB_DoubleAttr_ObjVal) << endl;
			curBound = model.get(GRB_DoubleAttr_ObjVal); 
		}
		else if (status == GRB_SOLUTION_LIMIT) {
			cout << "The number of solutions found reached the value specified in the SolutionLimit parameter" << endl;
		}
		else if (status == GRB_TIME_LIMIT) {
			cout << "Optimization terminated because the time expended exceeded the value specified in the TimeLimit parameter." << endl;
		}
		else {
			cout << "Optimization was stopped with status " << status << endl;
			if (status == GRB_INFEASIBLE) {
				cout << "The model is infeasible" << endl;
			}
			else {
				cout << "The model is NOT infeasible but didn't output optimal result!" << endl;
				//exit(-1);
				//cin.get();
			}
		}
		return status;
	}
	catch (GRBException e) {
		cout << "Error code = " << e.getErrorCode() << endl;
		cout << e.getMessage() << endl;
		cin.get();
	}
	catch (...) {
		cout << "Exception during optimization" << endl;
		cin.get();
	}
	cout << "ERROR: gurobi try/catch error!!" << endl;
	cin.get();
	return -110;
}



void lambdaSG_to_lambdaG(string dname, string LPname, double delta1) {
	vector<string> sign = {"min", "max"};
	string inprefix = "./", outprefix = "./";
	/*
	if (LPname == "myLP1") {inprefix += "LP1plots/"; outprefix += "LP1plots/lambdaGLP1/";}
	else if (LPname == "myLP2") {inprefix += "LP2plots/"; outprefix += "LP2plots/lambdaGLP2/";}
	else {cout << "ERROR: LPname = " << LPname << endl; cin.get();}
	*/

	double N = N_map[dname];
	for (int i=0; i<sign.size(); i++) {
		ifstream fin(inprefix + LPname + "-" + dname+"_"+sign[i]+"_cutoff=" + to_string((long)N) + ".txt");
		ofstream fout(outprefix + "lambda_G-" + LPname + "-" + dname+"_"+sign[i]+"_cutoff=" + to_string((long)N) + ".txt");
		double e1 =  sqrt(log(delta1)/((-2)*N));
		string linestr = "";
		getline(fin, linestr);
		fout << linestr << "  lambda_G  " << LPname << "  " << sign[i] << endl;
		double G,lambdaSG,lambda_G;
		while (getline(fin, linestr)) {
			if (linestr[0] == '}') {
				fout << linestr << endl;
				break;
			}
			int i1=0, i2=0;
			while (linestr[i1] != '(') i1++;
			fout << linestr.substr(0,i1);
			i2 = i1;
			while (linestr[i2] != ',') i2++;
			G = stod(linestr.substr(i1+1, i2-i1-1));
			i1 = i2+1;
			while (linestr[i2] != ')') i2++;
			lambdaSG = stod(linestr.substr(i1,i2-i1));
			if (sign[i] == "min") lambda_G = lambdaSG + e1*100;
			else lambda_G = lambdaSG - e1*100;
			fout << "(" << G << ", " << lambda_G << ")" << endl;
		}
		fin.close();
		fout.close();
	}
}
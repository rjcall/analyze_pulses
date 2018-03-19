//  Robert Call



#include"File_Class.h"
#include<cassert>
#include<cctype>
using namespace std;


bool is_number(string s)
{
	return !s.empty() && std::find_if(s.begin(),
		s.end(), [](char c) { return !std::isdigit(c); }) == s.end()-1;
}


vector<string> get_files_windows() {
	char* psBuffer = new char[128];
	system("dir /b *dat > files.dat");
	ifstream ifs("files.dat");
	string j;
	vector<string> files;
	string command = "";
	while (!ifs.eof() && ifs.good()) {
		getline(ifs, j);
		if (j != "files.dat") {
			files.push_back(j);
		}

	}
	ifs.close();
	cout << command;
	system("del files.dat");
	return files;

}


vector<string> get_files_unix() {
	char* psBuffer = new char[128];
	system("ls *.dat >files.dat 2>/dev/null");
	ifstream ifs("files.dat");
	string j;
	vector<string> files;
	string command = "";
	while (!ifs.eof() && ifs.good()) {
		getline(ifs, j);
		if (j != "files.dat") {
			files.push_back(j);
		}

	}
	ifs.close();
	cout << command;
	system("rm files.dat");
	return files;

}




vector<string> get_ini_files(string f) {
	char* psBuffer = new char[300];
	ifstream ifs(f);
	string j;
	vector<string> files;
	string command = "";
	while (!ifs.eof() && ifs.good()) {
		getline(ifs, j);
		if(strcmp(j.c_str(), ""))
			files.push_back(j);
	}
	ifs.close();
	cout << command;
	return files;

}

int check_os() 
{
	int i;
	system("echo off");

	i = system("ls *.dat");
	if (i != 0) 
	{
		cout << "WINDOWS SYSTEM\n";
		system("echo off");
		i = system("dir /b *.dat >> stdout");
		i = 1;
	}
	else 
	{
		i = 0;
		cout << "UNIX SYTEM";
	}
	return i;
}





int main()
{
	int os = check_os();
	int vt;
	int width;
	int pulse_delta;
	float drop_ratio;
	int below_drop_ratio;
	//vector<string> dat_files = piper("dir /b *.dat");
	vector<string> dat_files;
	if (os == 1) {
		dat_files = get_files_windows();
	}

	else if (os == 0) {
		dat_files = get_files_unix();
	}

	cout << "Enter ini file name: \n";
	string ini_file;
	cin >> ini_file;
	cin.clear();
	cin.ignore();
	cout << "Using: " << ini_file << endl;
	vector<string> ini_vars = get_ini_files(ini_file);

	try {
		if (ini_vars.size() != 5)
			throw runtime_error("INVALID PARAMETERS FOR INI FILE");

	}
	catch (exception &e) {
		cout << e.what();
		cin.get();
		return -1;
	}

	for (int i = 0; i < 5; i++) {
		int eq = ini_vars[i].find("=");
		string e = ini_vars[i].substr(eq + 1);
		string eb = ini_vars[i].substr(0,eq );
		try {
			if (!is_number(e) && i!=3)
			{
				throw runtime_error("ERROR WITH Parameter: " + eb + "=" + e + "\n");
			}
		}
		catch (exception &e) {
			cout << e.what();
			cin.get();
			return -1;
		}

		switch (i)
		{
		case 0:
			vt = atoi(e.c_str());
		case 1:
			width = atoi(e.c_str());
		case 2:
			pulse_delta = atoi(e.c_str());
		case 3:
			drop_ratio = atof(e.c_str());
		case 4:
			below_drop_ratio = atoi(e.c_str());
		}

	}
	string s = " ";

	for (auto f : dat_files) {
		if (f.size() > 4) {
			f.erase(std::remove_if(f.begin(), f.end(), iswspace), f.end());
			dat_data* dd = new dat_data(f, vt, width, pulse_delta, drop_ratio, below_drop_ratio);
			dd->info();
			delete dd;
		}
	}
	cin.get();
	return 0;
}



/* Reflection */

/* 
I really enjoyed this project because it showed me that the pain you go through with
c++ compared to other languages is actually worth it. In order to get all the details figured out
I first wrote this program in python which I will include in my folder. I love python because there are
so many modules I can use to get something figured out. While doing this project I realized that reading the parameters from the
ini file was actually easyier in c++ than it was in python. I see that C++ really has the advantage of being lower level
data can be changed from streams to ints or floats. Its incredible that with this language we really can do whatever we want with raw data.
My biggest hang up with c++ before this assignment was that I didnt know that the algorithms modules can make my program much simpler, I dont need to look
at every bit of data inorder to do what I need. I feel like the use of the algorithm lib is an important part of being an effcient c++ programmer.
*/
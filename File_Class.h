#pragma once
#ifndef Dat

#include <stdio.h>  
#include <stdlib.h>  
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include<sstream>
#include<cstring>
#include<string>
#include<vector>
#include<iomanip>
#include<deque>
#include<cctype>


struct dat_data {
	std::string file_name;
	std::vector<int> data;
	std::deque<int>smooth_data;
	int vt;
	int width;
	int pd;
	float dr;
	int bdr;
	std::vector<int>widths;
	std::vector<int> pulses;

	dat_data(std::string f_name, int _vt, int _width, int _pd, float _dr, int _bdr) {
		file_name = f_name;
		vt = _vt;
		width = _width;
		pd = _pd;
		dr = _dr;
		bdr = _bdr;
		read_dat();
		get_smooth_data();
		get_pulse();
		get_delta();
		get_width();
	}

	int get_peak(int next, int pulse) {

		if (next - pulse < 2) {
			return pulse;
		}

		std::vector<int>::iterator result;
		result = max_element(data.begin() + pulse, data.begin() + next);
		return distance(data.begin(), result);
	}

	void read_dat() {
		std::ifstream dat_f(file_name);
		int x;
		while (!dat_f.eof() && dat_f.good()) {
			dat_f >> x;
			x *= -1;
			data.push_back(x);
		}
	}


	void get_smooth_data() {

		for (int i = 3; i < data.size() - 4; i++) {
			smooth_data.push_back(((data[i - 3] + 2 * data[i - 2] + 3 * data[i - 1] + 3 * data[i] + 3 * data[i + 1] + 2 * data[i + 2] + data[i + 3]) / 15));
		}
		for (int i = 0; i < 4; i++) {
			smooth_data.push_front(data[i]);
		}
		for (int i = -4; i < -1; i++) {
			smooth_data.push_back(data[data.size() + i]);
		}
	}

	void get_pulse() {
		int i = 0;
		while (i + 2 < smooth_data.size()) {
			int diff = smooth_data[i + 2] - smooth_data[i];
			if (diff > vt) {
				pulses.push_back(i - 1);
				while (i + 1 < smooth_data.size() && smooth_data[i + 1] > smooth_data[i]) {
					i += 1;
				}
				i += 1;
			}
			else
				i += 1;
		}
	}

	void get_width() {
		for (auto p : pulses) {
			int i = p;
			int count = 0;
			while (count < 100 and !exists(pulses, i + 1)) {
				i += 1;
				count += 1;

			}
			if (exists(pulses, i + 1))
				i += 1;
			int sum_of_elems = 0;
			for_each(data.begin() + p, data.begin() + i, [&](int n) {
				sum_of_elems += n;
			});
			widths.push_back(sum_of_elems);
		}
	}

	void get_delta() {
		std::vector<int> pulse_remove;
		std::vector<int> temp = pulses;
		for (int i = 0; i < temp.size() - 1; i++) {
			for (auto pulse : temp) {
				int span = pulse - temp[i];
				if (span <= pd) {
					int drop_height = get_peak(pulse, temp[i]);
					std::vector<int> delta_points;
					for (int i = drop_height; i < pulse - 1; i++) {
						int delta = data[drop_height] * dr;
						if (data[i] < delta) {
							delta_points.push_back(data[i]);
						}
						if (delta_points.size() > bdr) {
							break;
						}
					}
					if (delta_points.size() > bdr) {
						pulse_remove.push_back(temp[i]);
						break;
					}
				}
			}
		}
		std::vector<int> good_p;
		for (auto p : pulses) {
			if (!exists(pulse_remove, p)) {
				good_p.push_back(p);
			}
		}
		pulses = good_p;

	}
	bool exists(std::vector<int>&arr1, int num) {
		for (auto n : arr1) {
			if (num == n)
				return true;
		}
		return false;
	}
	void info()
	{
		std::cout << "\nFile Name: " << file_name << std::endl;
		//cout << "Data Size: " << data.size() << endl;
		//cout << "smooth size: " << smooth_data.size() << endl;
		//cout << "PULSES\n";
		for (int i = 0; i < pulses.size(); i++) {
			std::cout << "Pulse: " << pulses[i] << " Width: " << widths[i] << std::endl;
		}
		std::cout << std::endl;
	}

};
#endif // !Dat
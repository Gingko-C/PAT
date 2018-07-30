#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <vector>
using std::vector;
#include <string>
using std::string;
#include <queue>
using std::priority_queue;
#include <algorithm>
using std::sort;
using std::min;
#include <map>
using std::map;

#define INT_MAX 100000000

int time_cost[25];

struct record {
	int month, day, hh, mm;
	bool on_off;
	bool tf = 1;
};

map<string, vector<int>> costs;
void count_cost(string id, record b, record e) {
	int res = 0;
	int altime = 0;
	if (b.day != e.day) {
		res += (60 - b.mm)*time_cost[b.hh];
		altime += 60 - b.mm;
		res += (e.mm)*time_cost[e.hh];
		altime += e.mm;
		while (++b.hh != 24) {
			res += time_cost[b.hh] * 60;
			altime += 60;
		}
		while (--e.hh >= 0) {
			res += time_cost[e.hh] * 60;
			altime += 60;
		}
		res += (e.day - b.day - 1)*time_cost[24] * 60;
		altime += 60 * 24;
	}
	else if (b.hh != e.hh) {
		res += (60 - b.mm)*time_cost[b.hh];
		altime += 60 - b.mm;
		res += (e.mm)*time_cost[e.hh];
		altime += e.mm;
		while (++b.hh != e.hh) {
			res += time_cost[b.hh] * 60;
			altime += 60;
		}
	}
	else {
		res += (e.mm - b.mm)*time_cost[b.hh];
		altime += e.mm - b.mm;
	}
	costs[id].push_back(altime);
	costs[id].push_back(res);

}


bool rec_order(const record &lhs, const record &rhs) {
	if (lhs.month < rhs.month) return 1;
	if (lhs.month > rhs.month) return 0;
	if (lhs.day < rhs.day) return 1;
	if (lhs.day > rhs.day) return 0;
	if (lhs.hh < rhs.hh) return 1;
	if (lhs.hh > rhs.hh) return 0;
	if (lhs.mm < rhs.mm) return 1;
	return 0;
}

int main() {
	for (int i = 0; i < 24; i++) {
		cin >> time_cost[i];
		time_cost[24] += time_cost[i];
	}
	int records_num;
	cin >> records_num;
	map<string, vector<record>> record_groups;
	string record_id, record_time, record_on;
	int month, day, hh, mm;
	bool on_off;
	string record_str;
	vector<std::pair<string, record>> first_calls;
	for (int i = 0; i < records_num; i++) {
		cin >> record_id >> record_time >> record_on;
		//record_groups[record_id].push_back({record_time})
		on_off = (record_on == "on-line") ? 1 : 0;
		month = stoi(string(record_time.begin(), record_time.begin() + 2));
		day = stoi(string(record_time.begin() + 3, record_time.begin() + 5));
		hh = stoi(string(record_time.begin() + 6, record_time.begin() + 8));
		mm = stoi(string(record_time.begin() + 9, record_time.end()));
		record_groups[record_id].push_back({ month,day,hh,mm,on_off });
	}
	for (auto &i : record_groups) {
		sort(i.second.begin(), i.second.end(), rec_order);
		int bb = 0, ee = 1;
		bool flag_call = 0;
		while (ee < i.second.size()) {
			if (i.second[bb].on_off == 1) {
				if (i.second[ee].on_off == 0) {
					if (flag_call == 0) {
						flag_call = 1;
						first_calls.push_back({ i.first, i.second[bb] });
					}
					count_cost(i.first, i.second[bb], i.second[ee]);
					bb += 2;
					ee += 2;
				}
				else {
					i.second[bb].tf = 0;
					bb++;
					ee++;
				}
			}
			else {
				i.second[bb].tf = 0;
				bb++;
				ee++;
			}
		}
		if (bb == i.second.size() - 1) i.second.back().tf = 0;
	}
	sort(first_calls.begin(), first_calls.end(), [](const std::pair<string, record> &lhs, const std::pair<string, record> &rhs) { return rec_order(lhs.second,rhs.second);});
	for (auto i : first_calls) {
		int costs_flag = 0;
		cout << i.first;
		printf(" %02d\n", i.second.month);
		int total_cost = 0;
		for (int j = 0; j < record_groups[i.first].size(); j++) {
			if (record_groups[i.first][j].tf == 1) {
				printf("%02d:%02d:%02d ", record_groups[i.first][j].day, record_groups[i.first][j].hh, record_groups[i.first][j].mm);
				if (record_groups[i.first][j].on_off == 0) {
					printf("%d $%.02f\n", costs[i.first][costs_flag++], float(costs[i.first][costs_flag]) / 100.0);
				}
			}
				
		}
	}
	system("pause");
	return 0;
}
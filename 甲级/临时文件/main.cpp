#include <vector>
using std::vector;
#include <string>
using std::string;
#include <map>
using std::map;
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <queue>
using std::queue;
using std::priority_queue;

#define INT_MAX 100000

struct record {
	string carid;
	int time;
	int val;
};

int stotime(string &st) {
	int h = stoi(string(st.begin(), st.begin() + 2));
	int m = stoi(string(st.begin() + 3, st.begin() + 5));
	int s = stoi(string(st.begin() + 6, st.end()));
	return h * 3600 + m * 60 + s;
}

bool compareRecord(record &lhs, record &rhs) {
	return lhs.time < rhs.time;
}

int main() {
	int n, k;
	cin >> n >> k;
	string carid, time_str, stat;
	vector<int> checkTime;
	priority_queue < record, vector<record>,decltype(compareRecord)* > pqr(compareRecord);
	map<string, int> ct;
	vector<int> checkRes;
	for (int i = 0;i < n;i++) {
		cin >> carid >> time_str >> stat;
		if (stat == "in") pqr.push({ carid, stotime(time_str), 1 });
		if (stat == "out") pqr.push({ carid, stotime(time_str), -1 });
	}
	for (int i = 0;i < k;i++) {
		cin >> time_str;
		checkTime.push_back(stotime(time_str));
	}
	int st = 0;
	int carnum = 0;
	record r1 = pqr.top();
	pqr.pop();
	while (checkTime[st] < r1.time) {
		checkRes[st] = 0;
		st++;
	}
	while (!pqr.empty()) {
		record r2 = pqr.top();
		pqr.pop();
		carnum += r1.val;
		while (checkTime[st] > r1.time &&checkTime[st] < r2.time) {
			checkRes[st] = carnum;
			st++;
		}


	}
	system("pause");
	return 0;
}

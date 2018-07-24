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
	bool tf = true;
	friend bool operator<(const record &l, const record &r) {
		return l.time < r.time;
	}
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

struct record_stat
{
	int record_no;
	int record_val;
};

int main() {
	int n, k;
	cin >> n >> k;
	string carid, time_str, stat;
	vector<int> checkTime;
	vector<record> vr;
	map<string, vector<record_stat>> rs;
	map<string, vector<int>> ct;
	vector<int> checkRes(k);
	for (int i = 0; i < n; i++) {
		cin >> carid >> time_str >> stat;
		if (stat == "in") vr.push_back({ carid, stotime(time_str), 1 });
		if (stat == "out") vr.push_back({ carid, stotime(time_str), -1 });
	}
	std::sort(vr.begin(), vr.end());
	for (int i = 0; i < n; i++) {
		rs[vr[i].carid].push_back({ i, vr[i].val });
		if (rs[vr[i].carid].size() % 2 == 1 && (rs[vr[i].carid].end()-1)->record_val == -1) {
			vr[i].tf = false;
			rs[vr[i].carid].erase(rs[vr[i].carid].end() - 1);
		}
		else if (rs[vr[i].carid].size() >= 2) {
			if (rs[vr[i].carid].size() % 2 == 0 && (rs[vr[i].carid].end() - 1)->record_val == (rs[vr[i].carid].end() - 2)->record_val) {
				vr[(rs[vr[i].carid].end() - 2)->record_no].tf = false;
				rs[vr[i].carid].erase(rs[vr[i].carid].end()-2);

				//if ((rs[vr[i].carid].end() - 1)->record_val == -1) {
				//	vr.erase(vr.begin() + (rs[vr[i].carid].end() - 1)->record_no);
				//	rs[vr[i].carid].erase(rs[vr[i].carid].end() - 1);
				//}
			}
		}

	}
	for (int i = 0; i < k; i++) {
		cin >> time_str;
		checkTime.push_back(stotime(time_str));
	}
	int st = 0;
	int vr_no = 0;
	int carnum = 0;
	while (vr[vr_no].tf == false) vr_no++;
	record r1 = vr[vr_no];
	vr_no++;
	while (vr[vr_no].tf == false) vr_no++;
	ct[r1.carid].push_back(r1.time);
	while (checkTime[st] < r1.time) {
		checkRes[st] = 0;
		st++;
	}
	while (vr_no != vr.size()) {
		record r2 = vr[vr_no];
		vr_no++;
		while (vr[vr_no].tf == false) {
			vr_no++;
			if (vr_no == vr.size()) break;
		} 
		if (vr_no == vr.size()) break;
		ct[r2.carid].push_back(r2.time);
		carnum += r1.val;
		while (checkTime[st] >= r1.time &&checkTime[st] <= r2.time) {
			checkRes[st] = carnum;
			st++;
		}
		r1 = r2;
	}
	for (auto i : checkRes) {
		cout << i << endl;
	}
	system("pause");
	return 0;
}

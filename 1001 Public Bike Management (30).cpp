#include <string>
using std::string;
#include <vector>
using std::vector;
#include <map>
using std::map;
#include <set>
using std::set;
#include <list>
using std::list;
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <memory>
using std::shared_ptr;
using std::unique_ptr;
using std::make_shared;
using std::allocator;
#include <new>
#include <algorithm>
#include <utility>
#include <sstream>

int main() {
	string line;
	int cmax, stanum, index, roadnum;
	map<std::pair<int, int>, int> timecost;
	cin >> cmax >> stanum >> index >> roadnum;
	vector<set<int>> fastroad(stanum + 1, { 0 });
	vector<std::pair<int, int>> ctrans(stanum + 1, { 0,0 });
	vector<int> csta(1,-1);
	for (int i = 0;i < stanum;i++) {
		int temp;
		cin >> temp;
		csta.push_back(temp);
	}
	for (int i = 0;i < roadnum;i++) {
		std::pair<int, int> temp_pair;
		int time;
		cin >> temp_pair.first >> temp_pair.second >> time;
		timecost[temp_pair] = time;
		if (temp_pair.first == 0) {
			fastroad[temp_pair.second] = { 0, temp_pair.second };
			int temp_ctrans = csta[temp_pair.second] - cmax/2;
			if (temp_ctrans > 0)
				ctrans[temp_pair.second].second = temp_ctrans;
			else ctrans[temp_pair.second].first = -temp_ctrans;
		}
	}
	for (int i = 1;i <= index;i++) {
		for (int j = 0;j < i;j++) {
			if (timecost[{0, j}] != 0 && timecost[{j, i}] != 0) {
				int temp = timecost[{0, j}] + timecost[{j, i}];
				int temp_ctrans = csta[i] - cmax / 2 + ctrans[j].second - ctrans[j].first;
				if (timecost[{0, i}] == 0) {
					timecost[{0, i}] = temp;
					if (temp_ctrans > 0) ctrans[i].second = temp_ctrans;
					else ctrans[i].first = -temp_ctrans;
					fastroad[i] = fastroad[j];
					fastroad[i].insert(i);
				}
				else {
					if (temp == timecost[{0, i}]) {
						if (abs(temp_ctrans) < abs(ctrans[i].second - ctrans[i].first)) {
							if (temp_ctrans > 0)
								ctrans[i] = { 0,temp_ctrans };
							else ctrans[i] = { -temp_ctrans,0 };
							timecost[{0, i}] = temp;
							fastroad[i] = fastroad[j];
							fastroad[i].insert(i);
						}
					}
					else {
						if (temp < timecost[{0, i}]) {
							timecost[{0, i}] = temp;
							if (temp_ctrans > 0)
								ctrans[i] = { 0,temp_ctrans };
							else ctrans[i] = { -temp_ctrans,0 };
							fastroad[i] = fastroad[j];
							fastroad[i].insert(i);
						}
					}
				}
			}
		}
	}
	cout << ctrans[index].first << " ";
	int flag = 0;
	for (auto i : fastroad[index]) {
		if (flag != 0) cout << "->";
		if (flag == 0) flag = 1;
		cout << i;
	}
	cout << " " << ctrans[index].second << endl;
	system("pause");
	return 0;
}
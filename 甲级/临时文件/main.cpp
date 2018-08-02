#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
using namespace std;
struct player
{
	int arr_time;
	int play_time;
	bool vip;
	int ser_time;
	int wait_time;
};
struct table
{
	int id;
	int free_time;
	int play_num = 0;
};
int main() {
	int player_num, time_temp, table_num, vip_table_num, order_no = 0;
	string time_str;
	cin >> player_num;
	vector<player> players(player_num);
	for (int i = 0; i < player_num; i++) {
		cin >> time_str;
		time_temp = stoi(string(time_str.begin(), time_str.begin() + 2)) * 3600 + stoi(string(time_str.begin() + 3, time_str.begin() + 5)) * 60 + stoi(string(time_str.begin() + 6, time_str.end()));
		players[i].arr_time = time_temp;
		cin >> players[i].play_time >> players[i].vip;
	}
	cin >> table_num >> vip_table_num;
	vector<int> vip_tables(vip_table_num);
	priority_queue<table> tables;
	for (int i = 0; i < vip_table_num; i++) {
		cin >> vip_tables[i];
	}
	for (int i = 1; i <= table_num; i++) {
		tables.push({ i,8 * 3600 });
	}
	sort(players.begin(), players.end(), [](const player &l, const player &r) {return l.arr_time < r.arr_time; });
	for (int i = 0; i < player_num; i++) {
		
	}
	system("pause");
	return 0;
}
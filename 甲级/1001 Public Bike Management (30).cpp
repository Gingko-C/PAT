//Dijkstra 改进加入 路径记录和等权重路径记录
#include <vector>
using std::vector;
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <algorithm>
 
#define INT_MAX 100000
int main() {
    int cmax, vnum, pnum, wnum;
    cin >> cmax >> vnum >> pnum >> wnum;
    int bv, ev;
    int baseP = 0;
    vector<int> cnum(++vnum); //实际结点数要加上0结点
    vector<vector<int>> wmat(vnum, vector<int>(vnum, INT_MAX));
    vector<int> dis(vnum, INT_MAX);
    vector<bool> flag(vnum, false);
    vector<vector<vector<int>>> sw(vnum);
    vector<vector<int>> w2p;
    for (int i = 1;i < vnum;i++) {
        cin >> cnum[i];
    }
    for (int i = 0;i < wnum;i++) {
        cin >> bv >> ev;
        cin >> wmat[bv][ev];
        wmat[ev][bv] = wmat[bv][ev];
        if (bv == 0) {
            dis[ev] = wmat[bv][ev];
            sw[ev] = { {0,ev} };
        }
        if (ev == 0) {
            dis[bv] = wmat[ev][bv];
            sw[bv] = { { 0,bv } };
        }
 
    }
    dis[0] = 0;
    flag[0] = true;
    for (int i = 0;i < vnum - 1;i++) {
        int min = INT_MAX;
        for (int j = 1;j < vnum;j++) {
            if (flag[j] != true && dis[j] < min) {
                min = dis[j];
                baseP = j;
            }
        }
        flag[baseP] = true;
        for (int j = 1;j < vnum;j++) {
            int temp_dis = (wmat[baseP][j] == INT_MAX) ? INT_MAX : dis[baseP] + wmat[baseP][j];
            if (temp_dis < dis[j]) {
                dis[j] = temp_dis;
                sw[j] = sw[baseP];
                for (auto &w : sw[j]) {
                    w.push_back(j);
                }
            }
            else if (temp_dis == dis[j]) {
                for (auto w : sw[baseP]) {
                    vector<int> temp_v(w);
                    temp_v.push_back(j);
                    sw[j].push_back(temp_v);
                }
            }
        }
    }
    for (int i = 0;i < sw[pnum].size();i++) {
        int sent = 0, carry = 0;
        for (int j = 1;j < sw[pnum][i].size();j++) {
            carry += cnum[sw[pnum][i][j]] - cmax / 2;
            if (carry < 0) {
                sent += -carry;
                carry = 0;
            }
        }
        w2p.push_back({ sent,carry,i });
    }
 
    std::sort(w2p.begin(), w2p.end());
 
    cout << w2p[0][0]<<" ";
    int flag_cout = false;
    for (auto i : sw[pnum][w2p[0][2]]) {
        if (flag_cout == false) {
            cout << i;
            flag_cout = true;
        }
        else cout << "->" << i;
    }
    cout << " " << w2p[0][1] << endl;
    system("pause");
    return 0;
}
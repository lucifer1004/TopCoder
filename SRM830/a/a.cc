#include <bits/stdc++.h>
#define INF 0x3f3f3f3f

using namespace std;
using ll = long long;

const int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
int dis[500][500][2];

class Jetpack {
 public:
  int travel(vector<string> maze, int T) {
    memset(dis, 0x3f, sizeof(dis));
    int n = maze.size(), m = maze[0].size();
    int ai = -1, aj = -1, bi = -1, bj = -1, pits = 0;

    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j) {
        if (maze[i][j] == 'A') {
          ai = i;
          aj = j;
        } else if (maze[i][j] == 'B') {
          bi = i;
          bj = j;
        } else if (maze[i][j] == '_') {
          pits++;
        }
      }

    priority_queue<array<int, 4>, vector<array<int, 4>>, greater<array<int, 4>>>
        q;
    dis[ai][aj][0] = 0;
    q.push({0, ai, aj, 0});
    while (!q.empty()) {
      auto f = q.top();
      q.pop();
      int d = f[0], i = f[1], j = f[2], pass = f[3];
      if (i == bi && j == bj) return d;
      if (d > dis[i][j][pass]) continue;

      for (int k = 0; k < 4; ++k) {
        int ni = i + dir[k][0], nj = j + dir[k][1];
        if (ni < 0 || ni >= n || nj < 0 || nj >= m || maze[ni][nj] == '#')
          continue;
        if (maze[ni][nj] == '_') {
          if (pass == 1 && dis[ni][nj][1] > d + T + 1) {
            dis[ni][nj][1] = d + T + 1;
            q.push({d + T + 1, ni, nj, 1});
          }
        } else {
          int npass = maze[ni][nj] == 'C' ? 1 : pass;
          if (dis[ni][nj][npass] > d + 1) {
            dis[ni][nj][npass] = d + 1;
            q.push({d + 1, ni, nj, npass});
          }
        }
      }
    }

    int ans = min(dis[bi][bj][0], dis[bi][bj][1]);
    return ans == INF ? -1 : ans;
  }
};

int main() {
  Jetpack jp;
  cout << jp.travel({"A###B", "....."}, 47) << endl;
  cout << jp.travel({"A#.#B", "..#.."}, 47) << endl;
  cout << jp.travel({"A#.#B", ".._C."}, 1) << endl;
  cout << jp.travel({"B_C_C_CA"}, 10) << endl;
  cout << jp.travel({"___B__.", "C#####.", "AC....."}, 1) << endl;
  cout << jp.travel({"___B__.", "C#####.", "AC....."}, 10) << endl;
  cout << jp.travel({"AC", ".#", "_B"}, 10) << endl;
  cout << jp.travel({"C.A", "___", "__B"}, 10) << endl;
}

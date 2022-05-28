#include <bits/stdc++.h>
#define INF 0x3f3f3f3f

using namespace std;

template <typename T>
void read(T &x) {
  x = 0;
  char c = getchar();
  T sig = 1;
  for (; !isdigit(c); c = getchar())
    if (c == '-') sig = -1;
  for (; isdigit(c); c = getchar()) x = (x << 3) + (x << 1) + c - '0';
  x *= sig;
}

int lim[5] = {2, 1, 3, 7, 13};

class MorseCodeCorrector {
 public:
  string fix(string message) {
    int n = message.size();
    vector<vector<vector<int>>> dp(
        n + 1, vector<vector<int>>(5, vector<int>(16, INF)));
    vector<vector<vector<array<int, 3>>>> pre(
        n + 1, vector<vector<array<int, 3>>>(5, vector<array<int, 3>>(16)));
    dp[0][0][0] = 0;
    for (int i = 0; i < n; ++i) {
      char ch = message[i];
      for (int j = 0; j <= 4; ++j)
        for (int state = 0; state <= lim[j]; ++state) {
          if (j == 4 && (state == 3 || state == 5)) continue;

          int cost = dp[i][j][state];
          if (cost == INF) continue;

          if (j == 0) {
            // '||'
            if (state == 1) {
              int c = cost + (ch != '|');
              if (c < dp[i + 1][j][2]) {
                dp[i + 1][0][2] = c;
                pre[i + 1][0][2] = {i, j, state};
              }
            }

            // '-' or '.'
            int c = cost + (ch != '.');
            if (c < dp[i + 1][1][0]) {
              dp[i + 1][1][0] = c;
              pre[i + 1][1][0] = {i, j, state};
            }

            c = cost + (ch != '-');
            if (c < dp[i + 1][1][1]) {
              dp[i + 1][1][1] = c;
              pre[i + 1][1][1] = {i, j, state};
            }
          } else {
            // '|'
            int c = cost + (ch != '|');
            if (c < dp[i + 1][0][1]) {
              dp[i + 1][0][1] = c;
              pre[i + 1][0][1] = {i, j, state};
            }

            if (j + 1 <= 4) {
              int c = cost + (ch != '.');
              if (c < dp[i + 1][j + 1][state << 1]) {
                dp[i + 1][j + 1][state << 1] = c;
                pre[i + 1][j + 1][state << 1] = {i, j, state};
              }

              c = cost + (ch != '-');
              if (c < dp[i + 1][j + 1][state << 1 | 1]) {
                dp[i + 1][j + 1][state << 1 | 1] = c;
                pre[i + 1][j + 1][state << 1 | 1] = {i, j, state};
              }
            }
          }
        }
    }

    int best = INF, p = -1, q = -1;
    for (int i = 1; i <= 4; ++i)
      for (int j = 0; j <= lim[i]; ++j) {
        if (i == 4 && (j == 3 || j == 5)) continue;
        if (dp[n][i][j] < best) {
          best = dp[n][i][j];
          p = i, q = j;
        }
      }

    string ans(message);
    for (int i = n - 1; i >= 0; --i) {
      if (p > 0) {
        int last = q & 1;
        if (last == 1)
          ans[i] = '-';
        else
          ans[i] = '.';
      } else {
        ans[i] = '|';
      }

      int p1 = pre[i + 1][p][q][1], q1 = pre[i + 1][p][q][2];
      p = p1, q = q1;
    }

    return ans;
  }
};

int main() {
  MorseCodeCorrector mcc;
  cout << mcc.fix("-...") << endl;
  cout << mcc.fix("---.") << endl;
  cout << mcc.fix("-.-.-") << endl;
  cout << mcc.fix(".||-") << endl;
  cout << mcc.fix("-|---|.--.||-.-.|---|-..|.|.-.") << endl;
  cout << mcc.fix("....||||||-----|||||.") << endl;
}
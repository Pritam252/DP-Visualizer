#include <bits/stdc++.h>
#include "Visualizer.cpp"

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int maxn = 1005, modnum = 1e9 + 7;
int n, m;
pii treasure;

int main(){
    cin.tie(nullptr)->sync_with_stdio(0);
    cin >> n >> m;
    vector<vector<int>> dp(n+1, vector<int>(m+1));
    init(dp, {1, dp.size()}, {1, dp[0].size()});
    treasure = {3, 3};
    dp[0][1] = 1;
    Describe("dp[0] = 1");
    Visualize(dp, {}, {});
    for (int i = 1; i <= treasure.first; i++){
        for (int j = 1; j <= treasure.second; j++){
            dp[i][j] = (dp[i - 1][j] + dp[i][j - 1]) % modnum;
            Describe("dp[i]");
            Visualize(dp, {}, {});
        }
    }
    for (int i = treasure.first; i <= n; i++){
        for (int j = treasure.second; j <= m; j++){
            dp[i][j] = (dp[i - 1][j] + dp[i][j - 1]) % modnum;
            Describe("dp[i]");
            Visualize(dp, {}, {});
        }
    }
    cout << dp[n][m];
    while(!WindowShouldClose()) Visualize(dp, {}, {});
    stop();
}
#include <bits/stdc++.h>
#include "Visualizer.cpp"
using namespace std;

const int maxn = 1005, modnum = 1e9 + 7;
int n, m;

int main(){
    cin.tie(nullptr)->sync_with_stdio(0);
    cin >> n >> m;
    vector<vector<int>> dp(n+1, vector<int>(m+1));
    init(dp, {1, n+1}, {1, m+1});
    dp[0][1] = 1;
    Describe("dp[0] = 1");
    Visualize(dp, {}, {});
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            dp[i][j] = (dp[i - 1][j] + dp[i][j - 1]) % modnum;
            Describe("dp[i]");
            Visualize(dp, {{i - 1, j}, {i, j - 1}}, {{i, j}});
        }
    }
    cout << dp[n][m];
    while(!WindowShouldClose()) Visualize(dp, {}, {});
    stop();
}
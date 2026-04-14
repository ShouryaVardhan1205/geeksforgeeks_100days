#include <limits.h>
#include <string.h>

#define MAXN 15

class Solution {
public:
    int n;
    int dp[1 << MAXN][MAXN];

    int solve(int mask, int pos, vector<vector<int>>& cost) {
        if (mask == (1 << n) - 1)
            return cost[pos][0];

        if (dp[mask][pos] != -1)
            return dp[mask][pos];

        int ans = INT_MAX;

        for (int city = 0; city < n; city++) {
            if ((mask & (1 << city)) == 0) {
                int newAns = cost[pos][city] +
                             solve(mask | (1 << city), city, cost);

                if (newAns < ans)
                    ans = newAns;
            }
        }

        return dp[mask][pos] = ans;
    }

    int tsp(vector<vector<int>>& cost) {
        n = cost.size();
        memset(dp, -1, sizeof(dp));

        return solve(1, 0, cost);
    }
};
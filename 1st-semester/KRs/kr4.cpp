#include <iostream>
#include <vector>
#include <limits>

int minCoins(std::vector<int> coins, int V) {
    int m = coins.size();
    std::vector<int> dp(V + 1, std::numeric_limits<int>::max());
    dp[0] = 0;

    for (int i = 1; i <= V; i++) {
        for (int j = 0; j < m; j++) {
            if (coins[j] <= i) {
                int sub_res = dp[i - coins[j]];
                if (sub_res != std::numeric_limits<int>::max() && sub_res + 1 < dp[i]) {
                    dp[i] = sub_res + 1;
                }
            }
        }
    }
    
    return dp[V] == std::numeric_limits<int>::max() ? -1 : dp[V];
}

int main() {
    std::cout << "Value insert" << std::endl;
    int v;
    std::cin >> v;
    std::vector<int> coins = {1, 2, 5, 10};
    int result = minCoins(coins, v);
    
    result == -1 ? std::cout << "Impossible combination" : std::cout << "Min: " << result;
    return 0;
}

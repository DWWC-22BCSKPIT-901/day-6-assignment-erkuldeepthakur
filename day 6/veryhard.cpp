#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional>

using namespace std;

class Solution {
public:
    int countValidRoots(int n, vector<vector<int>>& edges, vector<vector<int>>& guesses, int k) {
        // Step 1: Build the adjacency list (tree structure)
        vector<vector<int>> tree(n);
        for (const auto& edge : edges) {
            tree[edge[0]].push_back(edge[1]);
            tree[edge[1]].push_back(edge[0]);
        }
        
        // Step 2: Prepare for guess processing
        unordered_map<int, vector<int>> guess_from_parent, guess_to_child;
        
        // Store guesses where parent-child relationship is guessed
        for (const auto& guess : guesses) {
            guess_from_parent[guess[0]].push_back(guess[1]);
            guess_to_child[guess[1]].push_back(guess[0]);
        }

        int valid_root_count = 0;

        // Step 3: Check each node as the root and calculate valid guesses
        function<int(int, int)> dfs = [&](int node, int parent) -> int {
            int valid_guesses = 0;

            // Check guesses for the current node as the parent
            for (int child : guess_from_parent[node]) {
                if (child != parent) {
                    valid_guesses++;
                }
            }

            // Traverse the tree and calculate guesses recursively
            for (int child : tree[node]) {
                if (child != parent) {
                    valid_guesses += dfs(child, node);
                }
            }

            return valid_guesses;
        };

        // Try every node as the root
        for (int i = 0; i < n; ++i) {
            int valid_guesses = dfs(i, -1);  // DFS from node i with no parent (-1)
            if (valid_guesses >= k) {
                valid_root_count++;
            }
        }

        return valid_root_count;
    }
};

int main() {
    Solution sol;

    // Test case 1
    vector<vector<int>> edges1 = {{0, 1}, {1, 2}, {1, 3}, {4, 2}};
    vector<vector<int>> guesses1 = {{1, 3}, {0, 1}, {1, 0}, {2, 4}};
    int k1 = 3;
    cout << sol.countValidRoots(5, edges1, guesses1, k1) << endl; // Output: 3

    return 0;
}

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string findOrder(vector<string>& words) {
        // ── Step 1: Collect all unique characters ────────────────────────
        set<char> charSet;
        for (auto& w : words)
            for (char c : w)
                charSet.insert(c);

        // ── Step 2: Build adjacency list & in-degree map ─────────────────
        // graph[u] = list of chars that come AFTER u
        map<char, vector<char>> graph;
        map<char, int> indegree;

        // Initialise every character with 0 indegree
        for (char c : charSet) {
            indegree[c] = 0;
            graph[c];        // ensure key exists even if no outgoing edges
        }

        // Compare adjacent word pairs to extract ordering rules
        for (int i = 0; i < (int)words.size() - 1; i++) {
            string& w1 = words[i];
            string& w2 = words[i + 1];
            int minLen = min(w1.size(), w2.size());
            bool found = false;

            for (int j = 0; j < minLen; j++) {
                if (w1[j] != w2[j]) {
                    // w1[j] comes BEFORE w2[j] in alien order
                    graph[w1[j]].push_back(w2[j]);
                    indegree[w2[j]]++;
                    found = true;
                    break;   // only first differing char gives info
                }
            }

            // ── Invalid case ─────────────────────────────────────────────
            // "abcd" before "ab" is impossible (prefix rule)
            if (!found && w1.size() > w2.size())
                return "";
        }

        // ── Step 3: Topological Sort (Kahn's BFS Algorithm) ──────────────
        queue<char> q;

        // Push all chars with indegree 0 (no prerequisite)
        for (auto& [ch, deg] : indegree)
            if (deg == 0)
                q.push(ch);

        string result = "";

        while (!q.empty()) {
            char curr = q.front();
            q.pop();
            result += curr;   // add to order

            // Reduce indegree of all neighbours
            for (char next : graph[curr]) {
                indegree[next]--;
                if (indegree[next] == 0)
                    q.push(next);  // ready to process
            }
        }

        // ── Step 4: Cycle check ───────────────────────────────────────────
        // If result doesn't contain all chars → cycle exists → invalid
        if (result.size() != charSet.size())
            return "";

        return result;
    }
};
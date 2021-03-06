/*
    Suffix Automaton
    
    Compressed form of all substrings of a given string.

    Complexity:
        construction -> O(nk), k is alphabet size
*/

const int ALPHA = 27;
struct SuffixAutomaton{
    int len[2*MAX], link[2*MAX], next[2*MAX][ALPHA];
    int sz, last;

    SuffixAutomaton() : sz(1), last(0) {
        len[0] = 0;
        link[0] = -1;
        memset(next[0], -1, sizeof next[0]);
    }

    SuffixAutomaton(string& s) : sz(1), last(0) {
        len[0] = 0;
        link[0] = -1;
        memset(next[0], -1, sizeof next[0]);
        for(auto c: s) add(c);
    }

    int toi(char c) {
        if(c == '$') return 26;
        return c-'a';
    }

    void add(char c) {
        c = toi(c);
        int cur = sz++;
        len[cur] = len[last] + 1;
        memset(next[cur], -1, sizeof next[cur]);
        int p = last;
        while (p != -1 && next[p][c] == -1) {
            next[p][c] = cur; p = link[p];
        }
        if (p == -1) {
            link[cur] = 0;
        } else {
            int q = next[p][c];
            if (len[p] + 1 == len[q]) {
                link[cur] = q;
            } else {
                len[sz] = len[p] + 1;
                link[sz] = link[q];
                memcpy(next[sz], next[q], sizeof next[q]);
                while (p != -1 && next[p][c] == q) {
                    next[p][c] = sz; p = link[p];
                }
                link[q] = link[cur] = sz++;
            }
        }
        last = cur;
    }

    // Applications:
    void lcs (string s) { // O(size(s))
        int v = 0, l = 0, best = 0, bestpos = 0;
        FOR(i, s.size()) {
            int c = toi(s[i]);
            while (v && next[v][c] == -1) {
                v = link[v];
                l = len[v];
            }
            if (next[v][c] != -1) {
                v = next[v][c];
                l++;
            }
            if (l > best) {
                best = l;
                bestpos = i;
            }
        }
        return s.substr(bestpos - best + 1, best);
    }

    long long distinct_substrings() {
        long long ans = 0;
        for (int i = 1; i < sz; i++) ans += len[i] - len[link[i]];
        return ans;
    }
};
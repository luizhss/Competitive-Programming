/*
    Manacher algorithm (Longest Palindromic String)

    Find the longest palindromic substring given a string s.

    Complexity:
        manacher() -> O(n)
*/

int lps[2*N+5];

int manacher(string& s) {
    int n = s.size();

    string p (2*n+3, '#');
    p[0] = '^';
    for (int i = 0; i < n; i++) p[2*(i+1)] = s[i];
    p[2*n+2] = '$';

    int k = 0, r = 0, m = 0;
    int l = p.length();
    for (int i = 1; i < l; i++) {
        int o = 2*k - i;
        lps[i] = (r > i) ? min(r-i, lps[o]) : 0;
        while (p[i + 1 + lps[i]] == p[i - 1 - lps[i]]) lps[i]++;
        if (i + lps[i] > r) k = i, r = i + lps[i];
        m = max(m, lps[i]);
    }

    return m;
}
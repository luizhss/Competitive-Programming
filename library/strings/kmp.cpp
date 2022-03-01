/*
	KMP search (string matching)

	Complexity:
		prefix() -> O(n)
		kmp() -> O(n+m)
*/

std::vector<int> prefix(string s){
    int n = (int)s.length();
    std::vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j && s[i] != s[j]) j = pi[j-1];
        pi[i] = j + (s[i] == s[j]);
    }
    return pi;
}

std::vector<int> kmp(vi s, vi t){
    int n = t.size(), m = s.size();
	std::vector<int> lps = prefix(s),
					 matches;
	for (int i = 0, j = 0; i < n; i++) {
		while (j and s[j] != t[i]) j = lps[j-1];
		if (s[j] == t[i]) j++;
		if (j == m) matches.push_back(i-j+1), j = lps[j-1];
	}
	return matches;
}


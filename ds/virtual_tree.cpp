void solve() {
  ...
  vector<vector<pair<int64_t, int64_t>>> g(n + 1);
  vector<int> key(n + 1); // 关键点
  vector dp(n + 1, infll);
  ...
  int m;
  cin >> m;
  while (m--) {
    int k;
    cin >> k;
    vector<int> v(k);
    for (auto &i : v) {
      cin >> i;
    }
    for (auto i : v) {
      key[i] = true;
    }
    vector<int> x = v;
    {
      x.push_back(1);
      ranges::sort(x, [&](int a, int b) {
        return d.dft[a] < d.dft[b];
      });
      x.erase(ranges::unique(x).begin(), x.end());
      int fix_size = ssize(x);
      for (int i = 1; i < fix_size; ++i) {
        x.push_back(d.lca(x[i - 1], x[i]));
      }
      ranges::sort(x, [&](int a, int b) {
        return d.dft[a] < d.dft[b];
      });
      x.erase(ranges::unique(x).begin(), x.end());
    }
    for (int i = 1; i < ssize(x); ++i) {
      int lca = d.lca(x[i - 1], x[i]);
      int t = x[i];
      // path value: from t to lca
    }
    auto Dp = [&](this auto &self, int u, int f) -> void {
    };
    Dp(1, 1);
    cout << dp[1] << '\n';
    for (auto i : x) {
      key[i] = false;
      dp[i] = infll;
      g[i].clear();
    }
  }
}

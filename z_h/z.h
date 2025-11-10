#ifndef Z_H
#define Z_H
#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#include <other/debug.h>
#else
#define debug(...) 0
#endif
template <typename A, typename B>
std::istream &operator>>(std::istream &in, std::pair<A, B> &p) {
  in >> p.first >> p.second;
  return in;
}
template <typename A, typename B>
std::ostream &operator<<(std::ostream &out, const std::pair<A, B> &p) {
  out << p.first << ' ' << p.second;
  return out;
}
template <typename T>
concept ListOrVector = std::is_same_v<T, std::list<typename T::value_type>> or std::is_same_v<T, std::vector<typename T::value_type>>;
template <ListOrVector T>
std::istream &operator>>(std::istream &in, T &p) {
  for (auto &i : p) {
    in >> i;
  }
  return in;
}
template <ListOrVector T>
std::ostream &operator<<(std::ostream &os, const T &container) {
  for (auto it = begin(container); it != end(container); ++it) {
    if (it != begin(container)) {
      os << ' ';
    }
    os << *it;
  }
  return os;
}
template <typename A, typename B>
bool ckmn(A &x, const B &y) {
  return x > y && (x = y, true);
}
template <typename A, typename B>
bool ckmx(A &x, const B &y) {
  return x < y && (x = y, true);
}
template <typename T, typename U>
T sum(const std::vector<U> &A) {
  T sum = 0;
  for (auto &&a : A) sum += a;
  return sum;
}
template <typename T, typename U>
std::vector<T> presum(const std::vector<U> &A, int save0 = 0) {
  size_t N = A.size();
  std::vector<T> B(N + 1);
  for (size_t i = 0; i < N; ++i) {
    B[i + 1] = B[i] + A[i];
  }
  if (save0 == 0) {
    B.erase(B.begin());
  }
  return B;
}
template <typename T>
std::vector<int> index_sort(const std::vector<T> &A) {
  // stable index sort
  std::vector<int> ids(A.size());
  std::iota(ids.begin(), ids.end(), 0);
  sort(ids.begin(), ids.end(), [&](int i, int j) {
    if (A[i] == A[j]) {
      return i < j;
    } else {
      return A[i] < A[j];
    }
  });
  return ids;
}
template <typename F>
int64_t binary_search(F check, int64_t ok, int64_t ng, bool check_ok = true) {
  // F(ok) = 1, F(ng) = 0
  if (check_ok) {
    assert(check(ok));
    assert(!check(ng));
  }
  while (abs(ok - ng) > 1) {
    auto x = (ng + ok) / 2;
    std::tie(ok, ng) = (check(x) ? std::make_pair(x, ng) : std::make_pair(ok, x));
  }
  return ok;
}
template <typename F>
double binary_search(F check, double ok, double ng, int iter = 100) {
  while (iter--) {
    double x = (ok + ng) / 2;
    std::tie(ok, ng) = (check(x) ? std::make_pair(x, ng) : std::make_pair(ok, x));
  }
  return (ok + ng) / 2;
}
template <typename T, typename U>
T ceil(T x, U y) {
  return (x > 0 ? (x + y - 1) / y : x / y);
}
template <typename T, typename U>
T floor(T x, U y) {
  return (x > 0 ? x / y : (x - y + 1) / y);
}
template <typename t, typename u>
std::pair<t, t> div(t x, u y) {
  t q = floor(x, y);
  return {q, x - q * y};
}
int topbit(uint64_t x) {
  return (x == 0 ? -1 : 63 - std::countl_zero(x));
}
int lowbit(uint64_t x) {
  return (x == 0 ? -1 : std::countr_zero(x));
}
int popcount(int64_t x) {
  return popcount((uint64_t) x);
}
template <typename T>
using V = std::vector<T>;
template <typename T>
using VV = V<V<T>>;
template <typename T>
using VVV = V<VV<T>>;
template <typename T>
using VVVV = V<VVV<T>>;
template <typename T>
using dd = std::priority_queue<T, V<T>, std::less<T>>;
template <typename T>
using xd = std::priority_queue<T, V<T>, std::greater<T>>;
using sr = std::string;
using db = double;
using ld = long double;
using ll = long long;
using ull = unsigned long long;
using si = std::set<int>;
using sl = std::set<ll>;
using mii = std::map<int, int>;
using mll = std::map<ll, ll>;
using pii = std::pair<int, int>;
using pll = std::pair<ll, ll>;
using spii = std::set<pii>;
using spll = std::set<pll>;
using vpii = V<pii>;
using vpll = V<pll>;
using vvpii = VV<pii>;
using vvpll = VV<pll>;
using vi = V<int>;
using vvi = VV<int>;
using vvvi = VVV<int>;
using vl = V<ll>;
using vvl = VV<ll>;
using vvvl = VVV<ll>;
// clang-format off
#define OVERLOAD5(a, b, c, d, e, ...) e
#define FOR4(i, a, b, c) for (auto i = (a); i < (b); i += (c))
#define FOR1(a) FOR4(_, 0, a, 1)
#define FOR2(i, a) FOR4(i, 0, a, 1)
#define FOR3(i, a, b) FOR4(i, a, b, 1)
#define fk(...) OVERLOAD5(__VA_ARGS__, FOR4, FOR3, FOR2, FOR1)(__VA_ARGS__)  // fk
#define FB4(i, a, b, c) for (auto i = (a); i <= (b); i += (c))
#define FB1(a) FB4(_, 1, a, 1)
#define FB2(i, a) FB4(i, 1, a, 1)
#define FB3(i, a, b) FB4(i, a, b, 1)
#define fb(...) OVERLOAD5(__VA_ARGS__, FB4, FB3, FB2, FB1)(__VA_ARGS__)  // fb
#define FAN4(i, a, b, c) for (auto i = (a); i >= (b); i -= (c))
#define FAN1(a) FAN4(_, a, 0, 1)
#define FAN2(i, a) FAN4(i, a, 0, 1)
#define FAN3(i, a, b) FAN4(i, a, b, 1)
#define fn(...) OVERLOAD5(__VA_ARGS__, FAN4, FAN3, FAN2, FAN1)(__VA_ARGS__)  // fn
#define OVERLOAD8(_1, _2, _3, _4, _5, _6, _7, _8, ...) _8
#define EACHA2(a, b, v) a, b
#define EACHA3(a, ...) a, EACHA2(__VA_ARGS__)
#define EACHA4(a, ...) a, EACHA3(__VA_ARGS__)
#define EACHA5(a, ...) a, EACHA4(__VA_ARGS__)
#define EACHZ1(a, v) a
#define EACHZ2(a, b, v) [EACHA2(a, b, v)]
#define EACHZ3(a, ...) [ a, EACHA2(__VA_ARGS__) ]
#define EACHZ4(a, ...) [ a, EACHA3(__VA_ARGS__) ]
#define EACHZ5(a, ...) [ a, EACHA4(__VA_ARGS__) ]
#define EACHZ6(a, ...) [ a, EACHA5(__VA_ARGS__) ]
#define EACHB1(a, v) v
#define EACHB2(a, ...) EACHB1(__VA_ARGS__)
#define EACHB3(a, ...) EACHB2(__VA_ARGS__)
#define EACHB4(a, ...) EACHB3(__VA_ARGS__)
#define EACHB5(a, ...) EACHB4(__VA_ARGS__)
#define EACHB6(a, ...) EACHB5(__VA_ARGS__)
#define EACHA(...) OVERLOAD8(__VA_ARGS__, EACHZ6, EACHZ5, EACHZ4, EACHZ3, EACHZ2, EACHZ1)(__VA_ARGS__)
#define EACHB(...) OVERLOAD8(__VA_ARGS__, EACHB6, EACHB5, EACHB4, EACHB3, EACHB2, EACHB1)(__VA_ARGS__)
#define eh(...) for (auto &&EACHA(__VA_ARGS__) : EACHB(__VA_ARGS__))
#define OVERLOAD7(a, b, c, d, e, f, g, ...) g
#define PR1(a) ::std::cout << (a)
#define PR2(a, ...) PR1(a); PR1(' '); PR1(__VA_ARGS__)
#define PR3(a, ...) PR1(a); PR1(' '); PR2(__VA_ARGS__)
#define PR4(a, ...) PR1(a); PR1(' '); PR3(__VA_ARGS__)
#define PR5(a, ...) PR1(a); PR1(' '); PR4(__VA_ARGS__)
#define PR6(a, ...) PR1(a); PR1(' '); PR5(__VA_ARGS__)
#define print(...) OVERLOAD7(__VA_ARGS__, PR6, PR5, PR4, PR3, PR2, PR1)(__VA_ARGS__)  // print
#define println(...) print(__VA_ARGS__); PR1('\n')  // print '\n'
#define printe(...) print(__VA_ARGS__); PR1(::std::endl)  // print endl
#define sz(x) ((int) x.size())
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define so(x) std::sort(all(x))
#define rso(x) std::sort(rall(x))
#define rev(x) std::reverse(all(x))
#define uni(x) std::sort(all(x)), x.erase(std::unique(all(x)), x.end()), x.shrink_to_fit()
#define ip(...) [](auto &..._x_) { (std::cin >> ... >> _x_); }(__VA_ARGS__)
#define jp(...) __VA_ARGS__; ip(__VA_ARGS__)
#define mine(v) (*std::min_element(v.begin(), v.end()))
#define maxe(v) (*std::max_element(v.begin(), v.end()))
#define gv1(n0, val) std::vector(n0, val)
#define gv2(n0, ...) std::vector(n0, gv1(__VA_ARGS__))
#define gv3(n0, ...) std::vector(n0, gv2(__VA_ARGS__))
#define gv4(n0, ...) std::vector(n0, gv3(__VA_ARGS__))
#define gv5(n0, ...) std::vector(n0, gv4(__VA_ARGS__))
#define gv6(n0, ...) std::vector(n0, gv5(__VA_ARGS__))
#define GET_GENV(_1, _2, _3, _4, _5, _6, _7, NAME, ...) NAME
#define genv(...) GET_GENV(__VA_ARGS__, gv6, gv5, gv4, gv3, gv2, gv1)(__VA_ARGS__)  // gen vector
#define fors(t, s) for (auto t = (s); t >= 0; t = (t == 0 ? -1 : (t - 1) & (s)))  // for_subset
#define ft front()
#define bk back()
#define in insert
#define pb push_back
#define eb emplace_back
#define em emplace
#define pob pop_back
#define pof pop_front
#define fi first
#define se second
#define fif first.first
#define fis first.second
#define sef second.first
#define ses second.second
#define io_multicase std::ios::sync_with_stdio(false); std::cin.tie(nullptr); int tt = 1; std::cin >> tt; while (tt--)
#define io_singlecase std::ios::sync_with_stdio(false); std::cin.tie(nullptr); int tt = 1; while (tt--)
// clang-format on
using namespace std;
#endif // Z_H

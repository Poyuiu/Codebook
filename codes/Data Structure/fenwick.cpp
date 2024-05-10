namespace internal {
template <class T>
using to_unsigned_t = typename to_unsigned<T>::type;
}  // namespace internal

template <class T>
struct FenwickTree {
  using U = internal::to_unsigned_t<T>;

 public:
  FenwickTree() : _n(0) {}
  explicit FenwickTree(int n) : _n(n), data(n) {}

  void add(int p, T x) {
    assert(0 <= p && p < _n);
    p++;
    while (p <= _n) {
      data[p - 1] += U(x);
      p += p & -p;
    }
  }

  T sum(int l, int r) {
    assert(0 <= l && l <= r && r <= _n);
    return sum(r) - sum(l);
  }

 private:
  int _n;
  std::vector<U> data;

  U sum(int r) {
    U s = 0;
    while (r > 0) {
      s += data[r - 1];
      r -= r & -r;
    }
    return s;
  }
};
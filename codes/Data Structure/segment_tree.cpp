template <typename T>
class SegmentTree {
 private:
  std::vector<T> tree, lazy;
  std::vector<bool> updated;
  int n;

  void build(int node, int start, int end, const std::vector<T>& arr) {
    if (start == end) {
      tree[node] = arr[start];
    } else {
      int mid = (start + end) / 2;
      build(2 * node, start, mid, arr);
      build(2 * node + 1, mid + 1, end, arr);
      tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
  }

  void updateRange(int node, int start, int end, int l, int r, T val) {
    if (updated[node]) {
      tree[node] = lazy[node] * (end - start + 1);
      if (start != end) {
        lazy[node * 2] = lazy[node];
        lazy[node * 2 + 1] = lazy[node];
        updated[node * 2] = updated[node];
        updated[node * 2 + 1] = updated[node];
      }
      updated[node] = false;
    }
    if (start > end or start > r or end < l) return;
    if (start >= l and end <= r) {
      tree[node] = val * (end - start + 1);
      if (start != end) {
        lazy[node * 2] = val;
        lazy[node * 2 + 1] = val;
        updated[node * 2] = true;
        updated[node * 2 + 1] = true;
      }
      return;
    }
    int mid = (start + end) / 2;
    updateRange(node * 2, start, mid, l, r, val);
    updateRange(node * 2 + 1, mid + 1, end, l, r, val);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
  }

  T queryRange(int node, int start, int end, int l, int r) {
    if (start > end or start > r or end < l) return 0;
    if (updated[node]) {
      tree[node] = lazy[node] * (end - start + 1);
      if (start != end) {
        lazy[node * 2] = lazy[node];
        lazy[node * 2 + 1] = lazy[node];
        updated[node * 2] = updated[node];
        updated[node * 2 + 1] = updated[node];
      }
      updated[node] = false;
    }
    if (start >= l and end <= r) return tree[node];
    int mid = (start + end) / 2;
    T p1 = queryRange(node * 2, start, mid, l, r);
    T p2 = queryRange(node * 2 + 1, mid + 1, end, l, r);
    return p1 + p2;
  }

 public:
  SegmentTree(const std::vector<T>& arr) {
    n = arr.size();
    tree.resize(4 * n);
    lazy.resize(4 * n);
    updated.resize(4 * n, false);
    build(1, 0, n - 1, arr);
  }

  void updateRange(int l, int r, T val) { updateRange(1, 0, n - 1, l, r, val); }

  T queryRange(int l, int r) { return queryRange(1, 0, n - 1, l, r); }
};
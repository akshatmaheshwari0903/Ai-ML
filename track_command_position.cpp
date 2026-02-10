// Track Command Position
//
// A rooted tree represents a command-propagation network.
// When a node sends a command, it is received by nodes in its subtree in this order:
// - the node itself first
// - then recursively each child subtree, processing children by increasing node id.
//
// For each query (start, k), return the k-th node in this traversal of start's subtree,
// or -1 if the subtree contains fewer than k nodes.
//
// Optimal approach:
// - Build children lists, sort each by id.
// - Perform an iterative preorder DFS to produce a preorder array "order".
// - In preorder, each subtree is a contiguous segment [tin[u], tin[u] + subSize[u]).
// - Answer each query in O(1): idx = tin[start] + (k - 1).
//
// Complexity:
// - Preprocessing: O(n log n) due to sorting children lists (overall).
// - Each query: O(1).
// - Memory: O(n).

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>

namespace {

struct PreorderIndex {
  std::vector<int> order;      // preorder list of node ids
  std::vector<int> entryTime;  // entryTime[u] = index in order
  std::vector<int> subSize;    // subSize[u] = size of u's subtree in preorder
};

PreorderIndex buildPreorderIndex(const std::vector<int>& parent) {
  const int n = static_cast<int>(parent.size()) - 1;  // parent is 1-indexed

  int root = -1;
  std::vector<std::vector<int>> children(n + 1);
  children.reserve(n + 1);

  for (int u = 1; u <= n; ++u) {
    const int p = parent[u];
    if (p == -1) {
      root = u;
    } else if (p >= 1 && p <= n) {
      children[p].push_back(u);
    } else {
      // Invalid parent value; still keep structure best-effort by treating as root.
      root = u;
    }
  }
  if (root == -1) root = 1;  // best-effort fallback

  for (int u = 1; u <= n; ++u) {
    auto& ch = children[u];
    std::sort(ch.begin(), ch.end());
  }

  PreorderIndex idx;
  idx.order.reserve(n);
  idx.entryTime.assign(n + 1, -1);
  idx.subSize.assign(n + 1, 0);

  struct Frame {
    int u;
    int nextChildIdx;
  };

  std::vector<Frame> stack;
  stack.reserve(n);
  stack.push_back(Frame{root, 0});

  auto enterNode = [&](int u) {
    idx.entryTime[u] = static_cast<int>(idx.order.size());
    idx.order.push_back(u);
  };

  enterNode(root);

  while (!stack.empty()) {
    Frame& top = stack.back();
    const int u = top.u;
    if (top.nextChildIdx < static_cast<int>(children[u].size())) {
      const int v = children[u][top.nextChildIdx++];
      stack.push_back(Frame{v, 0});
      enterNode(v);
      continue;
    }

    // All children processed; finalize subtree size for u.
    idx.subSize[u] = static_cast<int>(idx.order.size()) - idx.entryTime[u];
    stack.pop_back();
  }

  return idx;
}

int kthNodeInSubtreePreorder(const PreorderIndex& idx, int startNode, std::int64_t k) {
  if (startNode <= 0 || startNode >= static_cast<int>(idx.entryTime.size())) return -1;
  if (k <= 0) return -1;

  const int tin = idx.entryTime[startNode];
  if (tin < 0) return -1;

  const int size = idx.subSize[startNode];
  if (k > static_cast<std::int64_t>(size)) return -1;

  const std::int64_t pos = static_cast<std::int64_t>(tin) + (k - 1);
  if (pos < 0 || pos >= static_cast<std::int64_t>(idx.order.size())) return -1;
  return idx.order[static_cast<std::size_t>(pos)];
}

}  // namespace

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n = 0;
  if (!(std::cin >> n)) return 0;
  if (n <= 0) return 0;

  // Parent array is 1-indexed; parent[root] == -1.
  std::vector<int> parent(n + 1, -1);
  for (int i = 1; i <= n; ++i) {
    std::cin >> parent[i];
  }

  const PreorderIndex idx = buildPreorderIndex(parent);

  int q = 0;
  std::cin >> q;
  for (int qi = 0; qi < q; ++qi) {
    int start = 0;
    std::int64_t k = 0;
    std::cin >> start >> k;
    const int ans = kthNodeInSubtreePreorder(idx, start, k);
    std::cout << ans << "\n";
  }

  return 0;
}


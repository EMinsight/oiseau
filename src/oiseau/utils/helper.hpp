#pragma once
#include <unordered_map>

namespace oiseau::utils {
template <typename K, typename V>
std::unordered_map<V, K> reverse_map(const std::unordered_map<K, V> &m) {
  std::unordered_map<V, K> r;
  for (const auto &[k, v] : m) r[v] = k;
  return r;
}
}  // namespace oiseau::utils

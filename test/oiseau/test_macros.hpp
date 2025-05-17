#define EXPECT_FLOATS_NEARLY_EQ(expected, actual, threshold)          \
  ASSERT_EQ(expected.size(), actual.size()) << "Array sizes differ."; \
  for (size_t idx = 0; idx < expected.size(); ++idx) {                \
    auto diff = std::abs(expected[idx] - actual[idx]);                \
    if (diff > threshold) {                                           \
      FAIL() << "Stopped at first mismatch:\n"                        \
             << "  index     : " << idx << "\n"                       \
             << "  expected  : " << expected[idx] << "\n"             \
             << "  actual    : " << actual[idx] << "\n"               \
             << "  difference: " << diff << "\n"                      \
             << "  threshold : " << threshold;                        \
    }                                                                 \
  }

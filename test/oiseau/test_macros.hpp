#define EXPECT_FLOATS_NEARLY_EQ(expected, actual, thresh)                       \
  EXPECT_EQ(expected.size(), actual.size()) << "Array sizes differ.";           \
  for (size_t idx = 0; idx < std::min(expected.size(), actual.size()); ++idx) { \
    EXPECT_NEAR(expected[idx], actual[idx], thresh) << "at index: " << idx;     \
  }

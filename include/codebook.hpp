#pragma once
#include <vector>
#include <opencv2/core.hpp>

namespace ipb {
  cv::Mat kMeans(const std::vector<cv::Mat> &descriptors, int k, int max_iter);
}; // namespace ipb

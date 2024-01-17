#pragma once

#include <opencv2/core.hpp>
#include <opencv2/flann.hpp>
#include <opencv2/highgui.hpp>
#include <vector>

namespace ipb {
class BowDictionary {
 public:
  // Singleton pattern
  static BowDictionary& getInstance();

  // getters method
  int max_iterations() const;
  int size() const;
  const std::vector<cv::Mat>& descriptors() const;
  const cv::Mat& vocabulary() const;
  int total_features() const;
  bool empty() const;

  // setters method
  void set_max_iterations(int max_iter);
  void set_size(int size);
  void set_descriptors(const std::vector<cv::Mat>& d);
  void set_params(int size, int max_iter, const std::vector<cv::Mat>& d);

 private:
  BowDictionary() = default;  // private constructor
  int max_iter_ = 0;  // maximum number of iterations for the clustering algorithm
  int size_ = 0;      // dictionary size, ie, the number of words
  std::vector<cv::Mat> descriptors_;  // input descriptors
  cv::Mat vocabulary_;                // computed dictionary/codebook
};
}  // namespace ipb

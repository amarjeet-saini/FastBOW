#include "bow_dictionary.hpp"
#include "codebook.hpp"

using namespace ipb;

int BowDictionary::max_iterations() const {
    return max_iter_;
}

int BowDictionary::size() const {
    return vocabulary_.size().height;
}

const std::vector<cv::Mat>& BowDictionary::descriptors() const {
    return descriptors_;
}

const cv::Mat& BowDictionary::vocabulary() const {
    return vocabulary_;
}

int BowDictionary::total_features() const {
    int total = 0;
    for(const auto& descriptor:descriptors_) {
        total += descriptor.rows;
    }
    return total;
}

bool BowDictionary::empty() const {
    return vocabulary_.size().height == 0;
}

void BowDictionary::set_max_iterations(int max_iter) {
    max_iter_ = max_iter;
    //updateDictionary();
}

void BowDictionary::set_size(int dictionary_size) {
    size_ = dictionary_size;
    //updateDictionary();
}

void BowDictionary::set_descriptors(const std::vector<cv::Mat>& descriptors) {
  std::vector<cv::Mat> out;
  out.reserve(descriptors.size());
  for (const auto& x: descriptors) out.push_back(x);
  descriptors_ = out;
}

void BowDictionary::set_params(int max_iter, int dictionary_size, const std::vector<cv::Mat>& descriptors) {
    set_max_iterations(max_iter);
    set_size(dictionary_size);
    set_descriptors(descriptors);
    vocabulary_ = kMeans(descriptors, dictionary_size, max_iter);
    //this->vocabulary_ = kMeans(descriptors, dictionary_size, max_iter);
}

BowDictionary& BowDictionary::getInstance() {
    static ipb::BowDictionary instance;
    return instance;
}

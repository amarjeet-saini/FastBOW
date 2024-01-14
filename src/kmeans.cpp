#include "kmeans.hpp"

cv::Mat ipb::kMeans(const std::vector<cv::Mat> &descriptors, int k, int max_iter)
{
    // Check if the input descriptors vector is not empty
    if (descriptors.empty()) {
        // Handle the error appropriately, such as throwing an exception
        throw std::invalid_argument("Input descriptors vector is empty");
    }

    // Combine all descriptors into a single matrix
    cv::Mat data;
    for (const auto &descriptor : descriptors) {
        data.push_back(descriptor);
    }

    // Convert the data matrix to the required type (32-bit float)
    data.convertTo(data, CV_32F);

    // Set up the k-means parameters
    cv::TermCriteria term_criteria(cv::TermCriteria::EPS + cv::TermCriteria::MAX_ITER, max_iter, 1.0);
    cv::Mat labels, centers;

    // Perform k-means clustering
    cv::kmeans(data, k, labels, term_criteria, 1, cv::KMEANS_RANDOM_CENTERS, centers);

    // Return the k-means centroids
    return centers;    
}

#include "convert_dataset.hpp"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>

void ipb::serialization::sifts::ConvertDataset(const fs::path& img_path) {
    for (const auto &entry : fs::directory_iterator(img_path)) {
        cv::Mat image = cv::imread(entry.path(), cv::IMREAD_COLOR);
        if (image.empty()) {
            std::cerr << "Unable to read image\n";
            continue;
        }

        // detect sift key point
        auto detector = cv::SiftFeatureDetector::create();
        std::vector<cv::KeyPoint> keypoints;
        detector->detect(image, keypoints);
  
        // compute sift descriptor
        cv::Mat temp;
        auto extractor = cv::SiftDescriptorExtractor::create();
        extractor->compute(image, keypoints, temp);

        std::string s =  "../data/freiburg/bin/" + entry.path().filename().replace_extension(".bin").u8string();
        ipb::serialization::Serialize(temp, s);
        
        // release resource explicitly
        keypoints.clear();
        temp.release();
        extractor.release();
    }
}

std::vector<cv::Mat> ipb::serialization::sifts::LoadDataset(const fs::path& bin_path) {
    // buffer store deserialize images
    std::vector<cv::Mat> bin_images;
    for (const auto &entry : fs::directory_iterator(bin_path)) {   
        cv::Mat bin_image = ipb::serialization::Deserialize(entry.path());
        // check if deserialize was successful
        if (!bin_image.empty())  bin_images.push_back(bin_image);
    }
    return bin_images;
}
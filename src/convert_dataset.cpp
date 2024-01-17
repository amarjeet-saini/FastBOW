#include "convert_dataset.hpp"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>

void ipb::serialization::sifts::ConvertDataset(const fs::path& img_path) {
    // create bin dir to store .bin files
    std::experimental::filesystem::path bin_dir="bin";
    std::experimental::filesystem::create_directory(img_path.parent_path()/bin_dir);

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
        cv::Mat buffer;
        auto extractor = cv::SiftDescriptorExtractor::create();
        extractor->compute(image, keypoints, buffer);
        
        // store sift descriptor in .bin file
        std::experimental::filesystem::path fileToCopy = entry;
        fileToCopy.replace_extension(".bin");
        auto out_file= img_path.parent_path()/bin_dir/ fileToCopy.filename();

        //fileToCopy.filename();
        ipb::serialization::Serialize(buffer, out_file);
        
        // release resource explicitly
        keypoints.clear();
        buffer.release();
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

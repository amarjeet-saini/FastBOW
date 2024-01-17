#include <fstream>
#include <iostream>
#include <tuple>
#include "convert_dataset.hpp"
#include "image_browser.hpp"
#include "serialize.hpp"
#include "codebook.hpp"
#include "bow_dictionary.hpp"

int main(int argc, char *argv[]) {
  // create image browser
  const std::string stylesheet{"style.css"};
  const std::string title{"Image Browser"};

  image_browser::ScoredImage image;
  image_browser::ImageRow image_row;
  std::vector<image_browser::ImageRow> images;
  std::ifstream fin("/home/amarjeet/Project/FastBOW/src/config.txt");
  std::string path;
  float score;
  size_t i = 0;
  while (fin >> path >> score) {
    image_row[i++] = make_tuple(path, score);
    if (i == 3) {
      i = 0;
      images.push_back(image_row);
    }
  }

  image_browser::CreateImageBrowser(title, stylesheet, images);

  // serialize image and store sift descriptor as .bin file
  const std::string imgpath = "../../data/freiburg/";
  ipb::serialization::sifts::ConvertDataset(imgpath + "images");

  // load .bin files
  std::vector<cv::Mat> sift_descriptors;
  for (const auto &entry : fs::directory_iterator(imgpath + "bin")) {
    sift_descriptors.push_back(ipb::serialization::Deserialize(entry.path()));
  }

  /*
  int dict_size = 50; // Number of visual words
  int max_iter = 10; // Maximum iterations
  cv::Mat kMeansCentroids = ipb::kMeans(sift_descriptors, dict_size, max_iter);
  std::cout << "K-Means Centroids:\n" << kMeansCentroids << std::endl;
  */
  return 0;
}

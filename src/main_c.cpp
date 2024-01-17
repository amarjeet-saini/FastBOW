#include <opencv2/opencv.hpp>
#include "serialize.hpp" 
#include "convert_dataset.hpp"

int main() 
{  
    const std::string path = "../../data/freiburg/";
    ipb::serialization::sifts::ConvertDataset(path + "images");
    std::vector<cv::Mat> bimg;
    for (const auto &entry : fs::directory_iterator(path + "bin")) {
        bimg.push_back(ipb::serialization::Deserialize(entry.path()));
    }
    std::cout << bimg.size() << std::endl;
    /* 
    std::cout << "hello, opencv" << std::endl;
    
    cv::Mat image = bimg[0];
    if (image.empty()) 
    {
        std::cerr << "Image not found\n";
        return 1;
    }
    
    cv::Mat image = cv::imread("../data/freiburg/images/imageCompressedCam0_0000000.png", cv::IMREAD_COLOR);
    const std::string file_name = "lenna.bin";
    // serialize
    ipb::serialization::Serialize(image, file_name);
    
    // deserialize
    cv::Mat result = ipb::serialization::Deserialize("lenna.bin");

    // display
    const std::string win_name1("lenna"); 
    //const std::string win_name2("serial"); 
    cv::namedWindow(win_name1);
    //cv::namedWindow(win_name2);
    cv::imshow(win_name1, result);
    //cv::imshow(win_name2, result);
    cv::waitKey(0);
    */
    return 0;
}

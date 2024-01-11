#include "serialize.hpp"

void ipb::serialization::Serialize(const cv::Mat& m,
                                   const std::string& filename) {
  std::ofstream file(filename, std::ios::out | std::ios::binary | std::ios::app);
  if (!file.is_open()) {
    std::cerr << "Error opening file: " << filename << "\n";
    throw std::runtime_error("Unable to open file");
  }

  int rows = m.rows;
  int cols = m.cols;
  int type = m.type();

  file.write(reinterpret_cast<char*>(&rows), sizeof(rows));
  file.write(reinterpret_cast<char*>(&cols), sizeof(cols));
  file.write(reinterpret_cast<char*>(&type), sizeof(type));
  file.write(reinterpret_cast<char*>(m.data), m.total() * m.elemSize());

  // Write pixel data to file
  if (m.isContinuous()) {
    file.write(reinterpret_cast<const char*>(m.data), m.total() * m.elemSize());
  }
  file.close();
}

cv::Mat ipb::serialization::Deserialize(const std::string& filename) {
  std::ifstream file;
  file.open(filename, std::ios::binary);
  if (!file.is_open()) {
    std::cerr << "Error opening file: " << filename << "\n";
    throw std::runtime_error("Unable to open file");
  }

  // read row, col & dtype
  int r, c, type;
  file.read(reinterpret_cast<char*>(&r), sizeof(r));
  file.read(reinterpret_cast<char*>(&c), sizeof(c));
  file.read(reinterpret_cast<char*>(&type), sizeof(type));
  
  // buffer to store deserialized data
  cv::Mat m(r, c, type);

  if (m.empty()) {
    std::cerr << "Error creating cv::Mat during deserialization " << std::endl;
    throw std::runtime_error("Error creating cv::Mat during deserialization");
  }

  file.read(reinterpret_cast<char*>(m.data), m.total() * m.elemSize());
  file.close();
  return m;
}


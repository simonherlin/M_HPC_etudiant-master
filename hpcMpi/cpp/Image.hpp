#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <Eigen/Dense>
#include <string>

namespace Image {

    using Mat = Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;

    // read image
    Mat readPnm(const std::string & filename);

    // write image
    void writePnm(const std::string &filename, const Eigen::Ref<Mat> data); 

    // Returns a blurred subimage of data1 (using the specified radius for the convolution kernel).
    // The blurred region is, in data1, (x0, x1, y0, y1).
    // The size of the subimage is (x1-x0, y1-y0)
    Mat blur(const Eigen::Ref<Mat> data1, int radius, int x0, int x1, int y0, int y1);

}  // namespace Image

#endif


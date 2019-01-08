#include "Image.hpp"

#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>

Image::Mat Image::readPnm(const std::string & filename) 
{
    int width, height;
    std::ifstream is(filename);
    std::string tmp;
    // read magic number
    std::getline(is, tmp);
    if (tmp != "P2")
        return Mat(0, 0);
    // read comments
    std::getline(is, tmp);
    while (tmp[0] == '#')
        std::getline(is, tmp);
    // read size
    std::stringstream ss(tmp);
    ss >> width >> height;
    // read max value
    std::getline(is, tmp);
    // read data
    auto data = Mat(height, width);
    for (int i=0; i<height; i++)
        for (int j=0; j<width; j++)
        {
            int pixel;
            is >> pixel;
            data(i,j) = pixel;
        }
    return data;
}

void Image::writePnm(const std::string &filename, const Eigen::Ref<Image::Mat> data) 
{
    std::ofstream os(filename);
    // write magic number
    os << "P2" << std::endl;
    // write size
    os << data.cols() << ' ' << data.rows() << std::endl;
    // write max value
    os << "255" << std::endl;
    // write data
    // os << data;
    for (int i=0; i<data.rows(); i++)
        for (int j=0; j<data.cols(); j++)
            os << data(i,j) << ' ';
 }

Image::Mat Image::blur(const Eigen::Ref<Image::Mat> data1, int radius, int x0, int x1, int y0, int y1)
{
    const int width = data1.cols();
    const int height = data1.rows();
    const int width2 = x1-x0;
    const int height2 = y1-y0;
    assert(width2 > 0);
    assert(height2 > 0);
    assert(radius >= 0);
    auto data2 = Mat(height2, width2);
    for (int x=x0; x<x1; x++)
    {
        for (int y=y0; y<y1; y++)
        {
            // compute pixel (mean kernel)
            int s = 0;
            int n = 0;
            for (int lx=-radius; lx<radius; lx++)
            {
                for (int ly=-radius; ly<radius; ly++)
                {
                    int xx = x+lx;
                    int yy = y+ly;
                    if (xx >= 0 and xx < width and yy >= 0 and yy < height)
                    {
                        s += data1(y+ly, x+lx);
                        n++;
                    }
                }
            }
            int pixel = 0;
            if (n>0)
               pixel = s / n;
            if (x==x0 or y==y0 or x==x1-1 or y==y1-1) 
                pixel = 0;  // draw border
            data2(y-y0, x-x0) = pixel;
        }
    }
    return data2;
}


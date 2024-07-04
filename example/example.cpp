
#include <iostream>
#include "opencv2/opencv.hpp"
#include "voml/voml.h"

const auto data = toml::parse("/root/master/00-dev/Module-Tomlpp/example/example.toml");

void MatExample() {
    auto matu = toml::find<cv::Mat>(data, "mat", "mat_u");
    std::cout << matu.type() << matu << std::endl;
    auto matc = toml::find<cv::Mat>(data, "mat", "mat_c");
    std::cout << matc.type() << matc << std::endl;
    auto matw = toml::find<cv::Mat>(data, "mat", "mat_w");
    std::cout << matw.type() << matw << std::endl;
    auto mats = toml::find<cv::Mat>(data, "mat", "mat_s");
    std::cout << mats.type() << mats << std::endl;
    auto mati = toml::find<cv::Mat>(data, "mat", "mat_i");
    std::cout << mati.type() << mati << std::endl;
    auto matf = toml::find<cv::Mat>(data, "mat", "mat_f");
    std::cout << matf.type() << matf << std::endl;
    auto matd = toml::find<cv::Mat>(data, "mat", "mat_d");
    std::cout << matd.type() << matd << std::endl;

    std::cout << "================================" << std::endl;
    const toml::value toml{{"mat_u", matu}, {"mat_c", matc}, {"mat_w", matw}, {"mat_s", mats},
                           {"mat_i", mati}, {"mat_f", matf}, {"mat_d", matd}};
    std::cout << toml;
    std::cout << "================================" << std::endl;
}

void SizeExample() {
    auto sizei = toml::find<cv::Size2i>(data, "size", "sizei");
    std::cout << sizei.width << "  " << sizei.height << std::endl;
    auto sized = toml::find<cv::Size2d>(data, "size", "sized");
    std::cout << sized.width << "  " << sized.height << std::endl;

    std::cout << "================================" << std::endl;
    const toml::value toml{{"sizei", sizei}, {"sized", sized}};
    std::cout << toml;
    std::cout << "================================" << std::endl;
}

void PointExample() {
    auto point2i = toml::find<cv::Point2i>(data, "point", "point_2i");
    std::cout << point2i.x << "  " << point2i.y << std::endl;
    auto point2f = toml::find<cv::Point2f>(data, "point", "point_2f");
    std::cout << point2f.x << "  " << point2f.y << std::endl;

    std::cout << "================================" << std::endl;
    const toml::value toml{{"point2i", point2i}, {"point2f", point2f}};
    std::cout << toml;
    std::cout << "================================" << std::endl;

    auto point3u = toml::find<cv::Point3_<uchar>>(data, "point", "point_3u");
    std::cout << (int)point3u.x << "  " << (int)point3u.y << "  " << (int)point3u.z << std::endl;
    auto point3d = toml::find<cv::Point3d>(data, "point", "point_3d");
    std::cout << point3d.x << "  " << point3d.y << "  " << point3d.z << std::endl;

    std::cout << "================================" << std::endl;
    const toml::value toml2{{"point3u", point3u}, {"point3d", point3d}};
    std::cout << toml2;
    std::cout << "================================" << std::endl;
}

int main() {
    MatExample();
    SizeExample();
    PointExample();
}
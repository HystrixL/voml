
#include <iostream>
#include "opencv2/opencv.hpp"
#include "tomlpp.hpp"

int main() {
    const auto data = toml::parse("/extend/00-dev/Module-Tomlpp/example.toml");
    auto matu = toml::find<cv::Mat>(data, "mat_u");
    std::cout << matu.type() << matu << std::endl;
    auto matc = toml::find<cv::Mat>(data, "mat_c");
    std::cout << matc.type() << matc << std::endl;
    auto matw = toml::find<cv::Mat>(data, "mat_w");
    std::cout << matw.type() << matw << std::endl;
    auto mats = toml::find<cv::Mat>(data, "mat_s");
    std::cout << mats.type() << mats << std::endl;
    auto mati = toml::find<cv::Mat>(data, "mat_i");
    std::cout << mati.type() << mati << std::endl;
    auto matf = toml::find<cv::Mat>(data, "mat_f");
    std::cout << matf.type() << matf << std::endl;
    auto matd = toml::find<cv::Mat>(data, "mat_d");
    std::cout << matd.type() << matd << std::endl;
    std::cout << "================================" << std::endl;
    const toml::value toml{{"mat_u", matu}, {"mat_c", matc}, {"mat_w", matw}, {"mat_s", mats},
                           {"mat_i", mati}, {"mat_f", matf}, {"mat_d", matd}};
    std::cout << toml;
}
#pragma once

#include <opencv2/core/hal/interface.h>
#include <sys/types.h>
#include <opencv2/core/persistence.hpp>
#include <opencv2/core/traits.hpp>
#include <string>
#include "details.hpp"

namespace toml {
template <>
struct from<cv::Mat> {
    template <typename C, template <typename...> class M, template <typename...> class A>
    static cv::Mat from_toml(const basic_value<C, M, A>& v) {
        switch (find<std::string>(v, "dt")[0]) {
            case 'u':
                return voml::Toml2Mat<uchar>(v);
            case 'c':
                return voml::Toml2Mat<char>(v);
            case 'w':
                return voml::Toml2Mat<ushort>(v);
            case 's':
                return voml::Toml2Mat<short>(v);
            case 'i':
                return voml::Toml2Mat<int>(v);
            case 'f':
                return voml::Toml2Mat<float>(v);
            case 'd':
                return voml::Toml2Mat<double>(v);
            default:
                throw voml::CastException{"Unknow dt"};
        }
    }
};

template <>
struct into<cv::Mat> {
    static toml::value into_toml(const cv::Mat& mat) {
        switch (mat.type()) {
            case 0:
                return voml::Mat2Toml<uchar>(mat);
            case 1:
                return voml::Mat2Toml<char>(mat);
            case 2:
                return voml::Mat2Toml<ushort>(mat);
            case 3:
                return voml::Mat2Toml<short>(mat);
            case 4:
                return voml::Mat2Toml<int>(mat);
            case 5:
                return voml::Mat2Toml<float>(mat);
            case 6:
                return voml::Mat2Toml<double>(mat);
            default:
                throw voml::CastException{"Unknow type"};
        }
    }
};
}  // namespace toml
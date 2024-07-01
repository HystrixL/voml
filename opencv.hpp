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

template <typename Tp>
struct from<cv::Size_<Tp>> {
    template <typename C, template <typename...> class M, template <typename...> class A>
    static cv::Size_<Tp> from_toml(const basic_value<C, M, A>& v) {
        switch (find<std::string>(v, "dt")[0]) {
            case 'u':
                return voml::Toml2Size<uchar>(v);
            case 'c':
                return voml::Toml2Size<char>(v);
            case 'w':
                return voml::Toml2Size<ushort>(v);
            case 's':
                return voml::Toml2Size<short>(v);
            case 'i':
                return voml::Toml2Size<int>(v);
            case 'f':
                return voml::Toml2Size<float>(v);
            case 'd':
                return voml::Toml2Size<double>(v);
            default:
                throw voml::CastException{"Unknow dt"};
        }
    }
};

template <typename Tp>
struct into<cv::Size_<Tp>> {
    static toml::value into_toml(const cv::Size_<Tp>& size) {
        switch (size.type()) {
            case 0:
                return voml::Size2Toml<uchar>(size);
            case 1:
                return voml::Size2Toml<char>(size);
            case 2:
                return voml::Size2Toml<ushort>(size);
            case 3:
                return voml::Size2Toml<short>(size);
            case 4:
                return voml::Size2Toml<int>(size);
            case 5:
                return voml::Size2Toml<float>(size);
            case 6:
                return voml::Size2Toml<double>(size);
            default:
                throw voml::CastException{"Unknow type"};
        }
    }
};

template <typename Tp>
struct from<cv::Point_<Tp>> {
    template <typename C, template <typename...> class M, template <typename...> class A>
    static cv::Size_<Tp> from_toml(const basic_value<C, M, A>& v) {
        switch (find<std::string>(v, "dt")[0]) {
            case 'u':
                return voml::Toml2Size<uchar>(v);
            case 'c':
                return voml::Toml2Size<char>(v);
            case 'w':
                return voml::Toml2Size<ushort>(v);
            case 's':
                return voml::Toml2Size<short>(v);
            case 'i':
                return voml::Toml2Size<int>(v);
            case 'f':
                return voml::Toml2Size<float>(v);
            case 'd':
                return voml::Toml2Size<double>(v);
            default:
                throw voml::CastException{"Unknow dt"};
        }
    }
};

template <typename Tp>
struct into<cv::Point_<Tp>> {
    static toml::value into_toml(const cv::Point_<Tp>& point) {
        switch (point.type()) {
            case 0:
                return voml::Size2Toml<uchar>(point);
            case 1:
                return voml::Size2Toml<char>(point);
            case 2:
                return voml::Size2Toml<ushort>(point);
            case 3:
                return voml::Size2Toml<short>(point);
            case 4:
                return voml::Size2Toml<int>(point);
            case 5:
                return voml::Size2Toml<float>(point);
            case 6:
                return voml::Size2Toml<double>(point);
            default:
                throw voml::CastException{"Unknow type"};
        }
    }
};
}  // namespace toml
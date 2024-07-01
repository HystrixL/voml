#pragma once

#include <opencv2/core/hal/interface.h>
#include <sys/types.h>
#include <exception>
#include <opencv2/core/persistence.hpp>
#include <opencv2/core/traits.hpp>
#include <opencv2/core/types.hpp>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>
#include "toml11/toml.hpp"

namespace voml {
class CastException : public std::exception {
   public:
    explicit CastException(std::string_view content) : content_(content) {}

    [[nodiscard]] const char* what() const noexcept override { return content_.c_str(); }

   private:
    std::string content_{};
};
template <typename T>
cv::Mat Vector2Mat(const std::vector<T>& data, const std::vector<int>& shape) {
    int ndims = static_cast<int>(shape.size());
    if (ndims == 0) {
        throw CastException{"Error: shape must have at least one dimension."};
    }

    if (shape.size() != 2) {
        throw CastException{"Error: all dimensions in shape must be positive."};
    }
    int totalSize = shape[0] * shape[1];

    if (totalSize != data.size()) {
        throw CastException{"Error: data size does not match shape."};
    }

    cv::Mat mat(ndims, shape.data(), cv::DataType<T>::type);
    memcpy(mat.data, data.data(), totalSize * sizeof(T));

    return mat;
}

template <typename T, typename C, template <typename...> class M, template <typename...> class A>
cv::Mat Toml2Mat(const toml::basic_value<C, M, A>& v) {
    int rows = toml::find<int>(v, "rows");
    int cols = toml::find<int>(v, "cols");
    std::vector<int> shape{rows, cols};
    return voml::Vector2Mat(toml::find<std::vector<T>>(v, "data"), shape);
}

template <typename Tp, typename C, template <typename...> class M, template <typename...> class A>
cv::Size_<Tp> Toml2Size(const toml::basic_value<C, M, A>& v) {
    return cv::Size_<Tp>{toml::find<Tp>(v, "width"),toml::find<Tp>(v, "height")};
}

template <typename Tp, typename C, template <typename...> class M, template <typename...> class A>
cv::Point_<Tp> Toml2Point(const toml::basic_value<C, M, A>& v) {
    return cv::Point_<Tp>{toml::find<Tp>(v, "x"),toml::find<Tp>(v, "y")};
}

template <typename T>
toml::value Mat2Toml(cv::Mat mat) {
    int rows = mat.rows;
    int cols = mat.cols;
    auto totalSize = rows * cols;
    std::vector<T> data(totalSize);
    memcpy(data.data(), mat.data, totalSize * sizeof(T));
    std::string dt{};
    if constexpr (std::is_same_v<T, uchar>) {
        dt = "u";
    } else if constexpr (std::is_same_v<T, char>) {
        dt = "c";
    } else if constexpr (std::is_same_v<T, ushort>) {
        dt = "w";
    } else if constexpr (std::is_same_v<T, short>) {
        dt = "s";
    } else if constexpr (std::is_same_v<T, int>) {
        dt = "i";
    } else if constexpr (std::is_same_v<T, float>) {
        dt = "f";
    } else if constexpr (std::is_same_v<T, double>) {
        dt = "d";
    } else {
        dt = "?";
    }
    return toml::value{{"rows", rows}, {"cols", cols}, {"dt", dt}, {"data", data}};
}

template <typename Tp>
toml::value Size2Toml(cv::Size_<Tp> size) {
    int width = size.width;
    int height = size.height;
    std::string dt{};
    if constexpr (std::is_same_v<Tp, uchar>) {
        dt = "u";
    } else if constexpr (std::is_same_v<Tp, char>) {
        dt = "c";
    } else if constexpr (std::is_same_v<Tp, ushort>) {
        dt = "w";
    } else if constexpr (std::is_same_v<Tp, short>) {
        dt = "s";
    } else if constexpr (std::is_same_v<Tp, int>) {
        dt = "i";
    } else if constexpr (std::is_same_v<Tp, float>) {
        dt = "f";
    } else if constexpr (std::is_same_v<Tp, double>) {
        dt = "d";
    } else {
        dt = "?";
    }
    return toml::value{{"width", width}, {"height", height}, {"dt", dt}};
}

template <typename Tp>
toml::value Point2Toml(cv::Point_<Tp> point) {
    int x = point.x;
    int y = point.y;
    std::string dt{};
    if constexpr (std::is_same_v<Tp, uchar>) {
        dt = "u";
    } else if constexpr (std::is_same_v<Tp, char>) {
        dt = "c";
    } else if constexpr (std::is_same_v<Tp, ushort>) {
        dt = "w";
    } else if constexpr (std::is_same_v<Tp, short>) {
        dt = "s";
    } else if constexpr (std::is_same_v<Tp, int>) {
        dt = "i";
    } else if constexpr (std::is_same_v<Tp, float>) {
        dt = "f";
    } else if constexpr (std::is_same_v<Tp, double>) {
        dt = "d";
    } else {
        dt = "?";
    }
    return toml::value{{"width", x}, {"height", y}, {"dt", dt}};
}

}  // namespace voml

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
#pragma once

#include <opencv2/core/hal/interface.h>
#include <sys/types.h>
#include <exception>
#include <opencv2/core/persistence.hpp>
#include <opencv2/core/traits.hpp>
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

}  // namespace voml
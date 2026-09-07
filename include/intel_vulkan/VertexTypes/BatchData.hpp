#ifndef INTEL_VULKAN_BATCHDATA_HPP
#define INTEL_VULKAN_BATCHDATA_HPP

#include <cstddef>
#include <tuple>
#include <utility>
#include <vector>

namespace intel_vulkan::VertexTypes {

// Non-interleaved (structure-of-arrays) vertex attribute storage: one
// std::vector per attribute type instead of one packed record per vertex.
template <typename... Ts> struct BatchData {
public:
    static constexpr std::size_t attribute_type_count = sizeof...(Ts);

    BatchData() = default;

    explicit BatchData(std::vector<Ts>... data) : m_data(std::move(data)...) {}

    template <std::size_t Index>
    std::vector<std::tuple_element_t<Index, std::tuple<Ts...>>> const& data()
            const {
        return std::get<Index>(m_data);
    }

    template <std::size_t Index> std::size_t byteCount() const {
        using attribute_type = std::tuple_element_t<Index, std::tuple<Ts...>>;
        return sizeof(attribute_type) * std::get<Index>(m_data).size();
    }

    std::size_t attributeCount() const { return std::get<0>(m_data).size(); }

private:
    std::tuple<std::vector<Ts>...> m_data;
};

}  // namespace intel_vulkan::VertexTypes

#endif

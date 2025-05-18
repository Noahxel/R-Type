#pragma once

#include <iostream>
#include <iterator>
#include <optional>
#include <stdexcept>
#include <vector>

/**
 * @class SparseArray
 * @brief Template class for managing optional components in an ECS.
 *
 * This class implements a sparse array, which is an array that allows gaps in the occupied indices.
 * It is commonly used in ECS to manage components efficiently, allowing fast access and iteration
 * over the components while avoiding the overhead of large contiguous memory allocations for unused indices.
 * 
 * @tparam Component The component type to be stored in the sparse array.
 */
template <typename Component>
class SparseArray {
   public:
    using value_type = std::optional<Component>;                     ///< Optional type for the component, allowing for uninitialized gaps.
    using reference = value_type&;                                   ///< Reference to the value_type.
    using const_reference = const value_type&;                       ///< Constant reference to the value_type.
    using container_type = std::vector<value_type>;                  ///< Underlying container type.
    using size_type = typename container_type::size_type;            ///< Size type used by the container.
    using iterator = typename container_type::iterator;              ///< Iterator type for the container.
    using const_iterator = typename container_type::const_iterator;  ///< Constant iterator type for the container.

    SparseArray() = default;
    explicit SparseArray(size_type size) : data(size, std::nullopt) {}

    SparseArray(const SparseArray&) = default;
    SparseArray(SparseArray&&) noexcept = default;
    ~SparseArray() = default;
    SparseArray& operator=(const SparseArray&) = default;
    SparseArray& operator=(SparseArray&&) noexcept = default;

    reference operator[](size_type idx);
    const_reference operator[](size_type idx) const;

    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const;
    iterator end();
    const_iterator end() const;
    const_iterator cend() const;

    size_type size() const;

    reference addComponent(size_type pos);
    reference insertComponent(size_type pos, Component&& component);
    void removeComponent(size_type pos);
    size_type indexOf(const_reference comp) const;

    template <class... Params>
    reference emplaceComponent(size_type pos, Params&&... params);

    /**
     * @brief Removes the component at the specified position.
     * 
     * @param pos Index of the component to remove.
     */
    void remove(size_type pos) {
        if (pos < data.size()) {
            data[pos].reset();
        }
    }

    /**
     * @brief Ensures that the component at the specified position is initialized as nullopt.
     * 
     * @param pos Index of the component to initialize.
     */
    void add(size_type pos) {
        if (pos >= data.size()) {
            data.resize(pos + 1);
        }
        data[pos] = std::nullopt;
    }

    container_type data;  ///< The underlying container that stores the components.
};

template <typename Component>
typename SparseArray<Component>::reference SparseArray<Component>::operator[](size_type idx) {
    return data.at(idx);
}

template <typename Component>
typename SparseArray<Component>::const_reference SparseArray<Component>::operator[](size_type idx) const {
    return data.at(idx);
}

template <typename Component>
typename SparseArray<Component>::const_iterator SparseArray<Component>::begin() const {
    return data.begin();
}

template <typename Component>
typename SparseArray<Component>::const_iterator SparseArray<Component>::cbegin() const {
    return data.cbegin();
}

template <typename Component>
typename SparseArray<Component>::iterator SparseArray<Component>::end() {
    return data.end();
}

template <typename Component>
typename SparseArray<Component>::const_iterator SparseArray<Component>::cend() const {
    return data.cend();
}

template <typename Component>
typename SparseArray<Component>::size_type SparseArray<Component>::size() const {
    return data.size();
}

template <typename Component>
typename SparseArray<Component>::reference SparseArray<Component>::addComponent(size_type pos) {
    if (pos >= data.size())
        data.resize(pos + 1);
    data[pos] = std::nullopt;
    return data[pos];
}

template <typename Component>
typename SparseArray<Component>::reference SparseArray<Component>::insertComponent(size_type pos, Component&& component) {
    if (pos >= data.size())
        data.resize(pos + 1);
    data[pos] = std::forward<Component>(component);
    return data[pos];
}

template <typename Component>
void SparseArray<Component>::removeComponent(size_type pos) {
    if (pos < data.size())
        data[pos].reset();
}

template <typename Component>
typename SparseArray<Component>::size_type SparseArray<Component>::indexOf(const_reference comp) const {
    auto it = std::find(data.begin(), data.end(), comp);
    if (it == data.end())
        throw std::runtime_error("Component not found.");
    return std::distance(data.begin(), it);
}

template <typename Component>
template <class... Params>
typename SparseArray<Component>::reference SparseArray<Component>::emplaceComponent(size_type pos, Params&&... params) {
    if (pos >= data.size())
        data.resize(pos + 1);
    data[pos] = std::make_optional<Component>(std::forward<Params>(params)...);
    return data[pos];
}

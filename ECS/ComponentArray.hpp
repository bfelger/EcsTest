///////////////////////////////////////////////////////////////////////////////
// ComponentArray.hpp
///////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef COMPONENT_ARRAY_HPP
#define COMPONENT_ARRAY_HPP

#include "Entity.hpp"

#include <array>
#include <cassert>
#include <cstdint>
#include <unordered_map>

class IComponentArray {
public:
    virtual ~IComponentArray() = default;
    virtual void entity_destroyed(Entity entity) = 0;
};

template <typename _Type>
class ComponentArray : public IComponentArray {
public:

    constexpr bool contains_data(Entity entity)
    {
        return (entity_index_map.find(entity) != entity_index_map.end());
    }

    constexpr void insert_data(Entity entity, _Type component)
    {
        assert(!contains_data(entity) && "Component added to same entity more than once.");

        std::size_t new_index = end_index;
        entity_index_map[entity] = new_index;
        index_entity_map[new_index] = entity;
        components[new_index] = component;
        ++end_index;
    }

    constexpr void remove_data(Entity entity)
    {
        assert(contains_data(entity) && "Removing non-existent component.");

        // Copy last element into removed element's place we we stay packed.
        std::size_t removed_index = entity_index_map[entity];
        std::size_t last_index = end_index - 1;
        components[removed_index] = components[last_index];

        // Update mappings.
        Entity last_entity = index_entity_map[last_index];
        entity_index_map[last_entity] = removed_index;
        index_entity_map[removed_index] = last_entity;

        // Remove the entity.
        entity_index_map.erase(entity);
        index_entity_map.erase(last_index);

        --end_index;
    }

    constexpr _Type& get_data(Entity entity)
    {
        assert(contains_data(entity) && "Retrieving non-existent component.");

        return components[entity_index_map[entity]];
    }

    constexpr void entity_destroyed(Entity entity) override
    {
        if (contains_data(entity)) {
            remove_data(entity);
        }
    }

private:
    std::array<_Type, MAX_ENTITIES> components{};
    std::unordered_map<Entity, std::size_t> entity_index_map{};
    std::unordered_map<std::size_t, Entity> index_entity_map{};
    std::size_t end_index = 0;
};

#endif // !COMPONENT_ARRAY_HPP

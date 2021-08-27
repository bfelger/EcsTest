///////////////////////////////////////////////////////////////////////////////
// ComponentManager.hpp
///////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef COMPONENT_MANAGER_HPP
#define COMPONENT_MANAGER_HPP

#include "Component.hpp"
#include "ComponentArray.hpp"

#include <cassert>
#include <memory>
#include <typeinfo>
#include <unordered_map>

class ComponentManager {
public:
    template <typename _Type>
    constexpr void register_component()
    {
        auto type_name = get_type_name<_Type>();

        assert(!contains_type<_Type>() && "Registering component type more than once.");

        component_types.insert({type_name, next_component_type});
        component_arrays.insert({type_name, std::make_shared<ComponentArray<_Type>>()});

        ++next_component_type;
    }

    template <typename _Type>
    constexpr ComponentType get_component_type()
    {
        auto type_name = get_type_name<_Type>();

        assert(contains_type<_Type>() && "Component not registered before use.");

        return component_types[type_name];
    }

    template <typename _Type>
    constexpr void add_component(Entity entity, _Type component)
    {
        get_component_array<_Type>()->insert_data(entity, component);
    }

    template <typename _Type>
    constexpr void remove_component(Entity entity)
    {
        get_component_array<_Type>()->remove_data(entity);
    }

    template <typename _Type>
    constexpr _Type& get_component(Entity entity)
    {
        return get_component_array<_Type>()->get_data(entity);
    }

    void entity_destroyed(Entity entity)
    {
        for (const auto& pair : component_arrays) {
            const auto& component = pair.second;
            component->entity_destroyed(entity);
        }
    }

private:
    std::unordered_map<const char*, ComponentType> component_types{};
    std::unordered_map<const char*, std::shared_ptr<IComponentArray>> component_arrays{};
    ComponentType next_component_type{};

    template <typename _Type>
    static constexpr const char* get_type_name() noexcept
    {
        return typeid(_Type).name();
    }

    template <typename _Type>
    constexpr bool contains_type()
    {
        return (component_types.find(get_type_name<_Type>()) != component_types.end());
    }

    template <typename _Type>
    constexpr std::shared_ptr<ComponentArray<_Type>> get_component_array()
    {
        auto type_name = get_type_name<_Type>();

        assert(contains_type<_Type>() && "Component not registered before use.");

        return std::static_pointer_cast<ComponentArray<_Type>>(component_arrays[type_name]);
    }
};

#endif // !COMPONENT_MANAGER_HPP

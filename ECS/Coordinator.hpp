///////////////////////////////////////////////////////////////////////////////
// Coordinator.hpp
///////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef COORDINATOR_HPP
#define COORDINATOR_HPP

#include "Component.hpp"
#include "ComponentManager.hpp"
#include "Entity.hpp"
#include "EntityManager.hpp"
#include "SystemManager.hpp"

#include <memory>

class Coordinator {
public:
    void init()
    {
        component_manager = std::make_unique<ComponentManager>();
        entity_manager = std::make_unique<EntityManager>();
        system_manager = std::make_unique<SystemManager>();
    }

    Entity create_entity()
    {
        return entity_manager->create_entity();
    }

    void destroy_entity(Entity entity)
    {
        entity_manager->destroy_entity(entity);
        component_manager->entity_destroyed(entity);
        system_manager->entity_destroyed(entity);
    }

    template <typename _Type>
    constexpr void register_component()
    {
        component_manager->register_component<_Type>();
    }

    template <typename _Type>
    constexpr void add_component(Entity entity, _Type component)
    {
        component_manager->add_component<_Type>(entity, component);

        auto signature = entity_manager->get_signature(entity);
        signature.set(component_manager->get_component_type<_Type>(), true);
        entity_manager->set_signature(entity, signature);

        system_manager->entity_signature_changed(entity, signature);
    }

    template <typename _Type>
    constexpr void remove_component(Entity entity)
    {
        component_manager->remove_component<_Type>(entity);

        auto signature = entity_manager->get_signature(entity);
        signature.set(component_manager->get_component_type<_Type>(), false);
        entity_manager->set_signature(entity, signature);

        system_manager->entity_signature_changed(entity, signature);
    }

    template <typename _Type>
    constexpr _Type& get_component(Entity entity)
    {
        return component_manager->get_component<_Type>(entity);
    }

    template <typename _Type>
    constexpr ComponentType get_component_type()
    {
        return component_manager->get_component_type<_Type>();
    }

    template <typename _Type>
    constexpr std::shared_ptr<_Type> register_system()
    {
        return system_manager->register_system<_Type>();
    }

    template <typename _Type>
    constexpr void set_system_signature(Signature signature)
    {
        system_manager->set_signature<_Type>(signature);
    }

private:
    std::unique_ptr<ComponentManager> component_manager;
    std::unique_ptr<EntityManager> entity_manager;
    std::unique_ptr<SystemManager> system_manager;
};

#endif // !COORDINATOR_HPP

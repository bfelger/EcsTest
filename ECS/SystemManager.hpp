///////////////////////////////////////////////////////////////////////////////
// SystemManager.hpp
///////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef SYSTEM_MANAGER_HPP
#define SYSTEM_MANAGER_HPP

#include "Signature.hpp"
#include "System.hpp"

#include <memory>
#include <typeinfo>
#include <unordered_map>

class SystemManager {
public:
    template <typename _Type>
    constexpr std::shared_ptr<_Type> register_system()
    {
        auto type_name = get_type_name<_Type>();

        assert(!contains_system<_Type>() && "Registering system more than once.");

        auto system = std::make_shared<_Type>();
        systems.insert({ type_name, system });

        return system;
    }

    template <typename _Type>
    constexpr void set_signature(Signature signature)
    {
        auto type_name = get_type_name<_Type>();

        assert(contains_system<_Type>() && "System used before registered.");

        signatures.insert({ type_name, signature });
    }

    void entity_destroyed(Entity entity)
    {
        for (const auto& pair : systems) {
            const auto& system = pair.second;
            system->entities.erase(entity);
        }
    }

    void entity_signature_changed(Entity entity, Signature entity_signature)
    {
        for (const auto& pair : systems) {
            auto const& type = pair.first;
            auto const& system = pair.second;
            auto const& system_signature = signatures[type];

            // Assign the entity to any system that matches its signature
            if ((entity_signature & system_signature) == system_signature) {
                system->entities.insert(entity);
            }
            else {
                system->entities.erase(entity);
            }
        }
    }

private:
    template <typename _Type>
    static constexpr const char* get_type_name() noexcept
    {
        return typeid(_Type).name();
    }

    template <typename _Type>
    constexpr bool contains_system()
    {
        return (systems.find(get_type_name<_Type>()) != systems.end());
    }

    std::unordered_map<const char*, Signature> signatures{};
    std::unordered_map<const char*, std::shared_ptr<System>> systems{};
};

#endif // !SYSTEM_MANAGER_HPP

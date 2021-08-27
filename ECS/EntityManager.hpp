///////////////////////////////////////////////////////////////////////////////
// EntityManager.hpp
///////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include "Entity.hpp"
#include "Signature.hpp"

#include <array>
#include <queue>
#include <cassert>

class EntityManager {
public:
    EntityManager()
    {
        for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
            available_entities.push(entity);
        }
    }

    Entity create_entity()
    {
        assert(entity_count < MAX_ENTITIES && "Too many entities in existence.");

        Entity id = available_entities.front();
        available_entities.pop();
        ++entity_count;

        return id;
    }

    void destroy_entity(Entity entity)
    {
        assert(entity < MAX_ENTITIES && "Entity out of range.");

        signatures[entity].reset();

        available_entities.push(entity);
        --entity_count;
    }

    void set_signature(Entity entity, Signature signature)
    {
        assert(entity < MAX_ENTITIES && "Entity out of range.");

        signatures[entity] = signature;
    }

    Signature get_signature(Entity entity)
    {
        assert(entity < MAX_ENTITIES && "Entity out of range.");

        return signatures[entity];
    }

private:
    std::queue<Entity> available_entities{};
    std::array<Signature, MAX_ENTITIES> signatures{};
    std::uint32_t entity_count = 0;
};

#endif // !ENTITY_MANAGER_HPP


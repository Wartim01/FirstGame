#include "Entity.h"
#include <iostream>

Entity::Entity(const std::string& name) : name(name) {}

Entity::~Entity() {}

void Entity::Update(float deltaTime) {
    // Mise à jour logique de l'entité
}

void Entity::Interact() {
    std::cout << name << " a été interagi.\n";
}

const std::string& Entity::GetName() const {
    return name;
}

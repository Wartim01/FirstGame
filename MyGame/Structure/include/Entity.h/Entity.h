#ifndef ENTITY_H
#define ENTITY_H

#include <string>

class Entity {
public:
    Entity(const std::string& name);
    virtual ~Entity();

    virtual void Update(float deltaTime);
    virtual void Interact();  // Interaction avec l'entité

    const std::string& GetName() const;

private:
    std::string name;
};

#endif // ENTITY_H

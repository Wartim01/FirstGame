#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

class EventManager {
public:
    EventManager();
    ~EventManager();

    void Update();  // Met à jour les événements
    void TriggerEvent(const std::string& eventName);  // Déclenche un événement spécifique

private:
    // Liste des événements
};

#endif // EVENT_MANAGER_H

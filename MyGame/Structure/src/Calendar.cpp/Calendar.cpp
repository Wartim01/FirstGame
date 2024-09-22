#include "Calendar.h"
#include <iostream>

Calendar::Calendar() : currentDay(1), currentMonth(6), currentYear(1940) {}

Calendar::~Calendar() {}

void Calendar::Update(float deltaTime) {
    // Gestion du temps, avancer les jours en fonction du deltaTime
}

void Calendar::AdvanceDay() {
    currentDay++;
    // Avancer le mois ou l'année si besoin
    std::cout << "Jour avancé: " << currentDay << "/" << currentMonth << "/" << currentYear << "\n";
}

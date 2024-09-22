#ifndef CALENDAR_H
#define CALENDAR_H

class Calendar {
public:
    Calendar();
    ~Calendar();

    void Update(float deltaTime);  // Avancer le temps
    void AdvanceDay();  // Passer au jour suivant

private:
    int currentDay;
    int currentMonth;
    int currentYear;
};

#endif // CALENDAR_H

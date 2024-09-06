#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Абстрактный класс Участник
class Participant 
{
protected:
    string name;
    int maxRunDistance;
    int maxJumpHeight;

public:
    Participant(const string& name, int maxRun, int maxJump)
        : name(name), maxRunDistance(maxRun), maxJumpHeight(maxJump) {}

    virtual void run(int distance) const = 0;
    virtual void jump(int height) const = 0;

    string getName() const { return name; }
    int getMaxRunDistance() const { return maxRunDistance; }
    int getMaxJumpHeight() const { return maxJumpHeight; }
};

// Реализация классов Участников
class Human : public Participant 
{
public:
    Human(const string& name, int maxRun, int maxJump)
        : Participant(name, maxRun, maxJump) {}

    void run(int distance) const override 
    {
        cout << "Человек " << name << " пробежал " << distance << " метров.\n";
    }

    void jump(int height) const override 
    {
        cout << "Человек " << name << " прыгнул на высоту " << height << " метров.\n";
    }
};

class Cat : public Participant 
{
public:
    Cat(const string& name, int maxRun, int maxJump)
        : Participant(name, maxRun, maxJump) {}

    void run(int distance) const override 
    {
        cout << "Кот " << name << " пробежал " << distance << " метров.\n";
    }

    void jump(int height) const override 
    {
        cout << "Кот " << name << " прыгнул на высоту " << height << " метров.\n";
    }
};

class Robot : public Participant 
{
public:
    Robot(const string& name, int maxRun, int maxJump)
        : Participant(name, maxRun, maxJump) {}

    void run(int distance) const override 
    {
        cout << "Робот " << name << " пробежал " << distance << " метров.\n";
    }

    void jump(int height) const override 
    {
        cout << "Робот " << name << " прыгнул на высоту " << height << " метров.\n";
    }
};

// Абстрактный класс Препятствие
class Obstacle 
{
public:
    virtual bool overcome(const Participant& participant) const = 0;
};

// Реализация классов Препятствий
class RunningTrack : public Obstacle 
{
private:
    int length;

public:
    RunningTrack(int length) : length(length) {}

    bool overcome(const Participant& participant) const override 
    {
        if (participant.getMaxRunDistance() >= length) 
        {
            participant.run(length);
            cout << "Участник [" << participant.getName() << "] прошел препятствие [Беговая дорожка] на дистанции [" << length << "] метров.\n";
            return true;
        }
        else 
        {
            cout << "Участник [" << participant.getName() << "] не прошел препятствие [Беговая дорожка] на дистанции [" << length << "] метров. Пройдено [" << participant.getMaxRunDistance() << "] метров.\n";
            return false;
        }
    }
};

class Wall : public Obstacle 
{
private:
    int height;

public:
    Wall(int height) : height(height) {}

    bool overcome(const Participant& participant) const override 
    {
        if (participant.getMaxJumpHeight() >= height) 
        {
            participant.jump(height);
            cout << "Участник [" << participant.getName() << "] прошел препятствие [Стена] на высоте [" << height << "] метров.\n";
            return true;
        }
        else 
        {
            cout << "Участник [" << participant.getName() << "] не прошел препятствие [Стена] на высоте [" << height << "] метров. Пройдено [" << participant.getMaxJumpHeight() << "] метров.\n";
            return false;
        }
    }
};

// Главная функция
int main() 
{

    setlocale(0, "ru");
    // Создание массивов участников и препятствий
    vector<Participant*> participants = 
    {
        new Human("Алексей", 1000, 2),
        new Cat("Мурчик", 500, 3),
        new Robot("R2D2", 1500, 1)
    };

    vector<Obstacle*> obstacles = 
    {
        new RunningTrack(400),
        new Wall(2),
        new RunningTrack(1000),
        new Wall(3)
    };

    // Проверка каждого участника на каждое препятствие
    for (auto participant : participants) 
    {
        bool passedAll = true;
        for (auto obstacle : obstacles) 
        {
            if (!obstacle->overcome(*participant)) 
            {
                passedAll = false;
                break;  // Участник выбывает, если не прошел препятствие
            }
        }
        if (!passedAll) 
        {
            cout << "Участник " << participant->getName() << " выбыл из участия в серии препятствий.\n";
        }
        cout << "-----------------------------\n";
    }

    // Очистка памяти
    for (auto participant : participants) 
    {
        delete participant;
    }
    for (auto obstacle : obstacles) 
    {
        delete obstacle;
    }

    return 0;
}

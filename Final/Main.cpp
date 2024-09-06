#include <iostream>
#include <vector>
#include <string>

using namespace std;

// ����������� ����� ��������
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

// ���������� ������� ����������
class Human : public Participant 
{
public:
    Human(const string& name, int maxRun, int maxJump)
        : Participant(name, maxRun, maxJump) {}

    void run(int distance) const override 
    {
        cout << "������� " << name << " �������� " << distance << " ������.\n";
    }

    void jump(int height) const override 
    {
        cout << "������� " << name << " ������� �� ������ " << height << " ������.\n";
    }
};

class Cat : public Participant 
{
public:
    Cat(const string& name, int maxRun, int maxJump)
        : Participant(name, maxRun, maxJump) {}

    void run(int distance) const override 
    {
        cout << "��� " << name << " �������� " << distance << " ������.\n";
    }

    void jump(int height) const override 
    {
        cout << "��� " << name << " ������� �� ������ " << height << " ������.\n";
    }
};

class Robot : public Participant 
{
public:
    Robot(const string& name, int maxRun, int maxJump)
        : Participant(name, maxRun, maxJump) {}

    void run(int distance) const override 
    {
        cout << "����� " << name << " �������� " << distance << " ������.\n";
    }

    void jump(int height) const override 
    {
        cout << "����� " << name << " ������� �� ������ " << height << " ������.\n";
    }
};

// ����������� ����� �����������
class Obstacle 
{
public:
    virtual bool overcome(const Participant& participant) const = 0;
};

// ���������� ������� �����������
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
            cout << "�������� [" << participant.getName() << "] ������ ����������� [������� �������] �� ��������� [" << length << "] ������.\n";
            return true;
        }
        else 
        {
            cout << "�������� [" << participant.getName() << "] �� ������ ����������� [������� �������] �� ��������� [" << length << "] ������. �������� [" << participant.getMaxRunDistance() << "] ������.\n";
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
            cout << "�������� [" << participant.getName() << "] ������ ����������� [�����] �� ������ [" << height << "] ������.\n";
            return true;
        }
        else 
        {
            cout << "�������� [" << participant.getName() << "] �� ������ ����������� [�����] �� ������ [" << height << "] ������. �������� [" << participant.getMaxJumpHeight() << "] ������.\n";
            return false;
        }
    }
};

// ������� �������
int main() 
{

    setlocale(0, "ru");
    // �������� �������� ���������� � �����������
    vector<Participant*> participants = 
    {
        new Human("�������", 1000, 2),
        new Cat("������", 500, 3),
        new Robot("R2D2", 1500, 1)
    };

    vector<Obstacle*> obstacles = 
    {
        new RunningTrack(400),
        new Wall(2),
        new RunningTrack(1000),
        new Wall(3)
    };

    // �������� ������� ��������� �� ������ �����������
    for (auto participant : participants) 
    {
        bool passedAll = true;
        for (auto obstacle : obstacles) 
        {
            if (!obstacle->overcome(*participant)) 
            {
                passedAll = false;
                break;  // �������� ��������, ���� �� ������ �����������
            }
        }
        if (!passedAll) 
        {
            cout << "�������� " << participant->getName() << " ����� �� ������� � ����� �����������.\n";
        }
        cout << "-----------------------------\n";
    }

    // ������� ������
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

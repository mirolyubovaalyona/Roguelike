#pragma once
#include <utility>
#include "Logic.h"



class GameObject {
protected:
    char type_of_obj;
    int hp;
    char sum;
    std::pair <int, int> coordinates; //x - first
public: 
    char GetType() {
        return type_of_obj;
    }
    int  GetHp() {
        return hp;
    }
    char GetSym() {
        return sum;
    }
    std::pair<int, int> GetPos() {
        return coordinates;
    }
    //virtual   ~GameObject() = 0;
};

class  Princess : public GameObject {
public:
    Princess(int x, int y) {
        hp = 100;
        sum = 'P';
        coordinates.first = x;
        coordinates.second = y;
        type_of_obj = 'O';
    }

};

class  Wall : public GameObject {
public:
    Wall(int x, int y) {
        hp = 100;
        sum = '#';
        coordinates.first = x;
        coordinates.second = y;
        type_of_obj = 'O';
    }

private:

};

class  AidKit : public GameObject {
public:
    AidKit(int x, int y) {
        hp = 100;
        sum = 'A';
        coordinates.first = x;
        coordinates.second = y;
        type_of_obj = 'O';
    }
};

class Bullet : public GameObject {
protected:
    eDirection bullet_dir;
    int speed;
    int next_coordinates;
    const  int max_next_coordinates = 100;
    int damage;

public:
    Bullet(int x, int y, eDirection d, char c) {
        bullet_dir = d;
        sum = c;
        hp = 100;
        coordinates.first = x;
        coordinates.second = y;
        next_coordinates = 0;
        damage = 4;
        speed = 100;
        type_of_obj = 'b';
    }

    void Go(int w, int h) {
        switch (bullet_dir) {
        case LEFT:
            if (coordinates.first > 0) {
                next_coordinates += speed;
                if (next_coordinates >= max_next_coordinates) {
                    coordinates.first -= 1;
                    next_coordinates = next_coordinates % max_next_coordinates;
                }
            }
            if (coordinates.first == 0) {
            }
            break;
        case RIGHT:
            if (coordinates.first < w-1) {
                next_coordinates += speed;
                if (next_coordinates >= max_next_coordinates) {
                    coordinates.first += 1;
                    next_coordinates = next_coordinates % max_next_coordinates;
                }
            }
            if (coordinates.first == w-1) {
            }
            break;
        case UP:
            if (coordinates.second > 0) {
                next_coordinates += speed;
                if (next_coordinates >= max_next_coordinates) {
                    coordinates.second -= 1;
                    next_coordinates = next_coordinates % max_next_coordinates;
                }
            }
            if (coordinates.second == 0) {
            }
            break;
        case DOWN:
            if (coordinates.second < h-1) {
                next_coordinates += speed;
                if (next_coordinates >= max_next_coordinates) {
                    coordinates.second += 1;
                    next_coordinates = next_coordinates % max_next_coordinates;
                }
            }
            if (coordinates.second == h-1) {
            }
            break;
        }
        //monster_dir = RandDir();
    }

    bool Collide(GameObject m) {
        switch (bullet_dir) {
        case LEFT:
            if (m.GetPos().first == GetPos().first - 1 & m.GetPos().second == GetPos().second) {
                return true;
            }
            break;
        case RIGHT:
            if (m.GetPos().first == GetPos().first + 1 & m.GetPos().second == GetPos().second) {
                return true;
            }
            break;
        case UP:
            if (m.GetPos().second == GetPos().second - 1 & m.GetPos().first == GetPos().first) {
                return true;
            }
            break;
        case DOWN:
            if (m.GetPos().second == GetPos().second + 1 & m.GetPos().first == GetPos().first) {
                return true;
            }
            break;
        }
        return false;
    }

    Bullet& operator=(const Bullet& rhs) {
        hp = rhs.hp;
        sum = rhs.sum;
        coordinates.first = rhs.coordinates.first;
        coordinates.second = rhs.coordinates.second;
        next_coordinates = rhs.next_coordinates;
        damage = rhs.damage;
        bullet_dir = rhs.bullet_dir;
        speed = rhs.speed;
        type_of_obj = rhs.type_of_obj;
        return *this;
    }

    int GetDamage() {
        return damage;
    }
};

class Character : public GameObject { 
protected:
    int damage;
    int max_hp;

public:
    bool TakeDamage(int d) {
        hp -= d;
        if (hp > 0) {
            return true;
        }
        return false;
    }

    int GetDamage() {
        return damage;
    };

    int GetMaxHp() {
        return max_hp;
    };
};

class  Knight : public Character {
protected:
    eDirection previous_dir;
    int mana;
    int max_mana;



    bool Collide(GameObject m, eDirection m_dir) {
        switch (m_dir) {
        case LEFT:
            if (m.GetPos().first == coordinates.first - 1 & m.GetPos().second == coordinates.second) {
                return true;
            }
            break;
        case RIGHT:
            if (m.GetPos().first == coordinates.first + 1 & m.GetPos().second == coordinates.second) {
                return true;
            }
            break;
        case UP:
            if (m.GetPos().second == coordinates.second - 1 & m.GetPos().first == coordinates.first) {
                return true;
            }
            break;
        case DOWN:
            if (m.GetPos().second == coordinates.second + 1 & m.GetPos().first == coordinates.first) {
                return true;
            }
            break;
        }
        return false;
    }

public:

    Knight() {
        previous_dir = UP;
        hp = 100;
        sum = 'K';
        damage = 5;
        mana = 100;
        max_mana = 100;
        max_hp = hp;
        type_of_obj = 'K';
    }

   

    void RL(int x, int y) {
        coordinates.first = x;
        coordinates.second = y;
    }

    void Go(std::vector<GameObject> m, eDirection d, int  w, int  h) {
        bool c = false; 
        for (int i = 0; i < m.size(); i++) {
            if (Collide(m[i], d)) c = true;
        }
        switch (d) {
        case LEFT:
            if (coordinates.first > 0 & !c)
                coordinates.first--;
            previous_dir = LEFT;
            return;
        case RIGHT:
            if(coordinates.first < w - 1 & !c)
                coordinates.first++;
            previous_dir = RIGHT;
            return;
        case UP:
            if (coordinates.second > 0 & !c)
                coordinates.second--;
            previous_dir = UP;
            return;
        case DOWN:
            if (coordinates.second < h - 1 & !c)
                coordinates.second++;
            previous_dir = DOWN;
            return;
        }
        return;
    }

    eDirection GetPreviousDir(){
        return previous_dir;
    }

    int GetMana() {
        return mana;
    }
    int GetMaxMana() {
        return max_mana;
    }

    Bullet  Shoot() {
        mana -= 10;
        Bullet b(coordinates.first, coordinates.second, previous_dir, '+');
        return b;
    }

    bool MCollide(GameObject m) {
        if (m.GetPos().second == coordinates.second  & m.GetPos().first == coordinates.first) {
            return true;
        }
        return false;
    }

    void UpHp(int x) {
        hp += x;
        if (hp > 100) {
            hp = 100;
       }
    }

    void UpMana(int x) {
        mana += x;
        mana -= mana % max_mana;
    }
    
};


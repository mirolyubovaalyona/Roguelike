#pragma once
#include <cstdlib>
#include "GameObject.h"
#include "Logic.h"

class  Monster : public Character {
protected:
    eDirection monster_dir;
    int speed;
    int next_coordinates;
    const  int max_next_coordinates = 100;


public:
    eDirection RandDir() {
        int k = 1 + rand() % 4;
        switch (k) {
        case 1:
            return LEFT;
        case 2:
            return UP;
        case 3:
            return RIGHT;
        case 4:
            return DOWN;
        }
    }

    void Go(int w, int h) {
        switch (monster_dir) {
        case LEFT: 
            if (coordinates.first > 0) {
                next_coordinates += speed;
                if (next_coordinates >= max_next_coordinates) {
                    coordinates.first -= 1;
                    next_coordinates = next_coordinates % max_next_coordinates;
                }
            }
            if (coordinates.first == 0) {
                monster_dir = RandDir();
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
                monster_dir = RandDir();
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
                monster_dir = RandDir();
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
                monster_dir = RandDir();
            }
            break;
        }
        //monster_dir = RandDir();
    }


    bool Collide(GameObject m) {
        switch (monster_dir) {
        case LEFT:
            if (m.GetPos().first == GetPos().first - 1 & m.GetPos().second == GetPos().second) {
                monster_dir = RandDir();
                return true;
            }
            break;
        case RIGHT:
            if (m.GetPos().first == GetPos().first + 1 & m.GetPos().second == GetPos().second) {
                monster_dir = RandDir();
                return true;
            }
            break;
        case UP:
            if (m.GetPos().second == GetPos().second - 1 & m.GetPos().first == GetPos().first) {
                monster_dir = RandDir();
                return true;
            }
            break;
        case DOWN:
            if (m.GetPos().second == GetPos().second + 1 & m.GetPos().first == GetPos().first) {
                monster_dir = RandDir();
                return true;
            }
            break;
        }
        return false;
    }

    Monster& operator=(const Monster& rhs) {
        hp = rhs.hp;
        sum = rhs.sum;
        coordinates.first = rhs.coordinates.first;
        coordinates.second = rhs.coordinates.second;
        next_coordinates = rhs.next_coordinates;
        damage = rhs.damage;
        max_hp = rhs.max_hp;
        monster_dir = rhs.monster_dir;
        speed = rhs.speed;
        type_of_obj = rhs.type_of_obj;
        return *this;
    }

    Bullet  Shoot() {
        Bullet b(coordinates.first, coordinates.second, monster_dir, 'o');
        return b;
    }

};

class  Zombie : public Monster {
public:
    Zombie(int x, int y) {
        hp = 10;
        sum = 'Z';
        coordinates.first = x;
        coordinates.second = y;
        next_coordinates = 0;
        damage = 3;
        max_hp = 100;
        monster_dir = RandDir();
        speed = 100;
        type_of_obj = 'M';
    }
};

class  Dragon : public Monster {
public:
    Dragon(int x, int y) {
        hp = 50;
        sum = 'D';
        coordinates.first = x;
        coordinates.second = y;
        next_coordinates = 0;
        damage = 4;
        max_hp = 500;
        monster_dir = RandDir();
        speed = 10;
        type_of_obj = 'M';
    }
};
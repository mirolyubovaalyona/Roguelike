#pragma once
#include <fstream>
#include <conio.h>
#include <utility>
#include <vector>
#include <string>
#include "GameObject.h"
#include "Monsters.h"
#include "Logic.h"
#include "MainMenu.h"
#include <cstdlib>

using namespace std;

class Map {
public:
    std::pair <int, int> size;
    std::vector<GameObject> objects_on_map;
    std::vector<GameObject> good_objects_on_map;
    std::vector<Monster> monsres_on_map;
    std::vector<Bullet> bullets_on_map;
    int score;
    int  fog_of_war = 6;
    int width, height;
    Knight K;
    MainMenue m;
    eDirection dir;
    int time;

    bool gameOver;

    Map() {
    }

    Knight NewMap() {
        m.Start();
        string arr = "";
        string s = "";
        string w = "";
        string h = "";
        std::ifstream in("MainMap.txt");
        if (in.is_open()) {
            getline(in, w);
            getline(in, h);
            width = atoi(w.c_str());
            height = atoi(h.c_str());
            for (int i = 0; i < height; i++) {
                getline(in, s);
                arr += s;
            }
        }
       // system("cls");
        //cout << arr;
        in.close();
        //exit(1);
        time = 0;
        gameOver = false;
        dir = STOP;
        score = 0;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (arr[i*width+j] != '.') {
                    if (arr[i * width + j] == '#') {
                        Wall c(j, i);
                        objects_on_map.push_back(c);
                    }
                    if (arr[i * width + j] == 'Z') {
                        Zombie c(j, i);
                        monsres_on_map.push_back(c);
                    }
                    if (arr[i * width + j] == 'D') {
                        Dragon c(j, i);
                        monsres_on_map.push_back(c);
                    }
                    if (arr[i * width + j] == 'P') {
                        Princess c(j, i);
                        good_objects_on_map.push_back(c);
                    }
                    if (arr[i * width + j] == 'A') {
                        AidKit c(j, i);
                        good_objects_on_map.push_back(c);
                    }
                    if (arr[i * width + j] == 'K') {
                        K.RL(j, i);
                    }
                }
            }
        }

        return K;
    };

    std::pair <int, int> GetSize() {
        return size;
    };

    std::vector<GameObject> GetObjectsOnMap() {
        return objects_on_map;
    };

    std::vector<Monster> GetMostersOnMap() {
        return monsres_on_map;
    };
    std::vector<GameObject> GetGoodObjectsOnMap() {
        return good_objects_on_map;
    };
    std::vector<Bullet> GetBulletsOnMap() {
        return bullets_on_map;
    };


private:

};

void  Draw(Map map) {
    system("cls");
    char** a;
    a = new char* [map.height];
    for (int i = 0; i < map.height; i++) {
        a[i] = new char[map.width];
        for (int j = 0; j < map.width; j++) {
            a[i][j] = '.';
        }
    }
    string buff = "";
    for (int i = 0; i < map.GetObjectsOnMap().size(); i++) {
        a[map.objects_on_map[i].GetPos().second][map.objects_on_map[i].GetPos().first] = map.objects_on_map[i].GetSym();
    }
    for (int i = 0; i < map.GetGoodObjectsOnMap().size(); i++) {
        a[map.good_objects_on_map[i].GetPos().second][map.good_objects_on_map[i].GetPos().first] = map.good_objects_on_map[i].GetSym();
    }
    for (int i = 0; i < map.GetMostersOnMap().size(); i++) {
        a[map.monsres_on_map[i].GetPos().second][map.monsres_on_map[i].GetPos().first] = map.monsres_on_map[i].GetSym();
    }
    for (int i = 0; i < map.GetBulletsOnMap().size(); i++) {
        a[map.bullets_on_map[i].GetPos().second][map.bullets_on_map[i].GetPos().first] = map.bullets_on_map[i].GetSym();
    }
    a[map.K.GetPos().second][map.K.GetPos().first] = map.K.GetSym();
    for (int i = 0; i < map.height; i++) {
        for (int j = 0; j < map.width; j++) {
            if ((j < map.K.GetPos().first - map.fog_of_war || j > map.K.GetPos().first + map.fog_of_war || i < map.K.GetPos().second - map.fog_of_war || i > map.K.GetPos().second + map.fog_of_war)) a[i][j] = '~';
            buff += a[i][j];
        }
        buff += "\n";
    }
    buff += "hp: " + to_string(map.K.GetHp()) + " | " + to_string(map.K.GetMaxHp()) + "    mana: " + to_string(map.K.GetMana()) + " | " + to_string(map.K.GetMaxMana()) + "\n";
    buff += "score : " + to_string(map.score) + "\n";
    cout << buff;
}

Map  Input(Map map) {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            map.dir = LEFT;
            break;
        case 'w':
            map.dir = UP;
            break;
        case 'd':
            map.dir = RIGHT;
            break;
        case 's':
            map.dir = DOWN;
            break;
        case 'e':
            map.dir = SHOOT;
            break;
        case 27:
            map.gameOver = true;
            break;
        }
    }
    return map;

}

Map Logic(Map map) {
    map.time++;
    std::vector<int> m;
    std::vector<int> b;
    for (int i = 0; i < map.GetMostersOnMap().size(); i++) {
        for (int j = 0; j < map.GetBulletsOnMap().size(); j++) {
            if (map.monsres_on_map[i].Collide(map.bullets_on_map[j]) && map.GetBulletsOnMap()[j].GetSym() == '+') {
                map.monsres_on_map[i].TakeDamage(map.bullets_on_map[j].GetDamage());
                if (map.monsres_on_map[i].GetHp() <= 0) {
                    m.push_back(i);
                }
                b.push_back(j);
            }
        }
    }
    for (int i = m.size() - 1; 0 <= i; i--) {
        map.monsres_on_map.erase(map.monsres_on_map.begin() + m[i]);
        map.score++;
    }
    for (int i = b.size() - 1; 0 <= i; i--) {
        map.bullets_on_map.erase(map.bullets_on_map.begin() + b[i]);
    }

    map.K.Go(map.GetObjectsOnMap(), map.dir, map.width, map.height);
    if (map.dir == SHOOT) {
        {
            if (map.K.GetMana() >= 10) {
                map.bullets_on_map.push_back(map.K.Shoot());
            }
        }
    }
    for (int i = map.good_objects_on_map.size() - 1; 0 <= i; i--) {
        if (map.good_objects_on_map[i].GetPos().first == map.K.GetPos().first & map.good_objects_on_map[i].GetPos().second == map.K.GetPos().second & map.good_objects_on_map[i].GetSym() == 'A') {
            map.K.UpHp(10);
            map.good_objects_on_map.erase(map.good_objects_on_map.begin() + i);
        }
        if (map.good_objects_on_map[i].GetPos().first == map.K.GetPos().first & map.good_objects_on_map[i].GetPos().second == map.K.GetPos().second & map.good_objects_on_map[i].GetSym() == 'P') {
            map.m.ToWin(map.score);
            exit(1);
        }
    }

    for (int i = 0; i < map.GetMostersOnMap().size(); i++) {
        if (map.K.MCollide(map.monsres_on_map[i])) {
            map.K.TakeDamage(map.monsres_on_map[i].GetDamage());
            if (map.K.GetHp() <= 0) {
                map.m.ToLose(map.score);
                exit(1);
            }
            map.monsres_on_map[i].TakeDamage(map.K.GetDamage());
            if (map.monsres_on_map[i].GetHp() <= 0) {
                map.monsres_on_map.erase(map.monsres_on_map.begin() + i);
                map.score++;
            }
        }
    }


    map.dir = STOP;
    bool c = false;


    b.clear();
    for (int i = 0; i < map.GetBulletsOnMap().size(); i++) {
        for (int j = 0; j < map.GetObjectsOnMap().size(); j++) {
            if (map.bullets_on_map[i].Collide(map.objects_on_map[j])) {
                b.push_back(i);
            }
        }
        if (map.bullets_on_map[i].GetPos().first == map.K.GetPos().first & map.bullets_on_map[i].GetPos().second == map.K.GetPos().second & map.bullets_on_map[i].GetSym() == 'o') {
            map.K.TakeDamage(map.bullets_on_map[i].GetDamage());
            if (map.K.GetHp() <= 0) {
                map.m.ToLose(map.score);
                exit(1);
            }
            b.push_back(i);
        }
    }
    for (int i = b.size() - 1; 0 <= i; i--) {
        map.bullets_on_map.erase(map.bullets_on_map.begin() + b[i]);
    }


    for (int i = 0; i < map.GetMostersOnMap().size(); i++) {
        for (int j = 0; j < map.GetMostersOnMap().size(); j++) {
            if (map.monsres_on_map[i].Collide(map.monsres_on_map[j])) {
                c = true;
            }
        }
        for (int j = 0; j < map.GetObjectsOnMap().size(); j++) {
            if (map.monsres_on_map[i].Collide(map.objects_on_map[j])) {
                c = true;
            }
        }
        if (!c) {
            if (map.time % 15 == 0) {
                map.bullets_on_map.push_back(map.monsres_on_map[i].Shoot());
                map.K.UpMana(10);
            }
            map.monsres_on_map[i].Go(map.width, map.height);
        }
    }

    for (int i = map.GetBulletsOnMap().size() - 1; 0 <= i; i--) {
        map.bullets_on_map[i].Go(map.width, map.height);
    }
    return map;
}

void GameLoop(Map map) {
    while (!map.gameOver) {
        Draw(map);
        map = Input(map);
        map = Logic(map);
    }

    if (!map.m.Esc(map.score)) {
        map.gameOver = false;
        GameLoop(map);
    }
}


void Setup(Map map) {
    map.NewMap();


    GameLoop(map);
    //system("mode con cols=30 lines=25");

}
//
// Created by Subidubi32 on 2019. 12. 13..
//
#include <iostream>
#include <cstddef>
#include "Snake.h"
#include <windows.h>

Snake::Coordinates::Coordinates(short x, short y){
    this->x = x;
    this->y = y;
}

Snake::Snake() {
    map = new char*[MAP_HEIGHT];
    for(int i = 0; i < MAP_HEIGHT; ++i)
        map[i] = new char[MAP_WIDTH];
    snake = new Coordinates[MAP_HEIGHT*MAP_WIDTH];
    for(int i = 0; i < MAP_HEIGHT*MAP_WIDTH; ++i){
        snake[i] = Coordinates(-1, -1);
    }
    died = false;
    snake_length = 0;
    food = Coordinates(rand() % (MAP_HEIGHT - 2) + 1, rand() % (MAP_WIDTH - 2) + 1);
}

Snake::~Snake() {
    for(size_t i = 0; i < MAP_HEIGHT; ++i)
        delete[] map[i];
    delete[] map;
    delete[] snake;
}

void Snake::set_start() {
    for(size_t i = 0; i < MAP_HEIGHT; ++i) {
        map[i][0] = '|';
        map[i][MAP_WIDTH-1] = '|';
    }
    for(size_t j = 1; j < MAP_WIDTH-1; ++j) {
        map[0][j] = '-';
        map[MAP_HEIGHT-1][j] = '-';
    }
    for(size_t i = 1; i < MAP_HEIGHT-1; ++i){
        for(size_t j = 1; j < MAP_WIDTH-1; ++j){
            map[i][j] = ' ';
        }
    }
    this->snake_length = INIT_SNAKE_LENGTH;
    for (int i = 0; i < snake_length; ++i){
        setSnakeSegment(i ,Coordinates(MAP_HEIGHT/2,MAP_WIDTH/2-i));
    }
    for (int i = 0; i < snake_length; ++i){
        setSnakeSegment(i ,Coordinates(MAP_HEIGHT/2,MAP_WIDTH/2-i));
        if (i == 0)
            map[getSnakeSegment(i).x][getSnakeSegment(i).y] = 219;
        else
            map[getSnakeSegment(i).x][getSnakeSegment(i).y] = 176;
    }
}

void Snake::go(){
    Coordinates last;
    Coordinates currentTemp;
    for (int i = 0; i < snake_length; ++i){
        if (i == 0) {
            last = Coordinates(getSnakeSegment(i).x, getSnakeSegment(i).y);
            if (getSnakeSegment(i).x < getSnakeSegment(i + 1).x) {
                checkDeath(snake[i].x - 1, snake[i].y);
                setSnakeSegment(i, Coordinates(getSnakeSegment(i).x - 1, getSnakeSegment(i).y));
            }
            else if (getSnakeSegment(i).x > getSnakeSegment(i + 1).x){
                checkDeath(snake[i].x + 1, snake[i].y);
                setSnakeSegment(i, Coordinates(getSnakeSegment(i).x + 1, getSnakeSegment(i).y));
            }
            else if (getSnakeSegment(i).y < getSnakeSegment(i + 1).y) {
                checkDeath(snake[i].x, snake[i].y - 1);
                setSnakeSegment(i, Coordinates(getSnakeSegment(i).x, getSnakeSegment(i).y - 1));
            }
            else if (getSnakeSegment(i).y > getSnakeSegment(i + 1).y) {
                checkDeath(snake[i].x, snake[i].y + 1);
                setSnakeSegment(i, Coordinates(getSnakeSegment(i).x, getSnakeSegment(i).y + 1));
            }
        } else if (i > 0) {
            currentTemp =  Coordinates(getSnakeSegment(i).x, getSnakeSegment(i).y);
            setSnakeSegment(i, Coordinates(last.x, last.y));
            last = currentTemp;
        }
    }
}

void Snake::go(char dir){
    Coordinates last;
    Coordinates currentTemp;
    for (int i = 0; i < snake_length; ++i){
        if (i == 0) {
            last = Coordinates(getSnakeSegment(i).x, getSnakeSegment(i).y);
            switch(dir) {
                case VK_UP:
                    if (getSnakeSegment(i).x > getSnakeSegment(i + 1).x)
                        Snake::go();
                    else {
                        checkDeath(snake[i].x - 1, snake[i].y);
                        setSnakeSegment(i, Coordinates(getSnakeSegment(i).x - 1, getSnakeSegment(i).y));
                    }
                    break;
                case VK_DOWN:
                    if (getSnakeSegment(i).x < getSnakeSegment(i + 1).x)
                        Snake::go();
                    else {
                        checkDeath(snake[i].x + 1, snake[i].y);
                        setSnakeSegment(i, Coordinates(getSnakeSegment(i).x + 1, getSnakeSegment(i).y));
                    }
                    break;
                case VK_LEFT:
                    if (getSnakeSegment(i).y > getSnakeSegment(i + 1).y)
                        Snake::go();
                    else {
                        checkDeath(snake[i].x, snake[i].y - 1);
                        setSnakeSegment(i, Coordinates(getSnakeSegment(i).x, getSnakeSegment(i).y - 1));
                    }
                    break;
                case VK_RIGHT:
                    if (getSnakeSegment(i).y < getSnakeSegment(i + 1).y)
                        Snake::go();
                    else {
                        checkDeath(snake[i].x, snake[i].y + 1);
                        setSnakeSegment(i, Coordinates(getSnakeSegment(i).x, getSnakeSegment(i).y + 1));
                    }
                    break;
            }
        } else if (i > 0) {
            currentTemp =  Coordinates(getSnakeSegment(i).x, getSnakeSegment(i).y);
            setSnakeSegment(i, Coordinates(last.x, last.y));
            last = currentTemp;
        }
    }
}

char** Snake::get_map() const{
    return this->map;
}

Snake::Coordinates Snake::getSnakeSegment(int segment) {
    return snake[segment];
}

void Snake::setSnakeSegment(int segment, Coordinates newCoord) {
    snake[segment] = newCoord;
}

void Snake::reDraw() {
    for(size_t i = 0; i < MAP_HEIGHT; ++i) {
        map[i][0] = '|';
        map[i][MAP_WIDTH-1] = '|';
    }
    for(size_t j = 1; j < MAP_WIDTH-1; ++j) {
        map[0][j] = '-';
        map[MAP_HEIGHT-1][j] = '-';
    }
    for(size_t i = 1; i < MAP_HEIGHT-1; ++i){
        for(size_t j = 1; j < MAP_WIDTH-1; ++j){
            map[i][j] = ' ';
        }
    }
    map[food.x][food.y] = 248;
    if (snake[0].x == food.x && snake[0].y == food.y){
        bool badPos = true;
        while (badPos) {
            food.x = rand() % (MAP_HEIGHT - 2) + 1;
            food.y = rand() % (MAP_WIDTH - 2) + 1;
            for (int i = 0; i < snake_length; ++i) {
                if (snake[i].x != food.x || snake[i].y != food.y)
                    badPos = false;
            }
        }
        snake_length++;
    }
    for (size_t i = 0; i < MAP_HEIGHT*MAP_WIDTH; ++i) {
        if (snake[i].x == -1 || snake[i].y == -1)
            break;
        if (i == 0)
            map[snake[i].x][snake[i].y] = 219;
        else
            map[snake[i].x][snake[i].y] = 176;
    }
}

void Snake::deDraw(int n) {
    for(size_t i = 0; i < MAP_HEIGHT; ++i){
        for(size_t j = 0; j < MAP_WIDTH; ++j){
            map[i][j] = ' ';
        }
    }
}

unsigned Snake::getSnakeLength(){
    return snake_length;
}

void Snake::checkDeath(int x, int y){
    if(map[x][y] != ' ' && map[x][y] != (char)248)
        died = true;
}

bool Snake::isDead() {
    return died;
}

std::ostream& operator<<(std::ostream& o, const Snake& snake){
    for(size_t i = 0; i < MAP_HEIGHT; ++i){
        for(size_t j = 0; j < MAP_WIDTH; ++j){
            o << snake.get_map()[i][j];
        }
        o << "\n";
    }
    return o;
}



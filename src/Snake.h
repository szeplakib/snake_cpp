//
// Created by Subidubi32 on 2019. 12. 13..
//
#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

static constexpr size_t MAP_WIDTH = 40;
static constexpr size_t MAP_HEIGHT = 25;
static constexpr size_t INIT_SNAKE_LENGTH = 3;

class Snake {
public:
    struct Coordinates{
        short x;
        short y;
        Coordinates() = default;
        Coordinates(short x, short y);
    };
private:
    char** map;
    unsigned snake_length;
    bool died;
    Coordinates* snake;
    Coordinates food;
public:
    Snake();
    ~Snake();
    void set_start();
    char** get_map() const;
    void go();
    void go(char);
    friend std::ostream& operator<<(std::ostream& o, const Snake& snake);
    Coordinates getSnakeSegment(int segment);
    void setSnakeSegment(int segment, Coordinates newCoord);
    unsigned getSnakeLength();
    void reDraw();
    void deDraw(int);
    void checkDeath(int, int);
    bool isDead();
};


#endif //SNAKE_SNAKE_H

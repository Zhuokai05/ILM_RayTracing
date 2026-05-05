#ifndef _FILM_H
#define _FILM_H
#include "Color.h"
#include <fstream>
#include <iostream>
#include <utility>

class Film {
public:

    Film(int x, int y, std::ofstream output) : _tamX(x), _tamY(y), _aspectRatio(1.0f*_tamX / _tamY), _out(std::move(output)) {}


    void AddPixel(Color color);

    int GetTamX() const { return _tamX; }
    int GetTamY() const { return _tamY; }
    float GetAspectRatio() const { return (float)_tamX / _tamY; }

private:

    int _tamX;
    int _tamY;

    std::ofstream _out;

    float _aspectRatio;

    bool missingHeader = true;
};

#endif

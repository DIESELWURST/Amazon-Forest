#ifndef MOBS_HPP
#define MOBS_HPP

class Mobs { // razred iz katerega bomo izpeljevali razrede
protected:
    int x, y; // te dve vrednosti smatramo, kot poziciji v koordinatenem sistemu
    int radius;
    int movementSpeed;
public:
    int getX() const { return x; }
    int getY() const { return y; }
    int getRadius() const { return radius; }
    int getSpeed() const { return movementSpeed; }
    virtual bool Borders(int minX, int maxX, int minY, int maxY);
};

#endif // MOBS_HPP

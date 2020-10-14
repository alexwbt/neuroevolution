#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>

#include "neuron.h"

constexpr double SIZE = 600.0;

double mapX(double x)
{
    return (x + 1.0f) * SIZE / 2.0;
}

double mapY(double y) {
    return (-y + 1.0f) * SIZE / 2.0;
}

struct Point
{
    sf::CircleShape shape;
    double x, y;
    bool label;
    Point(double x, double y, bool label) : shape(3, 6), x(x), y(y), label(label)
    {
        shape.setPosition(mapX(x), mapY(y));
        shape.setFillColor(label ? sf::Color::Red : sf::Color::Blue);
    }
};

int main()
{
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(SIZE, SIZE), "Neuralevolution");

    // Single layer perceptrons are only capable of learning linearly separable patterns.
    Neuron neuron(2);
    std::vector<Point*> points;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::MouseButtonPressed:
                points.push_back(new Point(
                    (event.mouseButton.x - SIZE / 2.0) / (SIZE / 2.0),
                    -(event.mouseButton.y - SIZE / 2.0) / (SIZE / 2.0),
                    event.mouseButton.button == 0
                ));
                break;
            case sf::Event::Closed:
                window.close(); 
                break;
            }
        }

        window.clear();

        for (Point* pt : points)
        {
            double input[] = { pt->x, pt->y };
            neuron.train(input, pt->label ? 1.0 : -1.0, 0.5);
            window.draw(pt->shape);
        }

        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(mapX(-1.0), mapY(neuron.getLineY(-1.0)))),
            sf::Vertex(sf::Vector2f(mapX(1.0), mapY(neuron.getLineY(1.0))))
        };
        window.draw(line, 2, sf::Lines);
        window.display();
    }


    for (Point* pt : points)
        delete pt;

    return 0;
}

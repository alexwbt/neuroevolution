#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>

#include "neuron.h"

float lineFunction(float x)
{
    return 0.3 * x;
}

float map(float x)
{
    return (x + 1.0f) * 600.0f;
}

struct Point
{
    sf::CircleShape shape;
    Point(float x, float y, float label) : shape(3, 6)
    {
        shape.setPosition(map(x), map(y));
        shape.setFillColor(label > 0 ? sf::Color::Red : sf::Color::Blue);
    }
};

int main()
{
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(600, 600), "Neuralevolution");

    // Single layer perceptrons are only capable of learning linearly separable patterns.
    Neuron neuron(2);
    std::vector<Point*> points;
    for (int i = 0; i < 1000; i++)
    {
        float x = (rand() % 200) / 200.0f - 1.0f;
        float y = (rand() % 200) / 200.0f - 1.0f;
        float inputs[] = { x, y };
        neuron.train(inputs, y < lineFunction(x) ? -1 : 1, 0.1f);
    }
    for (int i = 0; i < 500; i++)
    {
        float x = (rand() % 200) / 200.0f - 1.0f;
        float y = (rand() % 200) / 200.0f - 1.0f;
        float inputs[] = { x, y };
        points.push_back(new Point(x, y, neuron.activate(inputs)));
    }

    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(map(-1), map(lineFunction(-1)))),
        sf::Vertex(sf::Vector2f(map(1), map(lineFunction(1))))
    };

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        for (Point* pt : points)
            window.draw(pt->shape);

        window.draw(line, 2, sf::Lines);
        window.display();
    }


    for (Point* pt : points)
        delete pt;

    return 0;
}

#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>

#include "neuron.h"

constexpr float SIZE = 600.0f;

float mapX(float x)
{
    return (x + 1.0f) * SIZE / 2.0f;
}

float mapY(float y) {
    return (-y + 1.0f) * SIZE / 2.0f;
}

struct Point
{
    sf::CircleShape shape;
    float x, y;
    Point(float x, float y) : shape(3, 6), x(x), y(y)
    {
        shape.setPosition(mapX(x), mapY(y));
        shape.setFillColor(sf::Color::White);
    }
};

int main()
{
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(SIZE, SIZE), "Neuralevolution");

    // Single layer perceptrons are only capable of learning linearly separable patterns.
    Neuron neuron(1);
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
                    (event.mouseButton.x - SIZE / 2.0f) / (SIZE / 2.0f),
                    -(event.mouseButton.y - SIZE / 2.0f) / (SIZE / 2.0f)
                ));
                std::cout << points[points.size() - 1]->x << ' ' << points[points.size() - 1]->y << std::endl;
                break;
            case sf::Event::Closed:
                window.close(); 
                break;
            }
        }

        window.clear();

        for (Point* pt : points)
        {
            float input[] = { pt->x };
            neuron.train(input, pt->y, 0.001f);
            window.draw(pt->shape);
        }

        float input1[] = { -1.0f };
        float input2[] = { 1.0f };
        float y1 = neuron.activate(input1);
        float y2 = neuron.activate(input2);
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(mapX(input1[0]), mapY(y1))),
            sf::Vertex(sf::Vector2f(mapX(input2[0]), mapY(y2)))
        };
        window.draw(line, 2, sf::Lines);
        window.display();
    }


    for (Point* pt : points)
        delete pt;

    return 0;
}

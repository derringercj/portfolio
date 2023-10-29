/*A project completed Fall 2023 that demonstrates an orbital gravity simulator in C++. This program uses Simple Fast Multimedia Library to create the 
window functionality and true-to-life math and physics to accurately simulate the orbit of thousands of particles around two gravity sources.*/
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <cmath>
#include <vector>


class GravitySource {

    //Two element vector that stores the x and y value of the Gravity Source Position
    sf::Vector2f pos;
    float strength;
    //Displaying the gravity source as a circle
    sf::CircleShape s;


public:
    //Grav Source Constructor
    GravitySource(float pos_x, float pos_y, float strength) {
        //Assigning member variables with passed in values
        pos.x = pos_x;
        pos.y = pos_y;
        this->strength = strength;

        //Defining attributes of the circle shape like color, size, and position
        s.setPosition(pos);
        s.setFillColor(sf::Color::White);
        s.setRadius(10);
    }

    //Function to draw the object in the window
    void render(sf::RenderWindow& wind) {
        wind.draw(s);
    }

    //Getter functions for position and strength
    sf::Vector2f get_pos() {
        return pos;
    }
    float get_strength() {
        return strength;
    }
};

class Particle {

    //Two element vectors that hold x and y values of position and velocity
    sf::Vector2f pos;
    sf::Vector2f vel;

    //Displaying the circle particle that orbits the gravity source
    sf::CircleShape s;

public:
    //Particle constructor that sets initial position and velocity values
    Particle(float pos_x, float pos_y, float vel_x, float vel_y) {
        pos.x = pos_x;
        pos.y = pos_y;

        vel.x = vel_x;
        vel.y = vel_y;

        //Defining the attributes of the particle such as size and color
        s.setPosition(pos);
        s.setFillColor(sf::Color::White);
        s.setRadius(5);
    }

    void set_color(sf::Color col) {
        s.setFillColor(col);
    }

    //Drawing the circle particle on the window
    void render(sf::RenderWindow& wind) {
        s.setPosition(pos);
        wind.draw(s);
    }

    //Function that continually updates the physics of the particle
    void update_physics(GravitySource& s) {
        //Finding x and y distance of the particle from the Grav Source
        float distance_x = s.get_pos().x - pos.x;
        float distance_y = s.get_pos().y - pos.y;

        //Using pythagorean theorem to find straight distance
        float distance = sqrt(distance_x * distance_x + distance_y * distance_y);

        //Performing vector normalization
        float inverse_distance = 1.f / distance;
        float normalized_x = inverse_distance * distance_x;
        float nomrlaized_y = inverse_distance * distance_y;

        //Calculating gravity drop off based on the inverse square law
        float inverse_square_dropoff = inverse_distance * inverse_distance;

        //Calculating given acceleration of particle based on distance, strength, and dropoff
        float acceleration_x = normalized_x * s.get_strength() * inverse_square_dropoff;
        float acceleration_y = nomrlaized_y * s.get_strength() * inverse_square_dropoff;

        //Updating velocity based on acceleration
        vel.x += acceleration_x;
        vel.y += acceleration_y;

        //Updating position based on velocity
        pos.x += vel.x;
        pos.y += vel.y;
    }
};

sf::Color map_val_to_color(float value) { //value is 0-1
    if (value < 0.0f) {
        value = 0;
    }
    if (value > 1.0f) {
        value = 1;
    }

    int r = 0, g = 0, b = 0;

    //0 - 0.5 b to g
    //0.5 to 1 g to r

    if (value < 0.5f) {
        b = 255 * (1.0f - 2 * value);
        g = 255 * 2 * value;
    }
    else {
        g = 255 * (2.0f - 2 * value);
        r = 255 * (2 * value - 1);
    }

    return sf::Color(r, g, b);
}

int main()
{
    //Displaying the window
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "OrbitalSim");
    window.setFramerateLimit(60);

    std::vector<GravitySource> sources;

    sources.push_back(GravitySource(500, 500, 7000));
    sources.push_back(GravitySource(1200, 500, 7000));

    int num_particles = 2000;

    std::vector<Particle> particles;

    for (int i = 0; i < num_particles; i++) {
        //Starting all the particles at the same x pos, y pos, x vel, but different y vel
        particles.push_back(Particle(600, 700, 4, 0.2 + (0.1 / num_particles * i)));

        //Change colors
        float val = (float)i / (float)num_particles;

        sf::Color col = map_val_to_color(val);

        particles[i].set_color(col);
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
        }

        window.clear();

        //Updating the physics of the particles
        for (int i = 0; i < sources.size(); i++) {
            for (int j = 0; j < particles.size(); j++) {
                particles[j].update_physics(sources[i]);
            }
        }

        //Draw calls
        for (int i = 0; i < sources.size(); i++) {
            sources[i].render(window);
        }

        for (int j = 0; j < particles.size(); j++) {
            particles[j].render(window);
        }

        window.display();
    }
    return 0;
}

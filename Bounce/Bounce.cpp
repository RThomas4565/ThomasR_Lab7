#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>

using namespace std;
using namespace sf;
using namespace sfp;

int main()
{
    // Create our window and world with gravity 0,1
    RenderWindow window(VideoMode(800, 600), "Bounce");
    World world(Vector2f(0, 1));

    // Create the ball
    PhysicsCircle ball;
    ball.setCenter(Vector2f(400, 300));
    ball.setRadius(20);
    world.AddPhysicsBody(ball);

    // Create the floor
    PhysicsRectangle floor;
    floor.setSize(Vector2f(800, 20));
    floor.setCenter(Vector2f(400, 590));
    floor.setStatic(true);
    world.AddPhysicsBody(floor);

    // Create physics rectangles for the left, right, and top sides
    PhysicsRectangle leftWall;
    leftWall.setSize(Vector2f(20, 600));
    leftWall.setCenter(Vector2f(10, 300));
    leftWall.setStatic(true);
    world.AddPhysicsBody(leftWall);

    PhysicsRectangle rightWall;
    rightWall.setSize(Vector2f(20, 600));
    rightWall.setCenter(Vector2f(790, 300));
    rightWall.setStatic(true);
    world.AddPhysicsBody(rightWall);

    PhysicsRectangle topWall;
    topWall.setSize(Vector2f(800, 20));
    topWall.setCenter(Vector2f(400, 10));
    topWall.setStatic(true);
    world.AddPhysicsBody(topWall);


    PhysicsRectangle centerObstacle;
    centerObstacle.setSize(Vector2f(100, 100));
    centerObstacle.setCenter(Vector2f(400, 300));


    int bangCount = 0;


    bool ballInContactWithCenterObstacle = false;



    int thudCount = 0;

    Font font;
    font.loadFromFile("arial.ttf"); 

    Text bangText;
    bangText.setFont(font);
    bangText.setCharacterSize(24);
    bangText.setFillColor(Color::White);
    bangText.setPosition(10, 10); 

    Text thudText;
    thudText.setFont(font);
    thudText.setCharacterSize(24);
    thudText.setFillColor(Color::White);
    thudText.setPosition(10, 40); 

    Clock clock;
    Time lastTime(clock.getElapsedTime());

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        Time currentTime(clock.getElapsedTime());
        Time deltaTime(currentTime - lastTime);
        int deltaTimeMS(deltaTime.asMilliseconds());

        if (deltaTimeMS > 0) {


            world.UpdatePhysics(deltaTimeMS);
            lastTime = currentTime;
        }

        if (ball.getGlobalBounds().intersects(centerObstacle.getGlobalBounds())) {
            if (!ballInContactWithCenterObstacle) {
                bangCount++;
                ballInContactWithCenterObstacle = true;

                Vector2f velocity = ball.getVelocity();
                    velocity.x = -velocity.x; 
                velocity.y = -velocity.y; 
                ball.setVelocity(velocity);

                if (bangCount >= 3) {
                    cout << "Bang " << bangCount << endl;
                    exit(0); 
                }
                else {
                    cout << "Bang " << bangCount << endl;
                }
            }
        }
        else {
            ballInContactWithCenterObstacle = false;
        }
        if (ball.getGlobalBounds().intersects(leftWall.getGlobalBounds()) ||
            ball.getGlobalBounds().intersects(rightWall.getGlobalBounds()) ||
            ball.getGlobalBounds().intersects(topWall.getGlobalBounds())) {
            thudCount++;
            cout << "Thud " << thudCount << endl;
        }
        bangText.setString("Bang: " + to_string(bangCount));
        thudText.setString("Thud: " + to_string(thudCount));

        window.clear(Color(0, 0, 0));
        window.draw(ball);
        window.draw(floor);
        window.draw(leftWall);
            window.draw(rightWall);
        window.draw(topWall);
        window.draw(centerObstacle);
        window.draw(bangText);
        window.draw(thudText);
        window.display();
    }

    return 0;
}   

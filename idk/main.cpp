#include<iostream>
#include<vector>
#include<math.h>
#include<SFML/Graphics.hpp>
#include<time.h>

using namespace std;

class Enemy{

public:
    sf::Sprite shape;
    sf::Texture *texture;
    Enemy(sf::Texture* texture,int x,int y){
    this->texture=texture;
    this->shape.setTexture(*texture);
    this->shape.setScale(0.8f,0.8f);
    this->shape.setPosition(x,y);


    }
    void locomote(){
    shape.move(-0.2f,0.0f);
    }
};
class Bullet{
public:
    sf::Sprite shape;
    sf::Texture *texture;
    Bullet(sf::Texture* texture,sf::Vector2f pos){
        this->texture=texture;
        this->shape.setTexture(*texture);
        this->shape.scale(0.2f,0.2f);
        this->shape.setPosition(pos.x+200,pos.y+80);
}
    void locomote(){
       shape.move(4.0f,0.0f);
    }
};
class Player{
public:
    sf::Sprite shape;
    sf::Texture *texture;
    vector<Bullet> bullets;
    vector<Enemy>enemies;
    Player(sf::Texture *texture){
    this->texture=texture;
    this->shape.setTexture(*texture);

    }
    void up(){
        shape.move(0.0f,-5.0f);
    }
    void down(){
    shape.move(0.0f,5.0f);
    }
};

int main()
{
    int x=700;
    int y=20;
    srand(time(0));
sf::RenderWindow window(sf::VideoMode(800,600),"game!",sf::Style::Close);
window.setFramerateLimit(1080);
sf::Event ev;

sf::Texture etexture;
etexture.loadFromFile("path to the enemy image");

sf::Texture texture;
texture.loadFromFile("add your path to the maincharacter's image :)");
Player player(&texture);
sf::Texture btexture;
btexture.loadFromFile("add path to the bullet image");
for(int i=0;i<5;i++){
    player.enemies.push_back(Enemy(&etexture,rand()%1000,rand()%500));
}
while(window.isOpen()){
    while(window.pollEvent(ev)){
        if(ev.type==ev.Closed){
            window.close();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
            player.bullets.push_back(Bullet(&btexture,player.shape.getPosition()));

        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                player.shape.move(0.0f,-10.0f);
              window.draw(player.shape);
}

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            player.shape.move(0.0f,10.0f);
            window.draw(player.shape);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
           player.shape.move(10.0f,0.0f);
            window.draw(player.shape);
        }
   if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
           player.shape.move(-10.0f,0.0f);
    window.draw(player.shape);
        }

    }
    window.clear();
    window.draw(player.shape);
    sf::RectangleShape healthbar(sf::Vector2f(x,y));
    healthbar.setFillColor(sf::Color::Red);
    window.draw(healthbar);
        for(int i=0;i<player.bullets.size();i++){
            window.draw(player.bullets[i].shape);
                player.bullets[i].locomote();
                if(player.bullets[i].shape.getPosition().x>800){
                player.bullets.erase(player.bullets.begin()+i);
                }
}
        for(int j=0;j<player.enemies.size();j++){
            window.draw(player.enemies[j].shape);

            player.enemies[j].locomote();
            if(player.enemies[j].shape.getPosition().x<0){
                player.enemies.erase(player.enemies.begin()+j);
            }

              for(int i=0;i<player.bullets.size();i++){
                if(player.bullets[i].shape.getPosition().x>player.enemies[j].shape.getPosition().x &&player.bullets[i].shape.getPosition().y>player.enemies[j].shape.getPosition().y && player.bullets[i].shape.getPosition().x<player.enemies[j].shape.getPosition().x+100){
                        player.enemies.erase(player.enemies.begin()+j);
                        player.enemies.push_back(Enemy(&etexture,rand()%1000,rand()%500));
                }
        }
        }
window.display();
}
}

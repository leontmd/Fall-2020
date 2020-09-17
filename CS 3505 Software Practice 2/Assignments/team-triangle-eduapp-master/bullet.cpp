#include "bullet.h"
#include "QDebug"

bullet::~bullet() = default;

bullet::bullet(engine& eng, sf::Sprite sprite)
    : _sprite(sprite), _progress(0), _show_explosion(false), _upper_bounds(eng.window().getSize()), _lower_bounds(sf::Vector2i(0,0)){

    _sprite.setOrigin(4,7);
    _explosion.emplace_back(new sf::Sprite(eng.load_texture("../team-triangle-eduapp/assets/Tanks/PNG/"
                                                      "DefaultSize/explosion1.png")));
    _explosion[0]->setOrigin(30,30);
    _explosion.emplace_back(new sf::Sprite(eng.load_texture("../team-triangle-eduapp/assets/Tanks/PNG/"
                                                      "DefaultSize/explosion2.png")));
    _explosion[1]->setOrigin(28,28);
    _explosion.emplace_back(new sf::Sprite(eng.load_texture("../team-triangle-eduapp/assets/Tanks/PNG/"
                                                      "DefaultSize/explosion3.png")));
    _explosion[2]->setOrigin(32,32);
    _explosion.emplace_back(new sf::Sprite(eng.load_texture("../team-triangle-eduapp/assets/Tanks/PNG/"
                                                      "DefaultSize/explosion4.png")));
    _explosion[3]->setOrigin(23,23);
    _explosion.emplace_back(new sf::Sprite(eng.load_texture("../team-triangle-eduapp/assets/Tanks/PNG/"
                                                     "DefaultSize/explosion5.png")));
    _explosion[4]->setOrigin(26,26);

}

sf::Vector2f bullet::get_location() { return _sprite.getPosition(); }

bool bullet::show_explosion() {
    _show_explosion = true;
    _progress++;
    if(_progress == 24){
        //_show_explosion = false;
        _progress = 0;
        return true;
    }
    return false;
}

bool bullet::update() {
    if(!_show_explosion){
        if((_sprite.getPosition().x > _upper_bounds.x || _sprite.getPosition().x < _lower_bounds.x) ||(_sprite.getPosition().y > _upper_bounds.y || _sprite.getPosition().y < _lower_bounds.y)){
            if(show_explosion()){
                _show_explosion = false;
                return true;
            }
            return false;
        }else{
            _sprite.move(_direction);
            return false;
        }
    }else{
        if(show_explosion()){
            _show_explosion = false;
            return true;
        }
        return false;
    }
}

void bullet::set_location(sf::Vector2f pos) { _sprite.setPosition(pos); }

void bullet::move(int x, int y) { _sprite.move(x, y); }

void bullet::set_direction(float x, float y) { _direction = sf::Vector2f(x*3,y*3); }

void bullet::set_rotation(float angle) { _sprite.setRotation(180+angle); }

void bullet::set_bounds(int low_x, int low_y, int high_x, int high_y)
{
    _lower_bounds = sf::Vector2i(low_x, low_y);
    _upper_bounds = sf::Vector2i(high_x, high_y);
}

void bullet::draw(sf::RenderTarget& target, sf::RenderStates) const {
    if(_show_explosion){
        _explosion[_progress/5]->setPosition(_sprite.getPosition());
        target.draw(*_explosion[(_progress/5)]);
    } else {
        target.draw(_sprite);
    }
}


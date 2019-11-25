#include <ostream>
#include <deque>
#include <SFML/System/Vector2.hpp>
#include <iostream>

class Snake
{
public:
  sf::Vector2f position;
  int body_size;
  std::deque<sf::Vector2f> body_queue;
  sf::Vector2f direction;

  Snake(sf::Vector2f p_position, int p_size, sf::Vector2f p_direction);
  Snake();
  void update_body(sf::Vector2f new_position);

  
  
};

class Food
{
public:
  sf::Vector2f position;

  Food(sf::Vector2f p_position);
  Food();
};



template <typename T>
std::ostream& operator<< (std::ostream& flux, const std::deque<T>& q) {
  flux << "{ ";
  if ( !q.empty() ) {
    for (auto v : q){
      flux << v << ", ";
    }
  }
  flux << "}";
  return flux;
}

std::ostream &operator<<(std::ostream &flux, Food const &food);
std::ostream &operator<<(std::ostream &flux, Snake const &snake);
std::ostream &operator<<(std::ostream &flux, sf::Vector2f const &vector);


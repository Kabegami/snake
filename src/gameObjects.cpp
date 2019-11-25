#include "gameObjects.hpp"
#include <SFML/System/Vector2.hpp>


Snake::Snake(sf::Vector2f p_position, int p_size, sf::Vector2f p_direction){
  position = p_position;
  direction = p_direction;
  body_size = p_size;
  // we create the body part in the opposite direction of the snake
  // we start by the last blocks to have the good behavior when new elements come (the latest blocks are deleted first)
  for (float i=body_size; i > 0; i--){
    body_queue.push_back(position + -i * direction);
    }
  

}

// default constructor because c++ doesn't allow constructor to have objects parameters wich don't have a default constructor
Snake::Snake(){
  position = sf::Vector2f(0, 0);
  direction = sf::Vector2f(0, 0);
  body_size = 0;
}

Food::Food(){
  position = sf::Vector2f(0, 0);
}

void Snake::update_body(sf::Vector2f new_position){
  body_queue.push_back(new_position);
  while (body_queue.size() > body_size){
    body_queue.pop_front();
  }
}




// ========================================
Food::Food(sf::Vector2f p_position){
  position = p_position;
}

// add a flux operator for Vector2i for debuging conveniance
std::ostream &operator<<(std::ostream &flux, sf::Vector2f const &vector){
  return flux << "[ " << vector.x << ", " << vector.y << " ]";
}

std::ostream &operator<<(std::ostream &flux, Food const &food){
  return flux << "Food object -- position : " << food.position;
}

std::ostream &operator<<(std::ostream &flux, Snake const &snake){
  return flux << "Snake Object " << "\n" << "position : " << snake.position << ", "
	      << "direction : " << snake.direction << "\n"
	      << "body size : " << snake.body_size << "\n"
	      << "body queue " << snake.body_queue;
}

#include "gameObjects.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <string>
#include <unordered_map>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>

void change_only_valid_direction(Snake &snake, const sf::Vector2f &old_direction, sf::Vector2f direction);

class GameEngine
{
public:
  Snake snake;
  Food food;
  sf::Vector2i grid_dim;

  GameEngine(Snake p_snake, Food p_food, sf::Vector2i grid_dim);

  bool can_move();
  bool can_snake_eat();
  
  void respawn_food();
  void snake_eat();
  bool step(sf::Vector2f &old_direction);
  sf::VertexArray compute_snake_vertexes(sf::Texture texture, std::unordered_map<std::string, sf::IntRect> spriteMap);
  sf::VertexArray compute_food_vertexes(sf::Texture texture, std::unordered_map<std::string, sf::IntRect> spriteMap);
  sf::VertexArray compute_vertexes(sf::Texture texture, std::unordered_map<std::string, sf::IntRect> spriteMap, float square_size);
};

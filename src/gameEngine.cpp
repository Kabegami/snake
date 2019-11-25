#include "gameEngine.hpp"
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <algorithm>

bool anySup(sf::Vector2f v1, sf::Vector2i v2){return (v1.x >= v2.x) || (v1.y >= v2.y);}
bool anyInf(sf::Vector2f v1, sf::Vector2i v2) {return (v1.x < v2.x) || (v1.y < v2.y);}

void change_only_valid_direction(Snake &snake, const sf::Vector2f &old_direction, sf::Vector2f direction){
  auto sum = old_direction + direction;
  if ((sum.x == 0) && (sum.y == 0)){
    return;
  }
  snake.direction = direction;
}

// void change_only_valid_direction(Snake &snake, sf::Vector2f direction){
//   auto sum = snake.direction + direction;
//   if ((sum.x == 0) && (sum.y == 0)){
//     return;
//   }
//   snake.direction = direction;
// }
  
  

int randint(int maxValue){
  return rand() % maxValue;
}

GameEngine::GameEngine(Snake p_snake, Food p_food, sf::Vector2i p_grid_dim){
  snake = p_snake;
  food = p_food;
  grid_dim = p_grid_dim;
}

bool GameEngine::can_move(){
  sf::Vector2f pos = snake.position + snake.direction;
  bool grid_check = (anySup(pos,  grid_dim) || anyInf(pos, sf::Vector2i(0, 0)));
  auto predicate = [&pos](sf::Vector2f v) -> bool {return v == pos;};
  bool body_check = std::any_of(snake.body_queue.begin()+1, snake.body_queue.end(), predicate);
  return !(grid_check || body_check);

  
}

bool GameEngine::can_snake_eat() { return snake.position + snake.direction == food.position; }

void GameEngine::respawn_food(){
  sf::Vector2f pos = sf::Vector2f(randint(grid_dim.x), randint(grid_dim.y));

  auto predicate = [&pos](sf::Vector2f v) -> bool {return v == pos;};
  
  while (pos == snake.position ||
	 std::any_of(snake.body_queue.begin(), snake.body_queue.end(), predicate))
    {
      pos = sf::Vector2f(randint(grid_dim.x), randint(grid_dim.y));
    }
  food.position = pos;
}

bool GameEngine::step(sf::Vector2f &old_direction){
  if (!GameEngine::can_move()){return true;}

  if (GameEngine::can_snake_eat()){
    snake.body_size++;
    GameEngine::respawn_food();
  }
  snake.update_body(snake.position);
  snake.position = snake.position + snake.direction;
  old_direction = snake.direction;
  return false;
}

void create_quad(sf::VertexArray &quadArray, int index, sf::Vector2f position, sf::IntRect rect){
  quadArray[index].position = position;
  quadArray[index + 1].position = position + sf::Vector2f(rect.width, 0);
  quadArray[index + 2].position = position + sf::Vector2f(rect.width, rect.height);
  quadArray[index + 3].position = position + sf::Vector2f(0, rect.height);

  quadArray[index].texCoords = sf::Vector2f(rect.left, rect.top);
  quadArray[index + 1].texCoords = sf::Vector2f(rect.left + rect.width, rect.top);
  quadArray[index + 2].texCoords = sf::Vector2f(rect.left + rect.width, rect.top + rect.height);
  quadArray[index + 3].texCoords = sf::Vector2f(rect.left , rect.top + rect.height);  
}


sf::VertexArray GameEngine::compute_vertexes(sf::Texture texture, std::unordered_map<std::string, sf::IntRect> spriteMap, float square_size){
  int quadNumbers = 2 + snake.body_size;
  sf::VertexArray quadArray(sf::Quads, quadNumbers * 4);
  create_quad(quadArray, 0, food.position * square_size, spriteMap.at("food"));

  if (snake.direction == sf::Vector2f(1, 0)){
    create_quad(quadArray, 4, snake.position * square_size, spriteMap.at("head-right"));    
  }

  if (snake.direction == sf::Vector2f(-1, 0)){
    create_quad(quadArray, 4, snake.position * square_size, spriteMap.at("head-left"));    
  }

  if (snake.direction == sf::Vector2f(0, 1)){
    create_quad(quadArray, 4, snake.position * square_size, spriteMap.at("head-up"));
  }

  if (snake.direction == sf::Vector2f(0, -1)){
    create_quad(quadArray, 4, snake.position * square_size, spriteMap.at("head-down"));
  }
  
  for (int i = 0; i < snake.body_size; i++){
    create_quad(quadArray, (i+2)*4, snake.body_queue[i] * square_size, spriteMap.at("body"));
  }
  
  
  
  return quadArray;
}



// int main(){
//   Snake s = Snake(sf::Vector2f(8, 2), 1, sf::Vector2f(1, 0));
//   Food f = Food(sf::Vector2f(10, 10));
//   GameEngine g = GameEngine(s, f, sf::Vector2f(10, 10));
//   std::cout << g.can_move() << std::endl;
  

//   // std::cout << s << std::endl;
//   // std::cout << f << std::endl;
//   return 0;
// }



#include "gameEngine.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <string>
#include <unordered_map>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/VideoMode.hpp>



int main(){
  sf::Vector2i grid_dim = sf::Vector2i(10, 10);
  int square_size = 32;
  const float time_step = 0.20;
  
  std::string texture_file {"../img/Snake.png"};
  sf::RenderWindow window(sf::VideoMode(grid_dim.y * square_size, grid_dim.x * square_size), "Snake");
  sf::Clock clock;  
  bool gameOver = false;
  sf::Vector2f old_direction = sf::Vector2f(1, 0);

  int ncols = 3;

  auto spriteIndex_to_rect = [square_size, ncols](int index) -> sf::IntRect {
			       int i = index / ncols;
			       int j = index % ncols;
			       return sf::IntRect(j*square_size, i*square_size, square_size, square_size);
			       };
  
  

  std::unordered_map<std::string, sf::IntRect> spriteMap;
  spriteMap.insert({"background", spriteIndex_to_rect(0)});
  spriteMap.insert({"head-up", spriteIndex_to_rect(1)});
  spriteMap.insert({"head-down", spriteIndex_to_rect(2)});
  spriteMap.insert({"head-left", spriteIndex_to_rect(3)});
  spriteMap.insert({"head-right", spriteIndex_to_rect(4)});
  spriteMap.insert({"body", spriteIndex_to_rect(5)});
  spriteMap.insert({"food", spriteIndex_to_rect(6)});
  
  
  
  sf::Texture background_texture;
  if (!background_texture.loadFromFile(texture_file, spriteMap.at("background"))){
    std::cout << "An error have occured while loading the texture file : " <<  texture_file << std::endl;
    return -1;
  }

  background_texture.setRepeated(true);

  sf::Texture texture;
  texture.loadFromFile(texture_file);
  
  sf::Sprite background;
  background.setTexture(background_texture);
  background.setScale(sf::Vector2f(2, 2));
  background.setTextureRect({0, 0, grid_dim.x * square_size, grid_dim.y * square_size});

  //game objects
  Snake snake = Snake(sf::Vector2f(grid_dim / 2), 2, sf::Vector2f(1, 0));
  Food food = Food(sf::Vector2f(0, 0));
  GameEngine engine = GameEngine(snake, food, grid_dim);
  //spawn the food at a random space without spawning on a snake tile
  engine.respawn_food();
    

  

  while (window.isOpen()){
    sf::Event event;
    while (window.pollEvent(event)){
      switch (event.type) {
      case sf::Event::Closed:
	window.close();
	break;

      case sf::Event::KeyPressed:
	switch (event.key.code){
	case sf::Keyboard::Left:
	  change_only_valid_direction(engine.snake, old_direction,  sf::Vector2f(-1, 0));
	  break;

	case sf::Keyboard::Right:
	  change_only_valid_direction(engine.snake,  old_direction,sf::Vector2f(1, 0));
	  break;
	  
	case sf::Keyboard::Up:
	  change_only_valid_direction(engine.snake,  old_direction,sf::Vector2f(0, -1));
	  break;
	  
	case sf::Keyboard::Down:
	  change_only_valid_direction(engine.snake,  old_direction,sf::Vector2f(0, 1));
	  break;
	  
	  
	default:
	  break;
	}
	break;

      default:
	break;
      }


      
    }

    

    if (clock.getElapsedTime().asSeconds() > time_step){
      gameOver = engine.step(old_direction);
      clock.restart();
    }

    if (gameOver){
      window.close();
      std::cout << "Game over !" << std::endl;
      return 0;
    }
    
    window.clear(sf::Color::White);
    window.draw(background);

    sf::VertexArray vertexes = engine.compute_vertexes(texture, spriteMap, square_size);
    // std::cout << vertexes[0].position << vertexes[1].position << vertexes[2].position << vertexes[3].position << std::endl;

    // std::cout << vertexes[0].texCoords << vertexes[1].texCoords << vertexes[2].texCoords << vertexes[3].texCoords << std::endl;
    
    window.draw(vertexes, &texture);
    window.display();
    
  }

  return 0;
}

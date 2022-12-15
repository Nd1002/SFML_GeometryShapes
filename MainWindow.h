#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <iostream>

#include <SFML/Graphics.hpp>

#include <vector>
#include <map>
#include <memory>



namespace gui
{

			enum typeShape { RECTANGLE = 0, TRINAGLE = 1, CIRCLE = 2, RHOMB = 3 };

			class Button {
			public:
				Button(sf::Vector2f size, sf::Vector2f position, std::string lblButton, typeShape);
				bool mouseOnClick(sf::Vector2i mousePosition, bool pressedTrigger);
				void drawTo(sf::RenderWindow*);
				typeShape attchType;
			private:
				sf::Text text; 
				sf::Font font; 
				sf::RectangleShape btnGround;
				sf::Color baseColor;

			};

			class GShape {
			public:
				GShape(typeShape, sf::Color color, const sf::Vector2f& position);
				~GShape();
				void drawTo(sf::RenderWindow*);
				bool active;
			private:
				sf::Shape* shape;
			};

	class MainWindow : public sf::RenderWindow {
	public: 
		MainWindow();
		int show(); 
	private: 
		void renderButton(sf::RenderWindow*, std::vector<std::shared_ptr<Button>>*);
		void cntrlPressedButton(bool prsdTrg, sf::Vector2i mousePosition, std::vector<std::shared_ptr<Button>>*, std::map<typeShape, std::shared_ptr<GShape>>* Shapes);
		void renderShape(sf::RenderWindow*, std::map<typeShape, std::shared_ptr<GShape>> *Shapes);
		void setObjects();
		std::vector<std::shared_ptr<Button>> Buttons; 
		std::map<typeShape, std::shared_ptr<GShape>> Shapes;
	
	};
};
#endif 
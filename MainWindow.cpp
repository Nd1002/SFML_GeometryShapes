#include "MainWindow.h"


//button
namespace gui{

	Button::Button(sf::Vector2f size, sf::Vector2f position, std::string lblButton, typeShape attchType)
	{
        float xPosText = 0; 
        float yPosText = 0;
        this->baseColor = sf::Color(219, 142, 142);
		this->attchType = attchType;
        this->btnGround.setFillColor(baseColor);
        this->btnGround.setSize(size);
        this->btnGround.setPosition(position);

        this->font.loadFromFile("Herborn.ttf"); 
        this->text.setString(lblButton);
        this->text.setFont(font);
        this->text.setFillColor(sf::Color::Black);
        this->text.setCharacterSize(12);
        this->text.setStyle(sf::Text::Regular);
        
        xPosText = (position.x + btnGround.getLocalBounds().width / 2 - (text.getLocalBounds().width / 2)); //- (btnGround.getLocalBounds().width / 2);
        yPosText = (position.y + btnGround.getLocalBounds().height / 2) - (text.getLocalBounds().height / 2);
        this->text.setPosition(sf::Vector2f(xPosText, yPosText));

	}

	bool  Button::mouseOnClick(sf::Vector2i mousePosition, bool pressedTrigger){
			if (btnGround.getGlobalBounds().contains(mousePosition.x, mousePosition.y) && !pressedTrigger) {
				btnGround.setFillColor(baseColor);
				return true;
			}
			else if (btnGround.getGlobalBounds().contains(mousePosition.x, mousePosition.y) && pressedTrigger) {
				btnGround.setFillColor(sf::Color(233, 224, 224));
				return true;
			}

			return false;
	}

	void Button::drawTo(sf::RenderWindow*window) {
		window->draw(btnGround); 
		window->draw(text);
	}

    
//Shape 
	GShape::GShape(gui::typeShape TypeShape, sf::Color color, const sf::Vector2f& position) {
		active = false;

			switch (TypeShape) {
			case RECTANGLE:
				this->shape = new sf::RectangleShape(sf::Vector2f(150, 50));
				break;
			case TRINAGLE:
				this->shape = new sf::CircleShape(80, 3);
				break;
			case CIRCLE:
				this->shape = new sf::CircleShape(50);
				break;
			case RHOMB:
				this->shape = new sf::CircleShape(80, 4);
				break;
			}
			this->shape->setFillColor(color);
			this->shape->setPosition(position);
	}

	void GShape::drawTo(sf::RenderWindow* renderWindow) {
		renderWindow->draw(*this->shape);
	}

	GShape::~GShape() {
		if(this->shape)
			delete this->shape; 
	}




//Window

	void MainWindow::renderButton(sf::RenderWindow* window, std::vector<std::shared_ptr<Button>>* Buttons) {
		for (auto btnObject : *Buttons) {
			btnObject->drawTo(window);
		}
	}
	
	MainWindow::MainWindow()
	{
		sf::VideoMode modeWindow(900 , 400);
		const char* WindowTitle = "Geometry shapes";

		this->create(modeWindow, WindowTitle);

		setObjects();
	}

	void MainWindow::renderShape(sf::RenderWindow* window, std::map<typeShape, std::shared_ptr<GShape>>* Shapes) {
		for (auto Shape : *Shapes) {
			if (Shape.second->active) {
				Shape.second->drawTo(window); 
			}
		}
	}

	void MainWindow::cntrlPressedButton(bool prsdTrg, sf::Vector2i mousePosition, std::vector<std::shared_ptr<Button>>* Buttons, std::map<typeShape, std::shared_ptr<GShape>>* Shapes) {
		for (auto btnObject : *Buttons) {
			typeShape tpShape = btnObject->attchType;
			size_t res = Shapes->count(tpShape); 
			if (btnObject->mouseOnClick(mousePosition, prsdTrg) && res) {
				Shapes->at(tpShape)->active = true; 
			}
		}
	}

	void MainWindow::setObjects() {
        sf::Vector2f sizeButton2F(150, 50);
		float posX = 100; 
		float posY = this->getPosition().y + 250; 
		Buttons.push_back(std::make_shared<Button>(sizeButton2F,
		sf::Vector2f(posX, posY),"Show rectangle", RECTANGLE));

		Buttons.push_back(std::make_shared<Button>(sizeButton2F,
	    sf::Vector2f(posX + 200, posY), "Show triangle", TRINAGLE));

		Buttons.push_back(std::make_shared<Button>(sizeButton2F,
		sf::Vector2f(posX + 400, posY), "Show circle", CIRCLE));

		Buttons.push_back(std::make_shared<Button>(sizeButton2F,
		sf::Vector2f(posX + 600, posY), "Show rhobm", RHOMB));

		Shapes.emplace(std::make_pair(RECTANGLE, std::make_shared<GShape>(RECTANGLE, sf::Color::Red,
			sf::Vector2f(posX - 25, posY - 200))));

		Shapes.emplace(std::make_pair(TRINAGLE, std::make_shared<GShape>(TRINAGLE, sf::Color::Green,
			sf::Vector2f(posX + 150, posY - 200))));

		Shapes.emplace(std::make_pair(CIRCLE, std::make_shared<GShape>(CIRCLE, sf::Color::Cyan,
			sf::Vector2f(posX + 400, posY - 200))));

		Shapes.emplace(std::make_pair(RHOMB, std::make_shared<GShape>(RHOMB, sf::Color::Blue,
			sf::Vector2f(posX + 600, posY - 200))));
	}


	int MainWindow::show()
	{

		while (this->isOpen()) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(*this);
			sf::Event eventWindow;
			while (this->pollEvent(eventWindow)) {
				if (eventWindow.type == sf::Event::Closed) {
					this->close();
				}
				if (eventWindow.type == sf::Event::MouseButtonPressed && 
					eventWindow.key.code == sf::Mouse::Left) {
						cntrlPressedButton(1,mousePos, &Buttons, &Shapes);
					
				}
				if (eventWindow.type == sf::Event::MouseButtonReleased && 
					eventWindow.key.code == sf::Mouse::Left) {
						cntrlPressedButton(0,mousePos, &Buttons, &Shapes);
				}
			}

			this->clear(sf::Color(234, 221, 200));
			renderButton(this, &Buttons); 
			renderShape(this, &Shapes);
			this->display();

		}
		return 0;
	}
};
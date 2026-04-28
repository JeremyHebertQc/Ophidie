#pragma once

const float OUTLINE_THICKNESS_BUTTON = 10; //TODO: Déplacer dans const
const float OUTLINE_THICKNESS_PRESSED_BUTTON = 5; //TODO: Déplacer dans const

class Button
{
private:
	sf::RectangleShape _rectangle;
	sf::Text _text;
	sf::Color _fillColor, _outlineColor;
	sf::Vector2f _scale, _position;

	sf::SoundBuffer _pressedSoundBuffer;
	sf::Sound _pressedSound;
	sf::Font _font;


	unsigned int _buttonID;
	bool _isMouseReleased;

	void calculatePos();

public:
	// Constructeurs
	Button();
	Button(const unsigned int buttonID, const std::string text, const sf::Color fillColor, const sf::Color outlineColor, const sf::Vector2f scale, const sf::Vector2f position);

	// Destructeur
	~Button();

	// Getters
	sf::RectangleShape getRectangle() const;
	sf::Text getText() const;
	sf::Color getFillColor() const;
	sf::Color getOutlineColor() const;
	float getOutlineThickness() const;
	sf::Vector2f getScale() const;
	sf::Vector2f getPosition() const;
	sf::SoundBuffer getpressedSoundBuffer() const;
	sf::Sound getPressedSound() const;
	unsigned int getButtonID() const;
	bool getIsMouseReleased() const;

	// Setters
	void setRectangle(const sf::RectangleShape& rectangle);
	void setText(const sf::Text& text);
	void setFillColor(sf::Color fillColor);
	void setOutlineColor(sf::Color outlineColor);
	void setOutlineThickness(float thickness);
	void setScale(sf::Vector2f scale);
	void setPosition(sf::Vector2f position);
	void setpressedSoundBuffer(sf::SoundBuffer pressedSoundBuffer);
	void setPressedSound(sf::Sound pressedSound);
	void setButtonID(unsigned int buttonID);
	void setIsmouseReleased(bool isMouseReleased);

	// Fonctionnement du boutton
	void updateButton(sf::RenderWindow& window);
	void playButtonSound(sf::SoundBuffer& pressedSoundBuffer, sf::Sound& pressedSound, std::string soundPath = "assets/soundEffects/button.wav");
	void draw(sf::RenderWindow& window, const int activeID);
	bool isButtonPressed(sf::Event event, sf::RenderWindow& window);
	bool isButtonHover(sf::Event event, sf::RenderWindow& window);
};
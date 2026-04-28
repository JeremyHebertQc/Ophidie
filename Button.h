#pragma once
class Button
{
private:
	sf::RectangleShape _rectangle;
	sf::Text _text;
	sf::Color _fillColor, _outlineColor;
	sf::Vector2f _scale, _position;

	sf::SoundBuffer _pressedSoundBuffer;
	sf::Sound _pressedSound;


	unsigned int _buttonID;
	bool _isMouseReleased;

public:
	// Constructeurs
	Button();
	Button(const unsigned int buttonID, bool isMouseReleased);

	// Destructeur
	~Button();

	// Getters
	sf::RectangleShape getRectangle() const;
	sf::Text getText() const;
	sf::Color getFillColor() const;
	sf::Color getOutlineColor() const;
	sf::Vector2f getScale() const;
	sf::Vector2f getPosition() const;
	sf::SoundBuffer getpressedSoundBuffer() const;
	sf::Sound getPressedSound() const;
	unsigned int getButtonID() const;
	bool getIsMouseReleased() const;

	// Setters
	void setRectangle(sf::RectangleShape rectangle);
	void setText(sf::Text text);
	void setFillColor(sf::Color fillColor);
	void setOutlineColor(sf::Color outlineColor);
	void setScale(sf::Vector2f scale);
	void setPosition(sf::Vector2f position);
	void setpressedSoundBuffer(sf::SoundBuffer pressedSoundBuffer);
	void setPressedSound(sf::Sound pressedSound);
	void setButtonID(unsigned int buttonID);
	void setIsmouseReleased(bool isMouseReleased);

	// Fonctionnement du boutton
	void playButtonSound(sf::SoundBuffer pressedSoundBuffer, sf::Sound pressedSound, std::string soundPath = "assets/soundEffects/button.wav");
};
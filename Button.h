#pragma once

const float OUTLINE_THICKNESS_BUTTON = 10; //TODO: Déplacer dans const
const float OUTLINE_THICKNESS_PRESSED_BUTTON = 5; //TODO: Déplacer dans const
const std::string BUTTON_SOUND_PATH = "assets/soundEffects/button.wav"; //TODO: Déplacer dans const
const std::string FONT_PATH = "assets/fonts/arial.ttf"; //TODO: Déplacer dans const
const std::string TEXTURE_PATH = "assets/buttons/bigButton.png"; //TODO: Déplacer dans const

enum ButtonAction {
	debugAction,

	closeOphidie,
	startGame,
	openSettings,
	openScoreboard,
	openHTP,
	openHomeMenu,
	goToNormalSCR,
	goToSurvivalSCR,
	goToDeathTrapSCR,
	goToSurviveHellSCR,
	OpenFile,

	NbAction // Nombre total d'action
};

class Button
{
private:
	sf::Sprite _button;
	sf::Texture _texture, _pressedTexture;
	sf::Text _text;
	sf::Vector2f _scale, _position;

	sf::SoundBuffer _pressedSoundBuffer;
	sf::Sound _pressedSound;
	sf::Font _font;


	unsigned int _buttonID;
	bool _isMouseReleased;

	void calculatePos();

	int _action;

public:
	// Constructeurs
	Button();
	Button(const unsigned int buttonID, int action, const std::string text, const sf::Texture& texture, const sf::Vector2f scale, const sf::Vector2f position);

	// Destructeur
	~Button();

	// Getters
	sf::Sprite getSprite() const;
	sf::Text getText() const;
	sf::Vector2f getScale() const;
	sf::Vector2f getPosition() const;
	sf::SoundBuffer getpressedSoundBuffer() const;
	sf::Sound getPressedSound() const;
	unsigned int getButtonID() const;
	bool getIsMouseReleased() const;
	int getAction() const;
	sf::Texture getTexture() const;

	// Setters
	void setSprite(sf::Sprite button);
	void setText(const sf::Text& text);
	void setScale(sf::Vector2f scale);
	void setPosition(sf::Vector2f position);
	void setpressedSoundBuffer(sf::SoundBuffer pressedSoundBuffer);
	void setPressedSound(sf::Sound pressedSound);
	void setButtonID(unsigned int buttonID);
	void setIsmouseReleased(bool isMouseReleased);
	void setAction(int action);
	void setTexture(sf::Texture& texture);

	// Fonctionnement du boutton
	void updateButton(sf::RenderWindow& window);
	void playButtonSound(sf::SoundBuffer& pressedSoundBuffer, sf::Sound& pressedSound, std::string soundPath);
	void draw(sf::RenderWindow& window, const int activeID);
	bool isButtonPressed(sf::Event event, sf::RenderWindow& window);
	bool isButtonHover(sf::Event event, sf::RenderWindow& window);
	void doButtonAction(int action);
};
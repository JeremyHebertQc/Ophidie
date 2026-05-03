#pragma once

const float OUTLINE_THICKNESS_BUTTON = 10; //TODO: Déplacer dans const
const float OUTLINE_THICKNESS_PRESSED_BUTTON = 5; //TODO: Déplacer dans const
const std::string BUTTON_SOUND_PATH = "assets/soundEffects/"; //TODO: Déplacer dans const
const std::string FONT_PATH = "assets/fonts/PressStart2P.ttf"; //TODO: Déplacer dans const
const std::string BUTTON_TEXTURE_PATH = "assets/buttons/"; //TODO: Déplacer dans const
const int FONT_SIZE = 20; //TODO: Déplacer dans const

enum ButtonStyle
{
	bigButton,
	mediumButton,
	littleButton,
	yesButton,
	noButton
};

enum ButtonAction
{
	startGame,
	closeOphidie,
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
	// Gestion du bouton
	unsigned int _buttonID;
	int _action;

	// Gestion de l'apparence
	sf::Sprite _button;
	sf::Texture _texture, _pressedTexture;
	sf::Vector2f _scale, _position;

	// Gestion du texte
	sf::Text _text;
	sf::Font _font;
	sf::Color _textColor;
	void calculateTextPosition();

	// Gestion du son
	sf::SoundBuffer _soundEffectBuffer;
	sf::Sound _soundEffect;

public:
	// Constructeurs
	Button();
	Button(const unsigned int buttonID, int action, const std::string text, const int buttonStyle, const float scale, const sf::Vector2f position);

	// Destructeur
	~Button();

	// Getters
	unsigned int getButtonID() const;
	int getAction() const;

	sf::Texture getTexture() const;
	sf::Vector2f getScale() const;
	sf::Vector2f getPosition() const;

	sf::Text getText() const;

	// Setters
	void setButtonID(unsigned int buttonID);
	void setAction(int action);

	void setTexture(sf::Texture& texture);
	void setScale(sf::Vector2f scale);
	void setPosition(sf::Vector2f position);

	void setText(const sf::Text& text);
	void setTextColor(int r, int g, int b);

	// Fonctionnement du boutton
	void updateButton(sf::RenderWindow& window);
	void playButtonSound(sf::SoundBuffer& soundEffectBuffer, sf::Sound& soundEffect, std::string soundPath);
	void draw(sf::RenderWindow& window);
	int isButtonPressed(sf::Event event, sf::RenderWindow& window);
	bool isButtonHover(sf::Event event, sf::RenderWindow& window);
	void setButtonTexture(int buttonStyle);
};
#pragma once

#ifndef _MENUSYSTEM_
#define _MENUSYSTEM_



#include "Sound_system.h"
#include "Texture_System.h"
#include "Font_System.h"

class quit_Prompt
{
public:
	quit_Prompt(sf::RenderWindow& renderwindow, sf::Event& e, sf::Clock& clock, sf::Time& elapsed, Texture_System& message_Box, sf::Clock& messagebox_Animation, sf::Time& elapsed_Messagebox, Texture_System& background, Texture_System& YesBox, Texture_System& noBox)
	{
		bool quit_prompt = true;
		int quitPrompt_opt = 1;

		sf::Clock arrow_Animation;

		Texture_System no_Text("Textures/Main_menu_sprite_Sheet.png", sf::Vector2f(0.f, 0.f), sf::Vector2f(1000, 505), sf::IntRect(1079, 124, 111, 72), 0.8f, 0.8f, true, false);
		Texture_System Yes_Text("Textures/Main_menu_sprite_Sheet.png", sf::Vector2f(0.f, 0.f), sf::Vector2f(495, 510), sf::IntRect(1075, 211, 129, 65), 0.8f, 0.8f, true, false);

		Texture_System leftBlue_Arrow("Textures/Main_menu_sprite_Sheet.png", sf::Vector2f(0.f, 0.f), sf::Vector2f(1200, 500), sf::IntRect(404, 355, 58, 98), 1.f, 1.f, true, false);
		Texture_System rightBlue_Arrow("Textures/Main_menu_sprite_Sheet.png", sf::Vector2f(0.f, 0.f), sf::Vector2f(345, 255), sf::IntRect(470, 355, 61, 95), 1.f, 1.f, true, false);

		Sound_System menu_selectSfx2("Music/main_MenuSFX.wav", 100, 1.f, false);
		Sound_System selectOptSFX2("Music/Select sfx.ogg", 100, 1.f, false);

		Font_System T_quitPrompt("Fonts/segoeui.ttf", "Are you sure you want to quit? The pinguins would\nbe very sad if you left!", 34, true);

		T_quitPrompt.setPosition(345.f, 255.f);
		T_quitPrompt.setColor(155, 155, 255, 255);

		elapsed = clock.getElapsedTime();
		background.setPosition(sf::Vector2f(-40 * elapsed.asSeconds(), 0));
		background.setColor(sf::Color(255, 255, 255, 85));

		while (renderwindow.isOpen() && quit_prompt)
		{
			renderwindow.clear();
			background.draw(renderwindow);

			sf::Time elapsed_Animation = arrow_Animation.getElapsedTime();

			elapsed = clock.getElapsedTime();
			background.setPosition(sf::Vector2f(-40 * elapsed.asSeconds(), 0));

			while (renderwindow.pollEvent(e))
			{
				if (e.type == sf::Event::KeyPressed)
				{
					if (e.key.code == sf::Keyboard::Return)
					{
						switch (quitPrompt_opt)
						{

						case 1: //Yes
							renderwindow.close();
							break;
						case 2: //No
							quit_prompt = false;
							break;
						}
					}
					if (e.key.code == sf::Keyboard::Left && quitPrompt_opt > 1)
					{
						menu_selectSfx2.playMusic();
						quitPrompt_opt--;
						arrow_Animation.restart();
					}
					if (e.key.code == sf::Keyboard::Right && quitPrompt_opt < 2)
					{
						menu_selectSfx2.playMusic();
						quitPrompt_opt++;
						arrow_Animation.restart();
					}

				}
				if (e.type == sf::Event::Closed)
					renderwindow.close();
			}

			switch (quitPrompt_opt)
			{
			case 1:
			{
				YesBox.setColor(sf::Color(150, 180, 235, 255));
				noBox.setColor(sf::Color(150, 180, 235, 150));

				Yes_Text.setColor(sf::Color(150, 180, 235, 255));
				no_Text.setColor(sf::Color(150, 180, 235, 150));

				YesArrow_Animation(leftBlue_Arrow, rightBlue_Arrow, elapsed_Animation, arrow_Animation);
			}
			break;
			case 2:
			{
				YesBox.setColor(sf::Color(150, 180, 235, 150));
				noBox.setColor(sf::Color(150, 180, 235, 255));

				Yes_Text.setColor(sf::Color(150, 180, 235, 150));
				no_Text.setColor(sf::Color(150, 180, 235, 255));

				NoArrow_Animation(leftBlue_Arrow, rightBlue_Arrow, elapsed_Animation, arrow_Animation);
			}
			break;
			}

			leftBlue_Arrow.draw(renderwindow);

			YesBox.draw(renderwindow);
			noBox.draw(renderwindow);

			rightBlue_Arrow.draw(renderwindow);

			Yes_Text.draw(renderwindow);
			no_Text.draw(renderwindow);

			message_Box.draw(renderwindow);

			T_quitPrompt.draw(renderwindow);

			renderwindow.display();
		}
	}

	void YesArrow_Animation(Texture_System& leftBlue_Arrow, Texture_System& rightBlue_Arrow, sf::Time& elapsed_Animation, sf::Clock& arrow_Animation)
	{
		if (elapsed_Animation.asSeconds() < 1.5)
		{
			leftBlue_Arrow.setPosition(sf::Vector2f(325.f + (-25 * elapsed_Animation.asSeconds()), 490.0f));
			rightBlue_Arrow.setPosition(sf::Vector2f(705.f - (-25 * elapsed_Animation.asSeconds()), 490.0f));

			leftBlue_Arrow.setColor(sf::Color(150, 180, 235, 255 - (elapsed_Animation.asSeconds() * 169)));
			rightBlue_Arrow.setColor(sf::Color(150, 180, 235, 255 - (elapsed_Animation.asSeconds() * 169)));
		}
		else
			arrow_Animation.restart();
	}
	void NoArrow_Animation(Texture_System& leftBlue_Arrow, Texture_System& rightBlue_Arrow, sf::Time& elapsed_Animation, sf::Clock& arrow_Animation)
	{
		if (elapsed_Animation.asSeconds() < 1.5)
		{
			leftBlue_Arrow.setPosition(sf::Vector2f(825.f + (-25 * elapsed_Animation.asSeconds()), 490.0f));
			rightBlue_Arrow.setPosition(sf::Vector2f(1205.f - (-25 * elapsed_Animation.asSeconds()), 490.0f));

			leftBlue_Arrow.setColor(sf::Color(150, 180, 235, 255 - (elapsed_Animation.asSeconds() * 169)));
			rightBlue_Arrow.setColor(sf::Color(150, 180, 235, 255 - (elapsed_Animation.asSeconds() * 169)));
		}
		else
			arrow_Animation.restart();
	}

private:
};

//WORK IN PROGRESS\\

class credits_Screen
{
public:
	credits_Screen(sf::RenderWindow& renderwindow, sf::Event& e, sf::Clock clock, sf::Time& elapsed, Texture_System& background)
	{
		Texture_System Message_Box("Textures/Main_menu_sprite_Sheet.png", sf::Vector2f(0.0f, 0.0f), sf::Vector2f(375.f, -500.f), sf::IntRect(224, 497, 1051, 214), 0.8f, 10.f, true, false);

		Font_System T_creditsTitle("Fonts/segoeui.ttf", "Project PEnGUIn", 42, true);
		Font_System T_creditsText("Fonts/segoeui.ttf", "PRODUCED BY PROJECT PENGUIN", 32, true);
		Font_System T_creditsText2("Fonts/segoeui.ttf", "Created by Erik Magnusson and Dennis Mårtensson", 22, false);

		Texture_System leftBlue_Arrow("Textures/Main_menu_sprite_Sheet.png", sf::Vector2f(0.f, 0.f), sf::Vector2f(1200, 500), sf::IntRect(404, 355, 58, 98), 1.f, 1.f, true, false);
		Texture_System rightBlue_Arrow("Textures/Main_menu_sprite_Sheet.png", sf::Vector2f(0.f, 0.f), sf::Vector2f(345, 255), sf::IntRect(470, 355, 61, 95), 1.f, 1.f, true, false);

		Texture_System S_BackButton("Textures/Main_menu_sprite_Sheet.png", sf::Vector2f(0.0f, 0.0f), sf::Vector2f(595.f, 751.0f), sf::IntRect(10, 360, 395, 83), 1.f, 1.0f, true, false);
		Texture_System S_BackText("Textures/Main_menu_sprite_Sheet.png", sf::Vector2f(0.0f, 0.0f), sf::Vector2f(715.f, 762.f), sf::IntRect(548, 48, 191, 57), 0.8f, 0.8f, true, false);

		S_BackButton.setColor(sf::Color(150, 180, 235, 255));

		sf::Clock arrow_Animation;

		background.setColor(sf::Color(255, 255, 255, 85));

		T_creditsTitle.setUnderlined(true);
		T_creditsTitle.setPosition(625, 50);
		T_creditsText.setPosition(520, 175);
		T_creditsText2.setPosition(495, 255);


		bool credit_prompt = true;
		while (renderwindow.isOpen() && credit_prompt)
		{
			renderwindow.clear();
			sf::Time elapsed_Animation = arrow_Animation.getElapsedTime();

			elapsed = clock.getElapsedTime();
			background.setPosition(sf::Vector2f(-40 * elapsed.asSeconds(), 0));

			while (renderwindow.pollEvent(e))
			{
				if (e.type == sf::Event::Closed)
					renderwindow.close();
				if (e.type == sf::Event::KeyPressed)
				{
					if (e.key.code == sf::Keyboard::Return)
					{
						credit_prompt = false;
					}
				}
			}
			background.draw(renderwindow);

			Message_Box.draw(renderwindow);
			T_creditsTitle.draw(renderwindow);
			T_creditsText.draw(renderwindow);
			T_creditsText2.draw(renderwindow);

			leftBlue_Arrow.draw(renderwindow);
			S_BackButton.draw(renderwindow);
			rightBlue_Arrow.draw(renderwindow);
			acceptArrow_Animation(leftBlue_Arrow, rightBlue_Arrow, elapsed_Animation, arrow_Animation);

			S_BackText.draw(renderwindow);

			renderwindow.display();
		}
	}

	void acceptArrow_Animation(Texture_System& leftBlue_Arrow, Texture_System& rightBlue_Arrow, sf::Time& elapsed_Animation, sf::Clock& arrow_Animation)
	{
		if (elapsed_Animation.asSeconds() < 1.5)
		{
			leftBlue_Arrow.setPosition(sf::Vector2f(570.f + (-25 * elapsed_Animation.asSeconds()), 738.0f));
			rightBlue_Arrow.setPosition(sf::Vector2f(950.f - (-25 * elapsed_Animation.asSeconds()), 738.0f));

			leftBlue_Arrow.setColor(sf::Color(150, 180, 235, 255 - (elapsed_Animation.asSeconds() * 169)));
			rightBlue_Arrow.setColor(sf::Color(150, 180, 235, 255 - (elapsed_Animation.asSeconds() * 169)));
		}
		else
			arrow_Animation.restart();
	}

private:
};
//WORK IN PROGRESS\\

class Main_Menu
{
public:
	Main_Menu(sf::RenderWindow& renderwindow, sf::Event& e, sf::Clock clock, sf::Time& elapsed)

	{
		//Initiate a clock
		sf::Clock arrow_Animation;
		sf::Clock menuChange_Animation;
		sf::Clock messagebox_Animation;

		
		////Main Menu buttons
		Texture_System S_StartButton("Textures/Main_menu_sprite_Sheet.png", sf::Vector2f(0.0f, 0.0f), sf::Vector2f(870.f, 451.0f), sf::IntRect(10, 360, 395, 83), 1.f, 1.0f, true, false);
		Texture_System S_CreditsButton("Textures/Main_menu_sprite_Sheet.png", sf::Vector2f(0.0f, 0.0f), sf::Vector2f(870.f, 581.0f), sf::IntRect(10, 360, 395, 83), 1.0f, 1.0f, true, false);
		Texture_System S_QuitButton("Textures/Main_menu_sprite_Sheet.png", sf::Vector2f(0.0f, 0.0f), sf::Vector2f(870.f, 711.0f), sf::IntRect(10, 360, 395, 83), 1.0, 1.0f, true, false);
		
		Texture_System S_start_Text("Textures/Main_menu_sprite_Sheet.png", sf::Vector2f(0.0f, 0.0f), sf::Vector2f(980.f, 465.0f), sf::IntRect(27, 476, 161, 45), 1.f, 1.0f, true, false);
		Texture_System S_credits_Text("Textures/Main_menu_sprite_Sheet.png", sf::Vector2f(0.0f, 0.0f), sf::Vector2f(965.f, 595.0f), sf::IntRect(27, 529, 199, 45), 1.f, 1.0f, true, false);
		Texture_System S_quit_Text("Textures/Main_menu_sprite_Sheet.png", sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1000.f, 725.0f), sf::IntRect(26, 583, 113, 48), 1.f, 1.0f, true, false);
		
		//Message Box
		Texture_System Message_Box("Textures/Main_menu_sprite_Sheet.png", sf::Vector2f(0.0f, 0.0f), sf::Vector2f(225.f, 200.f), sf::IntRect(224, 497, 1051, 214), 1.1f, 1.1f, true, false);
		Texture_System yesBox("Textures/Main_menu_sprite_Sheet.png", sf::Vector2f(0.f, 0.f), sf::Vector2f(350, 500), sf::IntRect(10, 360, 395, 83), 1.f, 1.f, true, false);
		Texture_System noBox("Textures/Main_menu_sprite_Sheet.png", sf::Vector2f(0.f, 0.f), sf::Vector2f(850, 500), sf::IntRect(10, 360, 395, 83), 1.f, 1.f, true, false);
		
		//Arrows
		Texture_System leftBlue_Arrow("Textures/Main_menu_sprite_Sheet.png", sf::Vector2f(0.f, 0.f), sf::Vector2f(0, 0), sf::IntRect(404, 355, 58, 98), 1.f, 1.f, true, false);
		Texture_System rightBlue_Arrow("Textures/Main_menu_sprite_Sheet.png", sf::Vector2f(0.f, 0.f), sf::Vector2f(0, 0), sf::IntRect(470, 355, 61, 95), 1.f, 1.f, true, false);
		
		//Images
		Texture_System Main_menu_background("Backgrounds/Main_Menu_Background.png", sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 0.0f), sf::IntRect(0, 0, 1920 * 1000, 1080), 1.f, 1.f, true, true);
		Texture_System Main_Menu_Title("Textures/Project_PEnGUIn_Sheet2.png", sf::Vector2f(0.0f, 0.0f), sf::Vector2f(870.0f, 35.0f), sf::IntRect(85, 760, 265, 275), 1.45f, 1.45f, true, false);
		Texture_System Main_Menu_Vertex("Textures/Vertex_Array_PEnGUIn.png", sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 0.0f), sf::IntRect(0, 0, 1000, 900), 1.2f, 1.2f, true, false);
		
		////Initiate the Sound
		Sound_System menu_selectSfx("Music/main_MenuSFX.wav", 100, 1.f, false);
		Sound_System main_Theme("Music/01-Main_Theme.ogg", 25, 0.95f, true);
		Sound_System selectOptSFX("Music/Select sfx.ogg", 100, 1.f, false);
		
		main_Theme.playMusic();
		
		//Variables
		int menu_Option = 3;
		bool mainMenu = true;

		
        
		//While the Window is open "Do stuff"
		while (mainMenu && renderwindow.isOpen())
		{
			elapsed = clock.getElapsedTime();
			sf::Time elapsed_Animation = arrow_Animation.getElapsedTime();
			sf::Time elapsed_menuAnimation = menuChange_Animation.getElapsedTime();
			sf::Time elapsed_messagebox = messagebox_Animation.getElapsedTime();
		
			Main_menu_background.setPosition(sf::Vector2f(-40 * elapsed.asSeconds(), 0));
		
			renderwindow.clear();
		
			Main_menu_background.draw(renderwindow);
		
			Main_Menu_Title.draw(renderwindow);
			Main_Menu_Vertex.draw(renderwindow);
		
			leftBlue_Arrow.draw(renderwindow);
		
			S_StartButton.draw(renderwindow);
			S_start_Text.draw(renderwindow);
		
			S_CreditsButton.draw(renderwindow);
			S_credits_Text.draw(renderwindow);
		
			S_QuitButton.draw(renderwindow);
			S_quit_Text.draw(renderwindow);
		
			rightBlue_Arrow.draw(renderwindow);
		
			while (renderwindow.pollEvent(e))
			{
				if (e.type == sf::Event::KeyPressed)
				{
					if (e.key.code == sf::Keyboard::Up && menu_Option < 3)
					{
						menu_selectSfx.playMusic();
						menu_Option++;
						arrow_Animation.restart();
					}
		
					if (e.key.code == sf::Keyboard::Down && menu_Option > 1)
					{
						menu_selectSfx.playMusic();
						menu_Option--;
						arrow_Animation.restart();
					}
					if (e.key.code == sf::Keyboard::Return)
					{
						switch (menu_Option)
						{
						case 3: //Play start animation (Make a function within texture class)
						{
							selectOptSFX.playMusic();
							startChangeScene_Animation(S_StartButton, S_CreditsButton, S_QuitButton, S_start_Text, S_credits_Text, S_quit_Text, Main_Menu_Title, Main_Menu_Vertex, elapsed_menuAnimation, menuChange_Animation, renderwindow, e, Main_menu_background, elapsed, clock);
							mainMenu = false;
						}
						break;
						case 2: //Play credits animation (Make a function within texture class)
						{
							selectOptSFX.playMusic();
							creditsChangeScene_Animation(S_StartButton, S_CreditsButton, S_QuitButton, S_start_Text, S_credits_Text, S_quit_Text, Main_Menu_Title, Main_Menu_Vertex, elapsed_menuAnimation, menuChange_Animation, renderwindow, e, Main_menu_background, elapsed, clock);
							credits_Screen(renderwindow, e, clock, elapsed, Main_menu_background);
		
							selectOptSFX.playMusic();
		
							Main_menu_background.setColor(sf::Color(255, 255, 255, 255));
		
							Main_Menu_Title.setPosition(sf::Vector2f(870.0f, 35.0f));
							Main_Menu_Vertex.setPosition(sf::Vector2f(0.f, 0.f));
		
							S_StartButton.setPosition(sf::Vector2f(870.f, 451.f));
							S_CreditsButton.setPosition(sf::Vector2f(870.f, 581.f));
							S_QuitButton.setPosition(sf::Vector2f(870.f, 711.f));
		
							S_start_Text.setPosition(sf::Vector2f(980.f, 465.0f));
							S_credits_Text.setPosition(sf::Vector2f(965.f, 595.0f));
							S_quit_Text.setPosition(sf::Vector2f(1000.f, 725.0f));
						}
						break;
						case 1: //Play quit animation (Make a function within texture class)
						{
							selectOptSFX.playMusic();
							quitChangeScene_Animation(S_StartButton, S_CreditsButton, S_QuitButton, S_start_Text, S_credits_Text, S_quit_Text, Main_Menu_Title, Main_Menu_Vertex, elapsed_menuAnimation, menuChange_Animation, renderwindow, e, Main_menu_background, elapsed, clock);
							quit_Prompt(renderwindow, e, clock, elapsed, Message_Box, messagebox_Animation, elapsed_messagebox, Main_menu_background, yesBox, noBox);
		
							selectOptSFX.playMusic();
		
							Main_menu_background.setColor(sf::Color(255, 255, 255, 255));
		
							Main_Menu_Title.setPosition(sf::Vector2f(870.0f, 35.0f));
							Main_Menu_Vertex.setPosition(sf::Vector2f(0.f, 0.f));
		
							S_StartButton.setPosition(sf::Vector2f(870.f, 451.f));
							S_CreditsButton.setPosition(sf::Vector2f(870.f, 581.f));
							S_QuitButton.setPosition(sf::Vector2f(870.f, 711.f));
		
							S_start_Text.setPosition(sf::Vector2f(980.f, 465.0f));
							S_credits_Text.setPosition(sf::Vector2f(965.f, 595.0f));
							S_quit_Text.setPosition(sf::Vector2f(1000.f, 725.0f));
						}
						break;
						}
					}
				}
				if (e.type == sf::Event::Closed)
				{
					renderwindow.close();
				}
			}
			switch (menu_Option)
			{
			case 3: //Start arrows animation (Make a function within texture class)
			{
				S_StartButton.setColor(sf::Color(180, 180, 235, 255));
				S_CreditsButton.setColor(sf::Color(180, 180, 235, 150));
				S_QuitButton.setColor(sf::Color(180, 180, 235, 150));
		
				S_start_Text.setColor(sf::Color(180, 180, 235, 255));
				S_credits_Text.setColor(sf::Color(180, 180, 235, 150));
				S_quit_Text.setColor(sf::Color(180, 180, 235, 150));
		
				startArrow_Animation(leftBlue_Arrow, rightBlue_Arrow, elapsed_Animation, arrow_Animation);
			}
			break;
			case 2: //Credits arrows animation (Make a function within texture class)
			{
				S_StartButton.setColor(sf::Color(180, 180, 235, 150));
				S_CreditsButton.setColor(sf::Color(180, 180, 235, 255));
				S_QuitButton.setColor(sf::Color(180, 180, 235, 150));
		
				S_start_Text.setColor(sf::Color(180, 180, 235, 150));
				S_credits_Text.setColor(sf::Color(180, 180, 235, 2550));
				S_quit_Text.setColor(sf::Color(180, 180, 235, 150));
		
				creditsArrow_Animation(leftBlue_Arrow, rightBlue_Arrow, elapsed_Animation, arrow_Animation);
			}
			break;
			case 1: //Quit arrows animation (Make a function within texture class)
			{
				S_StartButton.setColor(sf::Color(180, 180, 235, 150));
				S_CreditsButton.setColor(sf::Color(180, 180, 235, 150));
				S_QuitButton.setColor(sf::Color(180, 180, 235, 255));
		
				S_start_Text.setColor(sf::Color(180, 180, 235, 150));
				S_credits_Text.setColor(sf::Color(180, 180, 235, 150));
				S_quit_Text.setColor(sf::Color(180, 180, 235, 255));
		
				quitArrow_Animation(leftBlue_Arrow, rightBlue_Arrow, elapsed_Animation, arrow_Animation);
			}
			break;
			}
			renderwindow.display();
		}
	}

	//

	void startArrow_Animation(Texture_System& leftBlue_Arrow, Texture_System& rightBlue_Arrow, sf::Time& elapsed_Animation, sf::Clock& arrow_Animation)
	{
		if (elapsed_Animation.asSeconds() < 1.5)
		{
			leftBlue_Arrow.setPosition(sf::Vector2f(850.f + (-25 * elapsed_Animation.asSeconds()), 440.0f));
			rightBlue_Arrow.setPosition(sf::Vector2f(1220.f - (-25 * elapsed_Animation.asSeconds()), 440.0f));

			leftBlue_Arrow.setColor(sf::Color(150, 180, 235, 255 - (elapsed_Animation.asSeconds() * 169.0f)));
			rightBlue_Arrow.setColor(sf::Color(150, 180, 235, 255 - (elapsed_Animation.asSeconds() * 169.0f)));
		}
		else
			arrow_Animation.restart();
	}
	void creditsArrow_Animation(Texture_System& leftBlue_Arrow, Texture_System& rightBlue_Arrow, sf::Time& elapsed_Animation, sf::Clock& arrow_Animation)
	{
		if (elapsed_Animation.asSeconds() < 1.5)
		{
			leftBlue_Arrow.setPosition(sf::Vector2f(850.f + (-25 * elapsed_Animation.asSeconds()), 570.0f));
			rightBlue_Arrow.setPosition(sf::Vector2f(1220.f - (-25 * elapsed_Animation.asSeconds()), 570.0f));

			leftBlue_Arrow.setColor(sf::Color(150, 180, 235, 255 - (elapsed_Animation.asSeconds() * 169)));
			rightBlue_Arrow.setColor(sf::Color(150, 180, 235, 255 - (elapsed_Animation.asSeconds() * 169)));
		}
		else
			arrow_Animation.restart();
	}
	void quitArrow_Animation(Texture_System& leftBlue_Arrow, Texture_System& rightBlue_Arrow, sf::Time& elapsed_Animation, sf::Clock& arrow_Animation)
	{
		if (elapsed_Animation.asSeconds() < 1.5)
		{
			leftBlue_Arrow.setPosition(sf::Vector2f(850.f + (-25 * elapsed_Animation.asSeconds()), 700.0f));
			rightBlue_Arrow.setPosition(sf::Vector2f(1220.f - (-25 * elapsed_Animation.asSeconds()), 700.0f));

			leftBlue_Arrow.setColor(sf::Color(150, 180, 235, 255 - (elapsed_Animation.asSeconds() * 169)));
			rightBlue_Arrow.setColor(sf::Color(150, 180, 235, 255 - (elapsed_Animation.asSeconds() * 169)));
		}
		else
			arrow_Animation.restart();
	}

	void YesArrow_Animation(Texture_System& leftBlue_Arrow, Texture_System& rightBlue_Arrow, sf::Time& elapsed_Animation, sf::Clock& arrow_Animation)
	{
		if (elapsed_Animation.asSeconds() < 1.5)
		{
			leftBlue_Arrow.setPosition(sf::Vector2f(325.f + (-25 * elapsed_Animation.asSeconds()), 490.0f));
			rightBlue_Arrow.setPosition(sf::Vector2f(705.f - (-25 * elapsed_Animation.asSeconds()), 490.0f));

			leftBlue_Arrow.setColor(sf::Color(150, 180, 235, 255 - (elapsed_Animation.asSeconds() * 169)));
			rightBlue_Arrow.setColor(sf::Color(150, 180, 235, 255 - (elapsed_Animation.asSeconds() * 169)));
		}
		else
			arrow_Animation.restart();
	}
	void NoArrow_Animation(Texture_System& leftBlue_Arrow, Texture_System& rightBlue_Arrow, sf::Time& elapsed_Animation, sf::Clock& arrow_Animation)
	{
		if (elapsed_Animation.asSeconds() < 1.5)
		{
			leftBlue_Arrow.setPosition(sf::Vector2f(825.f + (-25 * elapsed_Animation.asSeconds()), 490.0f));
			rightBlue_Arrow.setPosition(sf::Vector2f(1205.f - (-25 * elapsed_Animation.asSeconds()), 490.0f));

			leftBlue_Arrow.setColor(sf::Color(150, 180, 235, 255 - (elapsed_Animation.asSeconds() * 169)));
			rightBlue_Arrow.setColor(sf::Color(150, 180, 235, 255 - (elapsed_Animation.asSeconds() * 169)));
		}
		else
			arrow_Animation.restart();
	}

	void startChangeScene_Animation(Texture_System& startb, Texture_System& creditsb, Texture_System& quitb, Texture_System& startT, Texture_System& creditsT, Texture_System& quitT, Texture_System& mainmenuT, Texture_System& mainmenuV, sf::Time& sceneelapsed, sf::Clock& menuchange_Anim, sf::RenderWindow& renderwindow, sf::Event& e, Texture_System& background, sf::Time& elapsedB, sf::Clock& clock)
	{
		sf::Clock startbuttonblue;
		sf::Time blue_Elapsed;

		menuchange_Anim.restart();
		sceneelapsed = menuchange_Anim.getElapsedTime();

		startb.setColor(sf::Color(50, 15, 225, 255));
		startT.setColor(sf::Color(50, 15, 225, 255));

		while (sceneelapsed.asSeconds() < 2 && renderwindow.isOpen())
		{
			sceneelapsed = menuchange_Anim.getElapsedTime();
			elapsedB = clock.getElapsedTime();

			while (renderwindow.pollEvent(e))
			{
				if (e.type == sf::Event::Closed)
					renderwindow.close();
			}

			mainmenuT.setPosition(sf::Vector2f(870.0f + (-1955 * sceneelapsed.asSeconds()), 35.0f));
			mainmenuV.setPosition(sf::Vector2f(0.f + (-1955 * sceneelapsed.asSeconds()), 0.f));

			background.setPosition(sf::Vector2f(-40 * elapsedB.asSeconds(), 0));

			if (sceneelapsed.asSeconds() > 1)
			{
				startbuttonblue.restart();

				while (blue_Elapsed.asSeconds() < 1.2)
				{
					elapsedB = clock.getElapsedTime();

					blue_Elapsed = startbuttonblue.getElapsedTime();
					renderwindow.clear();

					startb.setPosition(sf::Vector2f(870.f - (2110 * blue_Elapsed.asSeconds()), 451.0f));
					startT.setPosition(sf::Vector2f(980.f - (2110 * blue_Elapsed.asSeconds()), 465.0f));

					background.setPosition(sf::Vector2f(-40 * elapsedB.asSeconds(), 0));


					startb.setColor(sf::Color(50, 15, 255, 255 - (blue_Elapsed.asSeconds() * 185)));
					startT.setColor(sf::Color(50, 15, 255, 255 - (blue_Elapsed.asSeconds() * 185)));

					background.draw(renderwindow);

					startb.draw(renderwindow);
					startT.draw(renderwindow);

					renderwindow.display();
				}
			}
			creditsb.setPosition(sf::Vector2f(870.f + (-1955 * sceneelapsed.asSeconds()), 581.0f));
			quitb.setPosition(sf::Vector2f(870.f + (-1955 * sceneelapsed.asSeconds()), 711.0f));

			creditsT.setPosition(sf::Vector2f(965.f + (-1955 * sceneelapsed.asSeconds()), 595.0f));
			quitT.setPosition(sf::Vector2f(1000.f + (-1955 * sceneelapsed.asSeconds()), 725.0f));

			renderwindow.clear();

			background.draw(renderwindow);

			mainmenuT.draw(renderwindow);
			mainmenuV.draw(renderwindow);

			startb.draw(renderwindow);
			creditsb.draw(renderwindow);
			quitb.draw(renderwindow);

			startT.draw(renderwindow);
			creditsT.draw(renderwindow);
			quitT.draw(renderwindow);

			renderwindow.display();
		}
		mainmenuT.setPosition(sf::Vector2f(870.0f, 35.0f));
		mainmenuV.setPosition(sf::Vector2f(0.f, 0.f));

		startb.setPosition(sf::Vector2f(870.f, 451.f));
		creditsb.setPosition(sf::Vector2f(870.f, 581.f));
		quitb.setPosition(sf::Vector2f(870.f, 711.f));

		startT.setPosition(sf::Vector2f(980.f, 465.0f));
		creditsT.setPosition(sf::Vector2f(965.f, 595.0f));
		quitT.setPosition(sf::Vector2f(1000.f, 725.0f));
	}
	void creditsChangeScene_Animation(Texture_System& startb, Texture_System& creditsb, Texture_System& quitb, Texture_System& startT, Texture_System& creditsT, Texture_System& quitT, Texture_System& mainmenuT, Texture_System& mainmenuV, sf::Time& sceneelapsed, sf::Clock& menuchange_Anim, sf::RenderWindow& renderwindow, sf::Event& e, Texture_System& background, sf::Time& elapsedB, sf::Clock& clock)
	{
		sf::Clock startbuttonblue;
		sf::Time blue_Elapsed;

		menuchange_Anim.restart();
		sceneelapsed = menuchange_Anim.getElapsedTime();

		creditsb.setColor(sf::Color(50, 15, 225, 255));
		creditsT.setColor(sf::Color(50, 15, 225, 255));

		while (sceneelapsed.asSeconds() < 2 && renderwindow.isOpen())
		{
			sceneelapsed = menuchange_Anim.getElapsedTime();
			elapsedB = clock.getElapsedTime();

			while (renderwindow.pollEvent(e))
			{
				if (e.type == sf::Event::Closed)
					renderwindow.close();
			}

			mainmenuT.setPosition(sf::Vector2f(870.0f + (-1955 * sceneelapsed.asSeconds()), 35.0f));
			mainmenuV.setPosition(sf::Vector2f(0.f + (-1955 * sceneelapsed.asSeconds()), 0.f));

			background.setPosition(sf::Vector2f(-40 * elapsedB.asSeconds(), 0));

			if (sceneelapsed.asSeconds() > 1)
			{
				startbuttonblue.restart();

				while (blue_Elapsed.asSeconds() < 1.2)
				{
					elapsedB = clock.getElapsedTime();

					blue_Elapsed = startbuttonblue.getElapsedTime();
					renderwindow.clear();

					creditsb.setPosition(sf::Vector2f(870.f - (2110 * blue_Elapsed.asSeconds()), 581.0f));
					creditsT.setPosition(sf::Vector2f(980.f - (2110 * blue_Elapsed.asSeconds()), 595.0f));

					background.setPosition(sf::Vector2f(-40 * elapsedB.asSeconds(), 0));

					creditsb.setColor(sf::Color(50, 15, 225, 255 - (blue_Elapsed.asSeconds() * 185)));
					creditsT.setColor(sf::Color(50, 15, 225, 255 - (blue_Elapsed.asSeconds() * 185)));

					background.draw(renderwindow);

					creditsb.draw(renderwindow);
					creditsT.draw(renderwindow);

					renderwindow.display();
				}
			}
			startb.setPosition(sf::Vector2f(870.f + (-1955 * sceneelapsed.asSeconds()), 451.0f));
			quitb.setPosition(sf::Vector2f(870.f + (-1955 * sceneelapsed.asSeconds()), 711.0f));

			startT.setPosition(sf::Vector2f(965.f + (-1955 * sceneelapsed.asSeconds()), 465.0f));
			quitT.setPosition(sf::Vector2f(1000.f + (-1955 * sceneelapsed.asSeconds()), 725.0f));

			renderwindow.clear();

			background.draw(renderwindow);

			mainmenuT.draw(renderwindow);
			mainmenuV.draw(renderwindow);

			startb.draw(renderwindow);
			creditsb.draw(renderwindow);
			quitb.draw(renderwindow);

			startT.draw(renderwindow);
			creditsT.draw(renderwindow);
			quitT.draw(renderwindow);

			renderwindow.display();
		}
		mainmenuT.setPosition(sf::Vector2f(870.0f, 35.0f));
		mainmenuV.setPosition(sf::Vector2f(0.f, 0.f));

		startb.setPosition(sf::Vector2f(870.f, 451.f));
		creditsb.setPosition(sf::Vector2f(870.f, 581.f));
		quitb.setPosition(sf::Vector2f(870.f, 711.f));

		startT.setPosition(sf::Vector2f(980.f, 465.0f));
		creditsT.setPosition(sf::Vector2f(965.f, 595.0f));
		quitT.setPosition(sf::Vector2f(1000.f, 725.0f));
	}
	void quitChangeScene_Animation(Texture_System& startb, Texture_System& creditsb, Texture_System& quitb, Texture_System& startT, Texture_System& creditsT, Texture_System& quitT, Texture_System& mainmenuT, Texture_System& mainmenuV, sf::Time& sceneelapsed, sf::Clock& menuchange_Anim, sf::RenderWindow& renderwindow, sf::Event& e, Texture_System& background, sf::Time& elapsedB, sf::Clock& clock)
	{
		sf::Clock startbuttonblue;
		sf::Time blue_Elapsed;

		menuchange_Anim.restart();
		sceneelapsed = menuchange_Anim.getElapsedTime();

		quitb.setColor(sf::Color(50, 15, 225, 255));
		quitT.setColor(sf::Color(50, 15, 225, 255));

		while (sceneelapsed.asSeconds() < 2 && renderwindow.isOpen())
		{
			sceneelapsed = menuchange_Anim.getElapsedTime();
			elapsedB = clock.getElapsedTime();

			while (renderwindow.pollEvent(e))
			{
				if (e.type == sf::Event::Closed)
					renderwindow.close();
			}

			mainmenuT.setPosition(sf::Vector2f(870.0f + (-1955 * sceneelapsed.asSeconds()), 35.0f));
			mainmenuV.setPosition(sf::Vector2f(0.f + (-1955 * sceneelapsed.asSeconds()), 0.f));

			background.setPosition(sf::Vector2f(-40 * elapsedB.asSeconds(), 0));

			if (sceneelapsed.asSeconds() > 1)
			{
				startbuttonblue.restart();

				while (blue_Elapsed.asSeconds() < 1.2)
				{
					elapsedB = clock.getElapsedTime();

					blue_Elapsed = startbuttonblue.getElapsedTime();

					quitb.setPosition(sf::Vector2f(870.f - (2110 * blue_Elapsed.asSeconds()), 711.0f));
					quitT.setPosition(sf::Vector2f(1000.f - (2110 * blue_Elapsed.asSeconds()), 725.0f));

					background.setPosition(sf::Vector2f(-40 * elapsedB.asSeconds(), 0));

					quitb.setColor(sf::Color(50, 15, 225, 255 - (blue_Elapsed.asSeconds() * 185)));
					quitT.setColor(sf::Color(50, 15, 225, 255 - (blue_Elapsed.asSeconds() * 185)));

					renderwindow.clear();

					background.draw(renderwindow);

					quitb.draw(renderwindow);
					quitT.draw(renderwindow);

					renderwindow.display();
				}
			}

			startb.setPosition(sf::Vector2f(870.f + (-1955 * sceneelapsed.asSeconds()), 451.0f));
			creditsb.setPosition(sf::Vector2f(870.f + (-1955 * sceneelapsed.asSeconds()), 581.0f));

			startT.setPosition(sf::Vector2f(965.f + (-1955 * sceneelapsed.asSeconds()), 465.0f));
			creditsT.setPosition(sf::Vector2f(1000.f + (-1955 * sceneelapsed.asSeconds()), 595.0f));

			background.draw(renderwindow);

			mainmenuT.draw(renderwindow);
			mainmenuV.draw(renderwindow);

			startb.draw(renderwindow);
			creditsb.draw(renderwindow);
			quitb.draw(renderwindow);

			startT.draw(renderwindow);
			creditsT.draw(renderwindow);
			quitT.draw(renderwindow);

			renderwindow.display();
		}
	}

};
#endif // !_MENUSYSTEM_


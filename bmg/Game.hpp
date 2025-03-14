#pragma once

struct GLFWwindow;
namespace bmg {
	class Game : public bm::Game{
		typedef bm::Game Super;
	public:
		bm::Sprite			playerShip;
		//bm::SpriteBatch		bg;
	public:
							Game();
		virtual				~Game() {};

		static bmg::Game*	get();
		virtual void		input(GLFWwindow*win,double dt) override;
		virtual void		update(double dt) override;
		virtual void		draw() override;
	};
}
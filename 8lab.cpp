#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;

class Game {
public:	
	int w = 32, minesCount = 0, n = 0;
	int gridLogic[12][12];
	int gridView[12][12];
	bool isLose = false, isWin = false;

	void print(int mines) {

		minesCount = 0;
		isWin = false; isLose = false;
		for (int i = 1; i <= 10; i++)
			for (int j = 1; j <= 10; j++)
			{
				gridView[i][j] = 10;
				if (rand() % mines == 0) {
					gridLogic[i][j] = 9;			//ìèíû
					minesCount++;
				}
				else gridLogic[i][j] = 0;
			}

		for (int i = 1; i <= 10; i++)
			for (int j = 1; j <= 10; j++)
			{
				int n = 0;
				if (gridLogic[i][j] == 9) continue;
				if (gridLogic[i + 1][j] == 9) n++;
				if (gridLogic[i][j + 1] == 9) n++;
				if (gridLogic[i - 1][j] == 9) n++;
				if (gridLogic[i][j - 1] == 9) n++;
				if (gridLogic[i + 1][j + 1] == 9) n++;
				if (gridLogic[i - 1][j - 1] == 9) n++;
				if (gridLogic[i - 1][j + 1] == 9) n++;
				if (gridLogic[i + 1][j - 1] == 9) n++;
				gridLogic[i][j] = n;							//÷èñëà
			}
	}

	void open(int i, int j) {									//îòêðûòèå îáëàñòè
		n++;
		if ((i + 1) <= 10)
			if (gridView[i + 1][j] == 10 && gridLogic[i + 1][j] < 9) {
				gridView[i + 1][j] = gridLogic[i + 1][j];
				n++;
				if (gridLogic[i + 1][j] == 0)
					open(i + 1, j);
			}
		if ((j + 1) <= 10)
			if (gridView[i][j + 1] == 10 && gridLogic[i][j + 1] < 9) {
				gridView[i][j + 1] = gridLogic[i][j + 1];
				n++;
				if (gridLogic[i][j + 1] == 0)
					open(i, j + 1);
			}
		if ((i - 1) > 0)
			if (gridView[i - 1][j] == 10 && gridLogic[i - 1][j] < 9) {
				gridView[i - 1][j] = gridLogic[i - 1][j];
				n++;
				if (gridLogic[i - 1][j] == 0)
					open(i - 1, j);
			}
		if ((j - 1) > 0)
			if (gridView[i][j - 1] == 10 && gridLogic[i][j - 1] < 9) {
				gridView[i][j - 1] = gridLogic[i][j - 1];
				n++;
				if (gridLogic[i][j - 1] == 0)
					open(i, j - 1);
			}
	}

	void RUN() {
		int difficulty = 11;
		srand(time(0));

		RenderWindow app(VideoMode(550, 400), "Saper");

		Texture menuTexture1, menuTexture2, menuTexture3, restartTexture;
		menuTexture1.loadFromFile("D:\\àâòîêàä\\îîï\\saper8\\images/1.png");
		menuTexture2.loadFromFile("D:\\àâòîêàä\\îîï\\saper8\\images/2.png");
		menuTexture3.loadFromFile("D:\\àâòîêàä\\îîï\\saper8\\images/3.png");
		restartTexture.loadFromFile("D:\\àâòîêàä\\îîï\\saper8\\images/restart.png");
		Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), restart(restartTexture);
		int menuNum = 0;
		restart.setPosition(400, 30);
		menu1.setPosition(400, 100);
		menu2.setPosition(400, 170);
		menu3.setPosition(400, 240);

		Texture winT, loseT, nonT;
		winT.loadFromFile("D:\\àâòîêàä\\îîï\\saper8\\images/win.png");
		loseT.loadFromFile("D:\\àâòîêàä\\îîï\\saper8\\images/lose.png");
		nonT.loadFromFile("D:\\àâòîêàä\\îîï\\saper8\\images/non.png");
		Sprite win(winT), lose(loseT), non(nonT);

		win.setPosition(350, 350);
		lose.setPosition(350, 350);
		non.setPosition(350, 350);

		Texture t;
		t.loadFromFile("D:\\àâòîêàä\\îîï\\saper8\\images\\tiles.jpg");
		Sprite s(t);

		while (app.isOpen())
		{
			Vector2i pos = Mouse::getPosition(app);
			int x = pos.x / w;
			int y = pos.y / w;

			Event e;

			app.clear(Color::White);
			while (app.pollEvent(e))
			{
				if (e.type == Event::Closed)
					app.close();

				if (e.type == Event::MouseButtonPressed)
				{
					if (e.key.code == Mouse::Left)				//ëêì
					{
						if (menuNum == 1) { print(difficulty); }
						if (menuNum == 2) { difficulty = 10; print(difficulty); app.draw(non); }
						if (menuNum == 3) { difficulty = 8; print(difficulty); app.draw(non); }
						if (menuNum == 4) { difficulty = 5; print(difficulty); app.draw(non); }
						menuNum = 0;

						if (!isWin && !isLose)
						{
							if (gridView[x][y] == 10)
								n++;
							gridView[x][y] = gridLogic[x][y];

							if (gridView[x][y] == 9) {
								for (int i = 1; i <= 10; i++)
									for (int j = 1; j <= 10; j++)
										gridView[i][j] = gridLogic[i][j];
								isLose = true;
								app.draw(lose);
							}
							if (gridView[x][y] == 0) {
								open(x, y);
							}
							n = 0;

							if (n + minesCount == 100) {
								isWin = true;
								app.draw(win);
							}
						}


					}
					else if (e.key.code == Mouse::Right)		//ïêì
						gridView[x][y] = 11;
				}
			}

			for (int i = 1; i <= 10; i++)
				for (int j = 1; j <= 10; j++)
				{
					//gridView[i][j] = gridLogic[i][j];  //ïðîñìîòðåòü ïîëå
					s.setTextureRect(IntRect(gridView[i][j] * w, 0, w, w));
					s.setPosition(i*w, j*w);
					app.draw(s);
				}

			if (IntRect(400, 30, 100, 60).contains(Mouse::getPosition(app))) { menuNum = 1; }
			if (IntRect(400, 100, 100, 60).contains(Mouse::getPosition(app))) { menuNum = 2; }
			if (IntRect(400, 170, 100, 60).contains(Mouse::getPosition(app))) { menuNum = 3; }
			if (IntRect(400, 240, 100, 60).contains(Mouse::getPosition(app))) { menuNum = 4; }

			app.draw(restart);
			app.draw(menu1);
			app.draw(menu2);
			app.draw(menu3);

			app.display();

		}
	}

};



int main()
{
	Game newGame;
	newGame.RUN();
	return 0;
}

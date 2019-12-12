#include"CommonFunction.h"
#include"MainObject.h"
#include "ThreatsObject.h"
#include"ExplosionObject.h"
#undef main

SDL_Surface* g_object;

bool Init()
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
		{
			return false;
		}
		g_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
		if (g_screen == NULL)
		{
			return false;
		}
		return true;
	}



int main(int arc, char argv[])
{
	bool is_run_screen = true;
	int bkgn_x = 0;
	bool is_quit = false;
	if (Init() == false)
		return 0;
	g_background = SDLCommon::LoadImage("bg4800.png");
	if (g_background == NULL)
	{
		return 0;
	}
	SDLCommon::ApplySurface(g_background, g_screen, 0, 0);


	//Make Main Object
	MainObject Plane_Object;
	Plane_Object.SetRect(300, 420);
	bool ret= Plane_Object.LoadImg("plane_fly.png");
	if (!ret)
	{
		return 0;
	}

	//Init explosion object
	ExplosionObject exp_main;
	ret = exp_main.LoadImg("exp_main.png");
	exp_main.set_clip();
	if (ret == false) return 0;



	Plane_Object.Show(g_screen);
	
	//Make Threat Object
	ThreatObject* threats = new ThreatObject[NUM_THREATS];

	for (int t = 0; t < NUM_THREATS; t++)
	{
		ThreatObject* threat = (threats + t);
		if (threat)
		{
			ret = threat->LoadImg("af1.png");
			if (ret == false)
			{
				return 0;
			}

			int rand_y = rand() % 600;
			if (rand_y > SCREEN_HEIGHT - 100)
			{
				rand_y = SCREEN_HEIGHT * 0.3;
			}

			threat->SetRect(SCREEN_WIDTH + t * 400, rand_y);
			threat->set_x_val(3);

			AmoObject* p_amo = new AmoObject();
			threat->InitAmo(p_amo);
		}
	}
	

	while (!is_quit)
	{
		while(SDL_PollEvent(&g_event))
		{
			if (g_event.type == SDL_QUIT)
			{
				is_quit = true;
				break;
			}
			Plane_Object.HandleInputAction(g_event);
		}

		// Apply Background

		if (is_run_screen == true)
		{
			bkgn_x -= 2;
			if (bkgn_x <= -(BACKGROUND_WIDTH - SCREEN_WIDTH))
			{
				is_run_screen = false;
			}
			else
			{
				SDLCommon::ApplySurface(g_background, g_screen, bkgn_x , 0);
			}
		}
		else
		{
			SDLCommon::ApplySurface(g_background, g_screen, bkgn_x, 0);
		}

		//Implement main objects
		Plane_Object.Show(g_screen);
		Plane_Object.HandleMove();
		Plane_Object.MakeAmo(g_screen);
		
		

		// Init Threats

		for (int tt = 0; tt < NUM_THREATS; tt++)
		{
			ThreatObject* threat = (threats + tt);
			if (threat)
			{
				threat->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
				threat->Show(g_screen);
				threat->MakeAmo(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
			
				if (SDL_Flip(g_screen) == -1)
					return 0;
				
				//check collision main and threats
				bool is_col = SDLCommon::CheckCollision(Plane_Object.GetRect(), threat->GetRect());
					if (is_col)
					{
						for (int exp = 0; exp < 4; exp++)
						{
							int x_pos = Plane_Object.GetRect().x + Plane_Object.GetRect().w * 0.5 - EXP_WIDTH * 0.5;
							int y_pos = Plane_Object.GetRect().y + Plane_Object.GetRect().h * 0.5 - EXP_HEIGHT * 0.5;

							exp_main.set_frame(exp);
							exp_main.SetRect(x_pos, y_pos);
							SDL_Delay(100);
							exp_main.Show(g_screen);
						
						
							if (SDL_Flip(g_screen) == -1)
								return 0;
						}


						if (MessageBox(NULL, L"Game Over!!!", L"Info", MB_OK) == IDOK)
						{
							delete[] threats;
							SDLCommon::CleanUp();
							SDL_Quit();
							return 1;
						}
				}

					std::vector<AmoObject*> amo_list = Plane_Object.GetAmoList();
					for (int im = 0; im < amo_list.size(); im++)
					{
						AmoObject* p_amo = amo_list.at(im);
						if (p_amo != NULL)
						{
							bool ret_col = SDLCommon::CheckCollision(p_amo->GetRect(), threat->GetRect());
							if (ret_col)
							{
								threat -> Reset(SCREEN_WIDTH + tt * 400);
								Plane_Object.RemoveAmo(im);
							}
						}
					}
			}
		}

		if (SDL_Flip(g_screen) == -1)
			return 0;
	}

	delete[] threats;
	SDLCommon::CleanUp();
	SDL_Quit();
	return 1;
}
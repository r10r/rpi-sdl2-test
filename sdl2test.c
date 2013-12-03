#include <SDL2/SDL.h>

int exit_counter = 1;

void exit_on_error(int result) {
	if (result != 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[%d]: %s", exit_counter, SDL_GetError());
		exit(exit_counter);
	} else {
		exit_counter++;
	}
}

int main ( int argc, char** argv )
{
	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "begin setup");

//	why is this not auto detected?
	SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengles");

	SDL_Window *sdlWindow;
	SDL_Renderer *sdlRenderer;

//	exit_on_error(SDL_Init(SDL_INIT_VIDEO));
	exit_on_error(SDL_Init(SDL_INIT_EVERYTHING));	// takes longer than only initializing video

	exit_on_error(SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP, &sdlWindow, &sdlRenderer));

	if (sdlWindow == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "sdlWindow is null: %s.", SDL_GetError());
		exit(1);
	}

	if (sdlRenderer == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "sdlRenderer is null %s.", SDL_GetError());
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "sdlRenderer is null %s.", SDL_GetHint(SDL_HINT_RENDER_DRIVER));
		exit(1);
	}

	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "setup completed");

	// see example in http://wiki.libsdl.org/SDL_RenderPresent

	// select BLACK for the background
	exit_on_error(SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255));
	// Clear the entire screen to our selected color.
	exit_on_error(SDL_RenderClear(sdlRenderer));


	// set RED for the rectangle
	exit_on_error(SDL_SetRenderDrawColor(sdlRenderer, 255, 0, 0, 255));
    SDL_Rect rectangle;
    rectangle.x = 200;
    rectangle.y = 200;
    rectangle.w = 200;
    rectangle.h = 200;
    exit_on_error(SDL_RenderFillRect(sdlRenderer, &rectangle));


	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "begin render");
    SDL_RenderPresent(sdlRenderer);
	SDL_Delay(5000);
	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "end render");

//	 won't work => message system is only available when using x11 output
//    exit_on_error(SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
//                             "Hello",
//                             "Hello Raspi!",
//                             sdlWindow));

//	is this required ?
	SDL_DestroyWindow(sdlWindow);
	SDL_Quit();
	return 0;

}
#ifndef USE_FLTK
#include "../inc/cli_interface.h"
#elif defined(USE_FLTK)
#include "../inc/gui_interface.h"
#endif


int main(int argc, char** argv)
{
#ifdef USE_FLTK
	return run_gui(argc, argv);
#else
	return run_cli();
#endif
}
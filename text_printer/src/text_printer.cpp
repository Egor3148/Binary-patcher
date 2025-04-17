#ifdef USE_FLTK

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>
#include <iostream>

#include "buffer.h"

int main(int argc, char** argv) {
    // Создаем окно
    Fl_Window* window = new Fl_Window(640, 480, "Buffer Content Viewer with Scroll");

    // Создаем скроллируемую область
    Fl_Scroll* scroll = new Fl_Scroll(0, 0, 640, 480);

    // Создаем буфер для текста и виджет для его отображения
    Fl_Text_Buffer* text_buf = new Fl_Text_Buffer();
    Fl_Text_Display* text_disp = new Fl_Text_Display(20, 20, 600, 440);
    text_disp->buffer(text_buf);  // Связываем буфер с виджетом
    text_disp->textfont(FL_COURIER);

    // Собираем содержимое буфера
    std::string buffer_content;
    int i = 3;
    while (i < BUFFER_SIZE &&
        !(buffer[i] == 's' &&
            buffer[i + 1] == 't' &&
            buffer[i + 2] == '>')) {
        buffer_content += buffer[i];
        ++i;
    }

    // Устанавливаем текст
    text_buf->text(buffer_content.c_str());

    scroll->end();
    window->end();
    window->show(argc, argv);

    return Fl::run();
}


#else

#include <iostream>
//#include <string>

#include "buffer.h"

using std::cin;
using std::cout;
using std::endl;


int main(int argc, char** argv)
{


	
	int i = 3;

	while(i < BUFFER_SIZE && 
		!(buffer[i] == 's' && 
		buffer[i+1] == 't' && 
		buffer[i+2] == '>'))
	{
		cout << buffer[i];
		++i;
	} 
	return 0;
}

#endif
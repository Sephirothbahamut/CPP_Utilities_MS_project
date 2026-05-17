#include <iostream>

#include "all.h"

namespace example::window
	{
	void all()
		{
		std::cout << "Base window"        "\npress [ESC] to go to the next example." << std::endl;
		base_window();
		std::cout << "Windowing system"   "\npress [ESC] to go to the next example." << std::endl;
		windowing_system();
		std::cout << "Input system"       "\npress [ESC] to go to the next example." << std::endl;
		input_system();
		std::cout << "Drawing system"     "\npress [ESC] to go to the next example." << std::endl;
		drawing_system();
		std::cout << "Fancy opengl wheel" "\npress [ESC] to go to the next example." << std::endl;
		//fancy_opengl_wheel();
		}
	}
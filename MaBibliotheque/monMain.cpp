#include "stdafx.h"
#include "monMain.h"
#include "Route.hpp"
#include <iostream>
#include "Draw.hpp"

int monMain()
{
	Route route = Route();

	SFML_output out;
	route.generation_automatique();
	route.draw(out.get_window());
	out.display(route);
	/*for (int32 i = 0; i < 10; ++i)
	{
		route.Update(out);
		route.draw(out);
		out.display();
	}*/

	return 0;
}
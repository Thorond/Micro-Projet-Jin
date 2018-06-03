#include "stdafx.h"
#include "monMain.h"
#include "Route.hpp"
#include <iostream>
#include "Draw.hpp"

int monMain()
{
	Route route = Route();

	SFML_output out;
	out.display(route);

	return 0;
}
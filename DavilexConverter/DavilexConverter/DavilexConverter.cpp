#include <iostream>

#include "d3d2obj.h"

int main(int argc, char* argv[])
{
	std::string file = "";
	if (argc < 2)
		file = OpenFileName();
	else
		file = argv[1];

	D3D convert;
	convert.Open(file);
}

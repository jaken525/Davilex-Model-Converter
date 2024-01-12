#include <iostream>
#include <filesystem>

#include "d3d2obj.h"
#include "obj2d3d.h"

int sequence[3] = { 0, 0, 0 };

int main(int argc, char* argv[])
{
	std::cout << "DAVILEX CONVERTER v0.2" << std::endl << std::endl;
	std::cout << "INFORMATION:" << std::endl;
	std::cout << "To display polygons correctly, enter the sequence of their recording.\nThe value should be from 0 to 2." <<
		"\nThe sequence is suitable for most models: 0 2 1.\nIf you have inverted polygons, it is most likely suitable: 1 2 0" << std::endl << std::endl;

	for (int i = 0; i < 3; i++)
	{ 
		int temp = -1;
		while (temp < 0 || temp > 2)
		{
			std::cout << "Enter " << i + 1 << " value: ";
			std::cin >> temp;
		}
		sequence[i] = temp;
	}

	std::cout << std::endl;

	std::string file = "";
	if (argc < 2)
		file = OpenFileName();
	else
		file = argv[1];

	if (file != "")
	{
		std::filesystem::path filePath = file;

		std::string extension = "";
		extension += filePath.extension().string()[1];
		extension += filePath.extension().string()[2];
		extension += filePath.extension().string()[3];

		if (extension == "d3d")
		{
			std::cout << "Using d3d2obj" << std::endl;

			D3D d3d2obj;
			d3d2obj.Open(file);
		}
		else if (extension == "obj")
		{
			std::cout << "Using obj2d3d" << std::endl;

			OBJ obj2d3d;
			obj2d3d.Open(file);
		}
		else
			std::cout << "Incorrect file format. If this is dc5 file change his extension to d3d..." << std::endl;
	}

	return 1;
}

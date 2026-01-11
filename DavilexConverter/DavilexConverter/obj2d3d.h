#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <iomanip>

#include "BinaryFileWork.h"
#include "parser.h"

extern int sequence[3];

struct OBJ
{
	int countVertices = 0;
	int countFaces = 0;

	std::vector<float> vertices;
	std::vector<float> textureVertices;
	std::vector<float> normals;

	OBJ()
	{
		vertices.clear();
		textureVertices.clear();
		normals.clear();
	}

	~OBJ()
	{
		vertices.clear();
		textureVertices.clear();
		normals.clear();
	}

	void Open(std::filesystem::path filePath)
	{
		if (filePath != "")
		{
			obj::ObjParser parser;
			parser.parse(filePath.string());

			std::string fname = filePath.stem().string();

			vertices = parser.GetVertices();
			textureVertices = parser.GetTextureVertices();
			normals = parser.GetNormals();

			countFaces = parser.GetFacesNumber();
			countVertices = parser.GetVerticiesNumber();

			std::ofstream file(fname + ".d3d", std::ios::binary);

			file << WriteLong(4294967295);
			file << WriteLong(countVertices);
			file << WriteLong(countFaces);

			for (int i = 0; i < countVertices; i++)
			{
				// vertices
				file << WriteFloat(vertices[i * 3]);
				file << WriteFloat(vertices[i * 3 + 1]);
				file << WriteFloat(vertices[i * 3 + 2]);

				// normals
				file << WriteFloat(normals[i * 3]);
				file << WriteFloat(normals[i * 3 + 1]);
				file << WriteFloat(normals[i * 3 + 2]);

				// texture vertices
				file << WriteFloat(textureVertices[i * 2]);
				file << WriteFloat(textureVertices[i * 2 + 1]);
				file << WriteFloat(1.0f);

				file << WriteFloat(1.0f);
				file << WriteFloat(1.0f);
				file << WriteFloat(1.0f);

				file << (char)0;
			}

			for (int i = 0; i < countFaces; ++i)
			{
				file << WriteShort(parser.verTriangles[i * 3 + sequence[0]]);
				file << WriteShort(parser.verTriangles[i * 3 + sequence[1]]);
				file << WriteShort(parser.verTriangles[i * 3 + sequence[2]]);
				file << WriteShort(0);

				file << (char)0;
			}

			file.close();
		}
	}

};
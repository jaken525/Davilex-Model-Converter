#include <filesystem>
#include <fstream>
#include <cstdio>

extern int sequence[3];

struct D3D
{
	bool isOriginal = true;

	uint32_t vertexCount = 0;
	uint32_t triangleCount = 0;

	float* vertices = NULL;
	float* normals = NULL;
	float* textureVertices = NULL;

	uint16_t* vertexEdge = NULL;
	uint16_t* normalEdge = NULL;

	D3D()
	{
		vertices = NULL;
		normals = NULL;
		textureVertices = NULL;
		vertexEdge = NULL;
		normalEdge = NULL;
	}

	~D3D()
	{
		if (vertices = NULL) delete[] vertices;
		if (normals = NULL) delete[] normals;
		if (textureVertices = NULL) delete[] textureVertices;
		if (vertexEdge = NULL) delete[] vertexEdge;
		if (normalEdge = NULL) delete[] normalEdge;
	}

	void Open(std::filesystem::path filePath)
	{
		std::FILE * fd = std::fopen(filePath.c_str(), "rb");
		if (fd)
		{
			size_t ptr = 0;
			Read(fd);
			WriteOBJ(filePath.parent_path().string() + std::filesystem::path::preferred_separator + filePath.stem().string() + ".obj");
		}
	}

	void Read(std::FILE * fd)
	{
		uint32_t size = 0;
		std::fread(&size, 1, sizeof(uint32_t), fd);
		if (size != 4294967295)
				std::fseek(fd, 0, SEEK_SET);

		std::fread((void *) &vertexCount, 1, sizeof(uint32_t), fd);
		std::fread((void *) &triangleCount, 1, sizeof(uint32_t), fd);

		if (vertexCount > 0 || triangleCount > 0)
		{
			vertices = new float[vertexCount * 3];
			normals = new float[vertexCount * 3];
			textureVertices = new float[vertexCount * 2];

			for (int i = 0; i < vertexCount; i++)
			{
				std::fread((void *) &vertices[i * 3], 1, sizeof(float), fd);
				std::fread((void *) &vertices[i * 3 + 1], 1, sizeof(float), fd);
				std::fread((void *) &vertices[i * 3 + 2], 1, sizeof(float), fd);

				std::fread((void *) &normals[i * 3], 1, sizeof(float), fd);
				std::fread((void *) &normals[i * 3 + 1], 1, sizeof(float), fd);
				std::fread((void *) &normals[i * 3 + 2], 1, sizeof(float), fd);

				std::fread((void *) &textureVertices[i * 2], 1, sizeof(float), fd);
				std::fread((void *) &textureVertices[i * 2 + 1], 1, sizeof(float), fd);

				std::fseek(fd, 17, SEEK_CUR);
			}

			normalEdge = new uint16_t[triangleCount];
			vertexEdge = new uint16_t[triangleCount * 3];

			for (int i = 0; i < triangleCount; i++)
			{
				std::fread((void *) &vertexEdge[i * 3], 1, sizeof(uint16_t), fd);
				std::fread((void *) &vertexEdge[i * 3 + 2], 1, sizeof(uint16_t), fd);
				std::fread((void *) &vertexEdge[i * 3 + 1], 1, sizeof(uint16_t), fd);
				std::fread((void *) &normalEdge[i], 1, sizeof(uint16_t), fd);

				std::fseek(fd, 1, SEEK_CUR);
			}
		}
		if(fd != NULL)
			std::fclose(fd);
	}

	void WriteOBJ(std::string file)
	{
		std::string line;
		std::ofstream obj(file.c_str());

		int fp = 6;
		if (obj.is_open()) 
		{
			for (int i = 0; i < vertexCount; i++)
			{
				obj << "v " << std::fixed << std::setprecision(fp);
				obj << vertices[(i * 3)] << " ";
				obj << vertices[(i * 3) + 1] << " ";
				obj << vertices[(i * 3) + 2] << std::endl;
			}

			for (int i = 0; i < vertexCount; i++)
			{
				obj << "vt " << std::fixed << std::setprecision(fp);
				obj << textureVertices[(i * 2)] << " ";
				obj << textureVertices[(i * 2) + 1] << std::endl;
			}

			for (int i = 0; i < vertexCount; i++)
			{
				obj << "vn " << std::fixed << std::setprecision(fp);
				obj << normals[(i * 3)] << " ";
				obj << normals[(i * 3) + 1] << " ";
				obj << normals[(i * 3) + 2] << std::endl;
			}

			for (int i = 0; i < triangleCount; i++)
			{
				obj << "f " << vertexEdge[(i * 3 + sequence[0])] + 1 << "/";
				obj << vertexEdge[(i * 3 + sequence[0])] + 1 << " ";

				obj << vertexEdge[(i * 3) + sequence[1]] + 1 << "/";
				obj << vertexEdge[(i * 3) + sequence[1]] + 1 << " ";

				obj << vertexEdge[(i * 3) + sequence[2]] + 1 << "/";
				obj << vertexEdge[(i * 3) + sequence[2]] + 1 << std::endl;
			}
			obj.close();
		}
		else
			std::cout << "Unable to open file";
	}
};
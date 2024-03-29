
#include "BinaryFileWork.h"

struct D3D
{
	bool isOriginal = true;

	uint32_t vertexCount = NULL;
	uint32_t triangleCount = NULL;

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

	void Open(std::string filePath)
	{
		char* buffer = NULL;
		size_t fsize = 0;
		if (OpenFile(buffer, fsize, filePath))
		{
			size_t ptr = 0;
			std::string fpath = GetFileNamePath(filePath);
			std::string fname = GetFileNameFile(filePath);

			Read(buffer, ptr, fsize, fpath, fname);
			WriteOBJ(fpath + fname + ".obj");
		}
		if (buffer != NULL)
		{
			delete[] buffer;
			buffer = NULL;
		}
	}

	void Read(char*& f, size_t& pos, size_t& fsize, std::string& fpath, std::string& fname)
	{
		uint32_t testModel = ReadLong(f, pos);
		if (testModel != 4294967295)
			pos = 0;

		vertexCount = ReadLong(f, pos);
		triangleCount = ReadLong(f, pos);

		if (vertexCount > 0 || triangleCount > 0)
		{
			vertices = new float[vertexCount * 3];
			normals = new float[vertexCount * 3];
			textureVertices = new float[vertexCount * 2];

			for (int i = 0; i < vertexCount; i++)
			{
				vertices[i * 3] = ReadFloat(f, pos);
				vertices[i * 3 + 1] = ReadFloat(f, pos);
				vertices[i * 3 + 2] = ReadFloat(f, pos);

				normals[i * 3] = ReadFloat(f, pos);
				normals[i * 3 + 1] = ReadFloat(f, pos);
				normals[i * 3 + 2] = ReadFloat(f, pos);

				textureVertices[i * 2] = ReadFloat(f, pos);
				textureVertices[i * 2 + 1] = ReadFloat(f, pos);

				pos += 17;
			}

			normalEdge = new uint16_t[triangleCount];
			vertexEdge = new uint16_t[triangleCount * 3];

			for (int i = 0; i < triangleCount; i++)
			{
				vertexEdge[i * 3] = ReadShort(f, pos);
				vertexEdge[i * 3 + 2] = ReadShort(f, pos);
				vertexEdge[i * 3 + 1] = ReadShort(f, pos);
				normalEdge[i] = ReadShort(f, pos);

				pos += 1;
			}
			if (f != NULL)
			{
				delete[] f;
				f = NULL;
				pos = 0;
			}

		}

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
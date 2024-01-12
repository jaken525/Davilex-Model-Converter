#include <iostream>
#include <vector>
#include <string>
#include <fstream>

namespace obj 
{
	class ObjParser 
	{
	public:
		std::vector<float> vx;
		std::vector<float> vy;
		std::vector<float> vz;
		std::vector<float> vnx;
		std::vector<float> vny;
		std::vector<float> vnz;
		std::vector<float> vtx;
		std::vector<float> vty;

		std::vector<std::string> fx;
		std::vector<std::string> fy;
		std::vector<std::string> fz;

		std::vector<int> verTriangles;
		std::vector<int> norTriangles;

		ObjParser() 
		{
			vx.clear();
			vy.clear();
			vz.clear();
			vnx.clear();
			vny.clear();
			vnz.clear();
			vtx.clear();
			vty.clear();
			fx.clear();
			fy.clear();
			fz.clear();
		}
		~ObjParser()
		{
			vx.clear();
			vy.clear();
			vz.clear();
			vnx.clear();
			vny.clear();
			vnz.clear();
			vtx.clear();
			vty.clear();
			fx.clear();
			fy.clear();
			fz.clear();
		}

		void parse(std::string path)
		{
			std::ifstream obj(path);

			std::string line = "";

			while (getline(obj, line))
			{
				int type = line[0] + line[1];

				switch (type)
				{
					//v
				case 150:
					VandVN(line, vx, vy, vz);
					break;

					//vt
				case 234:
					VT(line, vtx, vty);
					break;

					//vn
				case 228:
					VandVN(line, vnx, vny, vnz);
					break;

					//f
				case 134:
					F(line, fx, fy, fz);
					break;
				}
			}

			ConvertPolygons();

			obj.close();
		}

		int GetVerticiesNumber() 
		{
			return vx.size();
		}

		int GetTextureVerticiesNumber()
		{
			return vtx.size();
		}

		int GetNormalsNumber()
		{
			return vnx.size();
		}

		int GetFacesNumber()
		{
			return fx.size();
		}

		std::vector<std::string> GetFaces()
		{
			std::vector<std::string> faces;
			for (int i = 0; i < fx.size(); i++)
			{
				faces.push_back(fx[i]);
				faces.push_back(fy[i]);
				faces.push_back(fz[i]);
			}

			return faces;
		}

		std::vector<float> GetVertices()
		{
			std::vector<float> ver;
			for (int i = 0; i < vx.size(); i++)
			{
				ver.push_back(vx[i]);
				ver.push_back(vy[i]);
				ver.push_back(vz[i]);
			}

			return ver;
		}

		std::vector<float> GetTextureVertices()
		{
			std::vector<float> tex;
			for (int i = 0; i < vtx.size(); i++)
			{
				tex.push_back(vtx[i]);
				tex.push_back(vty[i]);
			}

			return tex;
		}

		std::vector<float> GetNormals()
		{
			std::vector<float> ver;
			for (int i = 0; i < vnx.size(); i++)
			{
				ver.push_back(vnx[i]);
				ver.push_back(vny[i]);
				ver.push_back(vnz[i]);
			}

			return ver;
		}

	private:

		void VandVN(std::string line, std::vector<float>& x, std::vector<float>& y, std::vector<float>& z)
		{
			int num = 1;
			int i = 0;
			std::string number = "";

			if (line[1] == 32)
				i = 2;
			else
				i = 3;

			for (i; i < line.length(); i++)
			{
				switch (num)
				{
				case 1:
					if (line[i] != 32)
						number += line[i];
					else
					{
						num++;
						x.push_back(stof(number));
						number = "";
					}
					break;

				case 2:
					if (line[i] != 32)
						number += line[i];
					else
					{
						num++;
						y.push_back(stof(number));
						number = "";
					}
					break;

				case 3:
					if (i != line.length() - 1)
						number += line[i];
					else
					{
						number += line[i];
						z.push_back(stof(number));
						number = "";
					}
					break;
				}
			}
		}

		void VT(std::string line, std::vector<float>& x, std::vector<float>& y)
		{
			std::vector<std::string> polygon;
			std::istringstream ist(line);
			std::string tmp;

			while (ist >> tmp)
				polygon.push_back(tmp);

			x.push_back(stof(polygon[1]));
			y.push_back(stof(polygon[2]));

			polygon.clear();
		}

		void F(std::string line, std::vector<std::string>& x, std::vector<std::string>& y, std::vector<std::string>& z)
		{
			std::vector<std::string> polygon;
			std::istringstream ist(line);
			std::string tmp;

			while (ist >> tmp)
				polygon.push_back(tmp);

			x.push_back(polygon[1]);
			y.push_back(polygon[2]);
			z.push_back(polygon[3]);

			polygon.clear();
		}

		void ConvertPolygons()
		{
			std::vector<std::string> polygons = GetFaces();

			for (int i = 0; i < polygons.size(); i++)
			{
				std::string tempFace = "";

				for (int k = 0; k < size(polygons[i]); k++)
					if (polygons[i][k] != '/')
						tempFace += polygons[i][k];
					else
					{
						verTriangles.push_back(stoi(tempFace) - 1);

						tempFace = "";
						break;
					}
			}

			polygons.clear();
		}

	};
}
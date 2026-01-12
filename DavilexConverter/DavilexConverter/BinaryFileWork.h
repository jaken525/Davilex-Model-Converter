#include <stdio.h>
#include <sstream>
#include <string>
#include <cstring>
#ifdef _WIN32
	#include <windows.h>
	#include <shlwapi.h>
	#include <algorithm>


	std::string OpenFileName(HWND owner = NULL, uint32_t flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY)
	{
		std::string filename(MAX_PATH, '\0');
		OPENFILENAME ofn = { };

		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = owner;
		ofn.lpstrFilter = "Davilex Model (*.d3d)\0*.d3d\0Wavefront OBJ (*.obj)\0*.obj\0All Files (*.*)\0*.*\0";
		ofn.lpstrFile = &filename[0];
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrTitle = "Select a File";
		ofn.Flags = flags;

		if (!GetOpenFileName(&ofn))
			return "";

		std::replace(filename.begin(), filename.end(), '\\', '/');
		return filename;
	}
#endif

std::string WriteShort(int num)
{
	int arr[] = { 0, 0 };
	while (num >= 256)
	{
		arr[1] += 1;
		num -= 256;
	}
	arr[0] = num;

	std::string hex;
	for (int i = 0; i < 2; i++)
		hex += char(arr[i]);

	return hex;
}

std::string WriteFloat(float num)
{
	std::string strHEX = "";
	unsigned long a = 0;
	unsigned long a24 = 0;
	float n = num;

	memcpy(&a, &n, 4);
	strHEX += char(uint8_t(a));
	strHEX += char((uint16_t(a) - uint8_t(a)) / 0x00000100);

	memcpy(&a24, &n, 3);
	strHEX += char((a24 - int(uint16_t(a))) / 0x00010000);
	strHEX += char((a - a24) / 0x01000000);

	return strHEX;
}

std::string WriteLong(int num)
{
	std::string Hex = "";
	std::stringstream s;
	s << std::hex << num;

	int zeroes = 8 - size(s.str());
	for (int i = 0; i < zeroes; i++)
		Hex += "0";
	Hex += s.str();

	int arr[] = { 0, 0, 0, 0 };
	int c = 3;
	for (int i = 0; i < Hex.length() - 1; i += 2)
	{
		std::stringstream h;
		h << Hex[i] << Hex[i + 1];
		h >> std::hex >> arr[c];
		c--;
	}

	Hex = "";
	for (int i = 0; i < 4; i++)
		Hex += char(uint8_t(arr[i]));

	return Hex;
}


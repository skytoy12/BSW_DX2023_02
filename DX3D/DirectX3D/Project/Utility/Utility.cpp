#include "Framework.h"
#include "Utility.h"

wstring Utility::GetExtention(wstring path)
{
	UINT index = path.find_last_of('.');
	return path.substr(index + 1, path.length());
}

string Utility::ToString(wstring str)
{
	string temp;

	temp.assign(str.begin(), str.end());

	return temp;
}

wstring Utility::ToWString(string str)
{
	wstring temp;

	temp.assign(str.begin(), str.end());

	return temp;
}

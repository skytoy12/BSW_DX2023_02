#include "Framework.h"
#include "Utility.h"

wstring Utility::GetExtention(wstring path)
{
	UINT index = path.find_last_of('.');
	return path.substr(index + 1, path.length());
}

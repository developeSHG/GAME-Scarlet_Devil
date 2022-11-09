#pragma once
template <typename T>
void SafeDelete(T& ptr)
{
	if (ptr)
	{
		delete ptr;
		ptr = nullptr;
	}
}

template <typename T>
void SafeDelete_Array(T& ptr)
{
	if (ptr)
	{
		delete[] ptr;
		ptr = nullptr;
	}
}

template <typename T>
DWORD SafeRelease(T& com)
{
	DWORD refcnt = com->Release();

	if (0 == refcnt)
		com = nullptr;

	return refcnt;
}
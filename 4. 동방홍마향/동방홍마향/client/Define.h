#pragma once

#define WINCX 800
#define WINCY 600
#define OBJ_DEAD 1
#define OBJ_NOEVENT 0

#define ERR_MSG(msg)					\
MessageBox(g_hWND, L"Error!", msg, MB_OK)


#define NULL_CHECK(ptr) \
if(nullptr == (ptr))	\
	return;

#define NULL_CHECK_MSG(ptr, msg)	\
if(nullptr == (ptr))				\
{									\
	ERR_MSG(msg);					\
	return;							\
}

#define NULL_CHECK_RETURN(ptr, returnVal)	\
if(nullptr == (ptr))						\
	return returnVal;

#define NULL_CHECK_MSG_RETURN(ptr, msg, returnVal)	\
if(nullptr == (ptr))								\
{													\
	ERR_MSG(msg);									\
	return returnVal;								\
}

#define FAILED_CHECK(hr)\
if(FAILED(hr))			\
	return;

#define FAILED_CHECK_MSG(hr, msg)	\
if(FAILED(hr))						\
{									\
	ERR_MSG(msg);					\
	return;							\
}

#define FAILED_CHECK_RETURN(hr, returnVal)	\
if(FAILED(hr))								\
	return returnVal;

#define FAILED_CHECK_MSG_RETURN(hr, msg, returnVal)	\
if(FAILED(hr))										\
{													\
	ERR_MSG(msg);									\
	return returnVal;								\
}


#define NO_COPY(ClassName)				\
private:								\
	ClassName(const ClassName& obj);	\
	ClassName& operator=(const ClassName& obj);

#define DECLARE_SINGLETON(ClassName)	\
		NO_COPY(ClassName)				\
public:									\
	static ClassName* GetInstance();	\
	static void DestroyInstance();				\
private:								\
	static ClassName* m_pInstance;

#define IMPLEMENT_SINGLETON(ClassName)			\
ClassName* ClassName::m_pInstance = nullptr;	\
ClassName* ClassName::GetInstance()				\
{												\
	if(nullptr == m_pInstance)					\
		m_pInstance = new ClassName;			\
	return m_pInstance;							\
}												\
void ClassName::DestroyInstance()				\
{												\
	if(m_pInstance)								\
	{											\
		delete m_pInstance;						\
		m_pInstance = nullptr;					\
	}											\
}
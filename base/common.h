#ifndef _THEFOX_BASE_TYPES_H_
#define _THEFOX_BASE_TYPES_H_

#ifdef WIN32
	#pragma warning(disable:4819)
	#pragma warning(disable:4996)
	#define snprintf _snprintf

	#if _MSC_VER < 1500 // MSVC 2008
		#define vsnprintf _vsnprintf
	#endif
#endif

// 简单类型定义
#if defined WIN32 && _MSC_VER < 1600 // MSVC 2010
	typedef __int8 int8_t;
	typedef __int16 int16_t;
	typedef __int32 int32_t;
	typedef __int64 int64_t;
	typedef unsigned __int8 uint8_t;
	typedef unsigned __int16 uint16_t;
	typedef unsigned __int32 uint32_t;
	typedef unsigned __int64 uint63_t;
#else
	#include <stdint.h>
	#define THEFOX_USE_CXX11
#endif

#include <assert.h>
#include <string>

#ifdef THEFOX_USE_CXX11
	#include <memory>
	#include <functional>
	using namespace std::placeholders; //std::bind可替换参数的占位符
#else
	#include <base/shared_ptr.h>
	#include <base/weak_ptr.h>
	#include <base/scoped_ptr.h>
	#include <base/function.h>
#endif

namespace thefox 
{

// 指定是否允许copy ctor 和 assign opt.
#undef THEFOX_DISALLOW_EVIL_CONSTRUCTORS
#define THEFOX_DISALLOW_EVIL_CONSTRUCTORS(TypeName)    \
  TypeName(const TypeName&);                           \
  void operator=(const TypeName&)

// 声明隐私转换
template<typename T>
inline T implicit_cast(T const &x) 
{
	return x;
}

// 安全删除对象
#define SAFE_DELETE(p)        \
    if (NULL != p) {          \
        delete p;             \
        p = NULL;             \
    }
    
// 安全删除对象数组
#define SAFE_DELETE_ARRAY(p)  \
    if (NULL != p) {          \
        delete []p;           \
        p = NULL;             \
    }

#define MIN(a,b) ((a)<(b)) ? (a) : (b)
#define MAX(a,b) ((a)>(b)) ? (a) : (b)

} // namespace thefox

#endif // _THEFOX_BASE_TYPES_H_
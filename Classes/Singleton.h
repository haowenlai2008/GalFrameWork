#pragma once
#include "cocos2d.h"
#include <type_traits>
using cocos2d::Ref;
template<class T>
class Singleton : public Ref
{
public:
	static T* getInstance()
	{
		if (ptr == nullptr)
		{
			ptr = new (std::nothrow)T();
			if (std::is_base_of<Ref, T>::value)
			{
				auto ptrRef = dynamic_cast<Ref*>(ptr);
				ptrRef->autorelease();
				ptrRef->retain();
			}
		}
		return ptr;
	}
	virtual ~Singleton() {};
protected:
	Singleton() {};
	static T* ptr;
};

template<class T>
T* Singleton<T>::ptr = nullptr;
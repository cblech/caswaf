#pragma once
#include <iostream>
#include "starStringEquals.h"

#define assert(a,b) if(a!=b) {std::cout<< "(" << #a << ") should be " << (b?"true":"false") << " and is " << (a?"true":"false") << std::endl; return false;}

bool starstringTest()
{
	assert(starstring("hi").equals("hi"), true);
	assert(starstring("hi4").equals("hi"), false);
	assert(starstring("").equals(""), true);
	assert(starstring("hi").equals(""), false);
	assert(starstring("").equals("hi"), false);


	assert(starstring("*").equals("hi"), true);
	assert(starstring("hi*").equals("hi"), false);
	assert(starstring("*hi").equals("hi"), false);
	assert(starstring("h*").equals("hi"), true);
	assert(starstring("h*i").equals("hi"), false);
	assert(starstring("*i").equals("hi"), true);
	assert(starstring("h*o").equals("hiho"), true);
	assert(starstring("h*a").equals("hiho"), false);
	assert(starstring("h*o").equals("hihaho"), true);
	assert(starstring("hi*o").equals("hiho"), true);
	assert(starstring("hi*o").equals("hihaho"), true);


	assert(starstring("*ih").equals("hiho"), false);
	assert(starstring("h*ih").equals("hiho"), false);
	assert(starstring("h*niho").equals("hiho"), false);
	assert(starstring("hih*ho").equals("hiho"), false);
	assert(starstring("hih").equals("hiho"), false);
	assert(starstring("iho").equals("hiho"), false);
	assert(starstring("hiho*hiho").equals("hiho"), false);


	assert(starstring("*i*").equals("hiho"), true);
	assert(starstring("h*o").equals("hiho"), true);
	assert(starstring("h*h*").equals("hiho"), true);
	assert(starstring("h*ho").equals("hihaho"), true);
	assert(starstring("h*ho*").equals("hihaho"), false);
	assert(starstring("*ho").equals("hihaho"), true);



	return true;
}
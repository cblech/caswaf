#pragma once
#include <boost/log/trivial.hpp>

//namespace lg = boost::log::trivial;

#define info BOOST_LOG_TRIVIAL(info)
#define warning BOOST_LOG_TRIVIAL(warning)
#define error BOOST_LOG_TRIVIAL(error)
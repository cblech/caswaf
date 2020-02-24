#pragma once
#include <boost/log/trivial.hpp>

//namespace lg = boost::log::trivial;

#define trace BOOST_LOG_TRIVIAL(trace)
#define debug BOOST_LOG_TRIVIAL(debug)
#define info BOOST_LOG_TRIVIAL(info)
#define warning BOOST_LOG_TRIVIAL(warning)
#define error BOOST_LOG_TRIVIAL(error)
#define fatal BOOST_LOG_TRIVIAL(fatal)
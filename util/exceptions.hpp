#pragma once

#include <stdexcept>


/**
 * IO Exception
 */
class IOException : public std::runtime_error {
public:
	/**
	 * Transparently constructs
	 * @param msg Message
	 */
	explicit IOException(const std::string &msg) : std::runtime_error(msg) {
		//
	}

};

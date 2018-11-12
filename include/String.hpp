#include <iostream>
#include <vector>
#include <sstream>

namespace String {
	/**
	 * @brief split give sentence with delimiter.
	 *
	 * @param sentence the sentence which you want to split.
	 * @param delimiter the sentence will be split every the delimiter.
	 *
	 * @return splited word.
	 *
	 * For example 
	 *
	 * sentence -> This is a good sentence
	 * delimiter -> :
	 *
	 * This sentence will be...
	 * ```
	 * This:is:a:good:sentence
	 * ```
	 *
	 * converted to 
	 * ```
	 * This
	 * is 
	 * a
	 * good
	 * sentence
	 * ```
	 *
	 */
	std::vector<std::string> split(const std::string sentence, const char delimiter);
} // namespace String

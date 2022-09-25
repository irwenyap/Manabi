#ifndef LOGGER_H
#define LOGGER_H

#include <string>

namespace Core {

	class Logger {
	public:
		Logger();
		~Logger();

		void LogInfo(std::string info);
		void LogError(std::string error);

	private:

	};

}

#endif // !LOGGER_H
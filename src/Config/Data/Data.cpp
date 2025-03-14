/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperthui <lperthui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:13:57 by lperthui          #+#    #+#             */
/*   Updated: 2025/03/14 15:37:08 by lperthui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Data.hpp"

Data::Data() {}

Data::Data(std::string configFile) {
	this->parseData(configFile);
	//std::cout << "Data constructed!" << std::endl;
	this->init();
	printData(*this);
}

Data::~Data() {}

void	Data::init() {
	std::vector<std::string> value;
	try {
		value = getValue("worker_processes", _data);
		_workerProcesses = atoi(value[1].c_str());
	}
	catch (std::exception & e) {
		
	}
}

void	Data::parseData(std::string configFile) {
	std::ifstream file(configFile.c_str());
	std::vector<Http> http;
	std::vector<Events> events;

	if (!file) {
		throw std::ios_base::failure("Error: Can't open file " + configFile);
	}

	char c;
	std::string buf;
	std::vector<std::string> content;

	while (file.get(c)) {
		if (c == '{') {
			content = split(buf);
			if (content[0] == "http")
				http.push_back(parseHttp(content, file));
			else if (content[0] == "events")
				events.push_back(parseEvents(content, file)); // coder parseEvent
			else
				throw std::logic_error("Error: config file: unrecognized argument: " + content[0]);
			buf = ""; // vide le buffer pour parser un nouvel element
		}
		else if (c == '}') {
			buf = ""; // vide le buffer pour parser un nouvel element
			return ;
		}
		else if (c == ';') {
			content = split(buf);
			_data[content[0]] = content;
			// Ajouter un element a la map
			buf = ""; // vide le buffer pour parser un nouvel element
		}
		else {
			buf += c;
		}
	}
	_http = http[0];
	_events = events[0];
}

// getters

unsigned int Data::getWorkerProcesses() {
	return _workerProcesses;
}

Http Data::getHttp() {
	return _http;
}
Events Data::getEvents() {
	return _events;
}

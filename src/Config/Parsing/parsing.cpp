/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperthui <lperthui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:11:53 by lperthui          #+#    #+#             */
/*   Updated: 2025/03/14 17:33:16 by lperthui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Data/Data.hpp"

std::vector<std::string>	split(std::string s) {
	std::stringstream			str(s);
	std::string					word;
	std::vector<std::string>	splited;

	while (str >> word) {
		splited.push_back(word);
	}

	return splited;
}

void	parseLimit(std::vector<std::string> key, std::ifstream &file) {
	// A coder
	char c;
	std::cout << "Coder parseLimit" << std::endl;
	while (file.get(c)) {
		if (c == '}') {
			return ;
		}
	}
	std::cout << "Error parsing" << std::endl;
}

Route	parseLocation(std::vector<std::string> key, std::ifstream &file) {
	std::map<std::string, std::vector<std::string> > data;
	std::map<std::string, std::string > fastCgiParam;

	char c;
	std::string buf;
	std::vector<std::string> content;

	std::string path;
	if (key.size() > 2 && key[1] == "=" && key.size() == 3) {
		path = key[2];
	}
	else if (key.size() == 2) {
		path = key[1];
	}
	else {
		throw std::logic_error("Invalid location.");
	}

	while (file.get(c)) {
		if (c == '{') {
			content = split(buf);
			if (content[0] == "limit_except")
				parseLimit(content, file); //Coder parsing de limit except
			else
				throw std::logic_error("Error: config file: unrecognized argument: " + content[0]);
			buf = ""; // vide le buffer pour parser un nouvel element
		}
		else if (c == '}') {
			buf = ""; // vide le buffer pour parser un nouvel element
			Route r(data, fastCgiParam, path);
			return r;
		}
		else if (c == ';') {
			content = split(buf);
			if (content[0] == "fastcgi_param") {
				if (content.size() != 3) {
					throw std::logic_error("fastcgi_param is invalid.");
				}
				fastCgiParam[content[1]] = content[2];
			}
			else {
				data[content[0]] = content;
				// Ajouter un element a la map
			}
			buf = ""; // vide le buffer pour parser un nouvel element
		}
		else {
			buf += c;
		}
	}
	std::cout << "Erreure lors du parsing" << std::endl;
	throw std::exception();
}

Server	parseServer(std::vector<std::string> key, std::ifstream &file) {
	std::map<std::string, std::vector<std::string> > data;

	char c;
	std::string buf;
	std::vector<std::string> content;
	std::vector<Route> routes;

	while (file.get(c)) {
		if (c == '{') {
			content = split(buf);
			if (content[0] == "location")
				routes.push_back(parseLocation(content, file));
			else
				throw std::logic_error("Error: config file: unrecognized argument: " + content[0]);
			buf = ""; // vide le buffer pour parser un nouvel element
		}
		else if (c == '}') {
			buf = ""; // vide le buffer pour parser un nouvel element
			Server s(data, routes);
			return s;
		}
		else if (c == ';') {
			content = split(buf);
			data[content[0]] = content;
			// Ajouter un element a la map
			buf = ""; // vide le buffer pour parser un nouvel element
		}
		else {
			buf += c;
		}
	}
	std::cout << "Erreure lors du parsing" << std::endl;
	throw std::exception();
}

Events	parseEvents(std::vector<std::string> key, std::ifstream &file) {
	std::map<std::string, std::vector<std::string> > data;

	char c;
	std::string buf;
	std::vector<std::string> content;

	while (file.get(c)) {
		if (c == '{') {
			content = split(buf);
			throw std::logic_error("Error: config file: unrecognized argument: " + content[0]);
			buf = ""; // vide le buffer pour parser un nouvel element
		}
		else if (c == '}') {
			buf = ""; // vide le buffer pour parser un nouvel element
			Events e(data);
			return e;
		}
		else if (c == ';') {
			content = split(buf);
			data[content[0]] = content;
			// Ajouter un element a la map
			buf = ""; // vide le buffer pour parser un nouvel element
		}
		else {
			buf += c;
		}
	}
	std::cout << "Erreure lors du parsing" << std::endl;
	throw std::exception();
}

Http	parseHttp(std::vector<std::string> key, std::ifstream &file) {
	std::map<std::string, std::vector<std::string> > data;

	char c;
	std::string buf;
	std::vector<std::string> content;
	std::vector<Server> servers;

	while (file.get(c)) {
		if (c == '{') {
			content = split(buf);
			if (content[0] == "server")
				servers.push_back(parseServer(content, file));
			else
				throw std::logic_error("Error: config file: unrecognized argument: " + content[0]);
			buf = ""; // vide le buffer pour parser un nouvel element
		}
		else if (c == '}') {
			buf = ""; // vide le buffer pour parser un nouvel element
			Http h(data, servers);
			return h;
		}
		else if (c == ';') {
			content = split(buf);
			data[content[0]] = content;
			// Ajouter un element a la map
			buf = ""; // vide le buffer pour parser un nouvel element
		}
		else {
			buf += c;
		}
	}
	std::cout << "Erreure lors du parsing" << std::endl;
	throw std::exception();
}

std::vector<std::string>	getValue(std::string key, std::map<std::string, std::vector<std::string> > data) {
	if (data.find(key) != data.end()) {
		return data[key];
	}
	throw std::logic_error("Key does not exist.");
}

void printData(Data d) {
	std::cout << "workerProcesses : " << d.getWorkerProcesses() << std::endl;
	std::cout << "Events : workerConnections : " << d.getEvents().getWorkerConnections() << std::endl;
	Http http = d.getHttp();
	std::cout << "Http : _serverName : " << http.getServerName() << std::endl;
	std::cout << "Http : _clientMaxBody : " << http.getClientMaxBody() << std::endl;
	for (int i = 0; i < http.getServers().size(); i++) {
		//Afficher routes
		Server s = http.getServers()[i];
		std::cout << "Server : _serverNames : ";
		for (int j = 0; j < s.getServerNames().size(); j++) {
			std::cout << s.getServerNames()[j] << " | ";
		}
		std::cout << std::endl << "Server : _listen : " << s.getListen() << std::endl;
		std::cout << "Server : _root : " << s.getRoot() << std::endl;
		// afficher _index
	}
}

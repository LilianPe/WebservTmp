/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperthui <lperthui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:11:53 by lperthui          #+#    #+#             */
/*   Updated: 2025/03/16 22:06:44 by lperthui         ###   ########.fr       */
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

int isInVector(std::vector<std::string> vector, std::string string) {
	for (int i = 0; i < vector.size(); i++) {
		if (vector[i] == string) {
			return 1;
		}
	}
	return 0;
}

Methods	parseLimit(std::vector<std::string> key, std::ifstream &file) {
	bool deny = 0;
	std::vector<std::string> clients;
	std::vector<std::string> methods;
	char c;
	std::string buf;
	std::vector<std::string> content;

	for (int i = 1; i < key.size(); i++) {
		if (key[i] != "GET" && key[i] != "POST" && key[i] != "DELETE" && key[i] != "PUT" && key[i] != "HEAD" && key[i] != "OPTIONS" && key[i] != "PATCH" && key[i] != "TRACE" && key[i] != "CONNECT") { // a ajuster en fonction des methods que l on veut enlever
			throw std::logic_error("Error: config file: unrecognized method: " + key[i]);
		}
		if (isInVector(methods, key[i])) {
			throw std::logic_error("Error: config file: method: " + key[i] + " specified twice.");
		}
		methods.push_back(key[i]);
	}

	while (file.get(c)) {
		if (c == '{') {
			content = split(buf);
			throw std::logic_error("Error: config file: unrecognized argument: " + content[0]);
			buf = ""; // vide le buffer pour parser un nouvel element
		}
		else if (c == '}') {
			buf = ""; // vide le buffer pour parser un nouvel element
			Methods m(methods, clients, deny);
			return m;
		}
		else if (c == ';') {
			content = split(buf);
			if (content.size() == 2 && content[0] == "deny" && content[1] == "all") {
				deny = 1;
			}
			else if (content.size() == 2 && content[0] == "allow") {
				clients.push_back(content[1]);
			}
			// Ajouter un element a la map
			buf = ""; // vide le buffer pour parser un nouvel element
		}
		else {
			buf += c;
		}
	}
	std::cout << "Erreure lors du parsing" << std::endl;
	throw std::exception();}

Route	parseLocation(std::vector<std::string> key, std::ifstream &file) {
	std::map<std::string, std::vector<std::string> > data;
	std::map<std::string, std::string > fastCgiParam;
	std::map<int, File> errorFiles;
	Methods method;
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
				method = parseLimit(content, file);
			else
				throw std::logic_error("Error: config file: unrecognized argument: " + content[0]);
			buf = ""; // vide le buffer pour parser un nouvel element
		}
		else if (c == '}') {
			buf = ""; // vide le buffer pour parser un nouvel element
			Route r(data, fastCgiParam, path, method, errorFiles);
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
			else if (content[0] == "error_page") {
				for (int i = 1; i < content.size() - 1; i++) {
					File file((content[content.size() - 1]));
					errorFiles[atoi(content[i].c_str())] = file;
				}
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
	std::map<int, File> errorFiles;

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
			Http h(data, servers, errorFiles);
			return h;
		}
		else if (c == ';') {
			content = split(buf);
			if (content[0] == "error_page") {
				for (int i = 1; i < content.size() - 1; i++) {
					File file((content[content.size() - 1]).substr(1), "/");
					errorFiles[atoi(content[i].c_str())] = file;
				}
			}
			else {
				data[content[0]] = content;
			}
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
	std::cout << "Http : _serverName : ";
	for (int i = 0; i < http.getServerName().size(); i++) {
		std::cout << http.getServerName()[i] << " | ";
	}
	std::cout << std::endl;
	std::cout << "Http : _errorFiles : ";
	for (int i = 0; i < http.getServerName().size(); i++) {
		for (std::map<int, File>::const_iterator it = http.getErrorFiles().begin(); it != http.getErrorFiles().end(); it++) {
			File f = it->second;
			std::cout << "Error : " << it->first << std::endl;
			std::cout << "File : _name : " << f.getName() << std::endl;
			std::cout << "File : _absolutePath : " << f.getAbsolutePath() << std::endl;
			std::cout << "File : _root : " << f.getRoot() << std::endl;
			std::cout << "File : _extension : " << f.getExtension() << std::endl;
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;
	std::cout << "Http : _clientMaxBody : " << http.getClientMaxBody() << std::endl;
	for (int i = 0; i < http.getServers().size(); i++) {
		Server s = http.getServers()[i];
		std::cout << "Server : _serverNames : ";
		for (int j = 0; j < s.getServerNames().size(); j++) {
			std::cout << s.getServerNames()[j] << " | ";
		}
		std::cout << std::endl << "Server : _listen : " << s.getListen() << std::endl;
		std::cout << std::endl << "Server : _clientMaxBodysize : " << s.getClientMaxBodysize() << std::endl;
		std::cout << "Server : _root : " << s.getRoot() << std::endl;
		for (int j = 0; j < s.getIndex().size(); j++) {
			File f = s.getIndex()[j];
			std::cout << "Server : File : _name : " << f.getName() << std::endl;
			std::cout << "Server : File : _absolutePath : " << f.getAbsolutePath() << std::endl;
			std::cout << "Server : File : _root : " << f.getRoot() << std::endl;
			std::cout << "Server : File : _extension : " << f.getExtension() << std::endl;
			std::cout << std::endl;
		}
		// afficher _index
		for (int j = 0; j < s.getRoutes().size(); j++) {
			Route r = s.getRoutes()[j];
			//afficher errorFiles / methods / extensios
			std::cout << "Route : _location : " << r.getLocation() << std::endl;
			std::cout << "Route : _root : " << r.getRoot() << std::endl;
			std::cout << "Route : _errorFiles : ";
			for (std::map<int, File>::const_iterator it = r.getErrorFiles().begin(); it != r.getErrorFiles().end(); it++) {
				File f = it->second;
				std::cout << "Error : " << it->first << std::endl;
				std::cout << "File : _name : " << f.getName() << std::endl;
				std::cout << "File : _absolutePath : " << f.getAbsolutePath() << std::endl;
				std::cout << "File : _root : " << f.getRoot() << std::endl;
				std::cout << "File : _extension : " << f.getExtension() << std::endl;
				std::cout << std::endl;
			}
			std::cout << std::endl;
			std::cout << "Route : _redirection : " << r.getRedirection() << std::endl;
			std::cout << "Route : _redirectionCode : " << r.getRedirectionCode() << std::endl;
			std::string c = r.getInternal() == 1 ? "true" : "false";
			std::cout << "Route : _internal : " << c << std::endl;
			c = r.getAutoIndex() == 1 ? "true" : "false";
			std::cout << "Route : _autoIndex : " << c << std::endl;
			std::cout << "Route : _fastcgiPass : " << r.getFastcgiPass() << std::endl;
			std::cout << "Route : _fastcgiIndex : " << r.getFastcgiIndex() << std::endl;
			std::cout << "Route : _fastcgiParams : key : ";
			for (std::map<std::string, std::string>::const_iterator it = r.getFastcgiParam().begin(); it != r.getFastcgiParam().end(); it++) {
				std::cout << it->first << " value : " << it->second << " | ";
			}
			std::cout << std::endl;
			std::cout << "Route : _include : ";
			for (std::vector<std::string>::const_iterator it = r.getInclude().begin(); it != r.getInclude().end(); it++) {
				std::cout << *it << " | ";
			}
			std::cout << std::endl;
			Methods m = r.getMethods();
			std::cout << "Route : Methods : _allowedMethods : ";
			for (std::vector<std::string>::const_iterator it = m.getAllowedMethods().begin(); it != m.getAllowedMethods().end(); it++) {
				std::cout << *it << " | ";
			}
			std::cout << std::endl;
			std::cout << "Route : Methods : _allowedClients : ";
			for (std::vector<std::string>::const_iterator it = m.getAllowedClients().begin(); it != m.getAllowedClients().end(); it++) {
				std::cout << *it << " | ";
			}
			std::cout << std::endl;
			std::cout << "Route : Methods : _deny : " << m.getDeny() << std::endl;
			std::cout << "Route : _clientBodyTempPath : " << r.getClientBodyTempPath() << std::endl;
			std::cout << "Route : _uploadMaxFilesize : " << r.getUploadMaxFilesize() << std::endl;
			std::cout << "Route : _clientMaxBodysize : " << r.getClientMaxBodysize() << std::endl;
			std::cout << std::endl;
			std::cout << std::endl;
		}
	}
}

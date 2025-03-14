/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Route.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperthui <lperthui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:58:20 by lperthui          #+#    #+#             */
/*   Updated: 2025/03/14 17:40:08 by lperthui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Route.hpp"

Route::Route() {}

Route::Route(std::map<std::string, std::vector<std::string> > data, std::map<std::string, std::string > fastcgiParam, std::string location) {
	// std::cout << "Route constructed!" << std::endl;
	// for (std::map<std::string, std::vector<std::string> >::iterator it = data.begin(); it != data.end(); it++) {
	// 	std::cout << "Key : " << it->first << " | Value : ";
	// 	printVector(it->second);
	// 	std::cout << std::endl;
	// }
	this->init(data, fastcgiParam, location);
}

Route::Route(const Route &route) {}

	Route::~Route() {}

//methods

void Route::init(std::map<std::string, std::vector<std::string> > data, std::map<std::string, std::string > fastcgiParam, std::string location) {
	// reste a init la liste de fichier d'erreure le default file et _files
	_location = location;
	// verifier avant que les parametres dans fastcgiParam sont valide
	_fastcgiParam = fastcgiParam;
	
	try {
		std::vector<std::string> value = getValue("root", data);
		if (value.size() < 2) {
			throw std::invalid_argument("Incomplete root.");
		}
		_root = value[1];
	}
	catch (std::logic_error & e) {
		_root = "";
	}
	
	try {
		std::vector<std::string> value = getValue("return", data);
		if (value.size() == 1) {
			throw std::logic_error("No value in return.");
		}
		else if (value.size() == 2) {
			_redirection = "";
		}
		else if (value.size() > 2){
			_redirection = value[2];
		}
		// reste a gerer si size() > 3
		_redirectionCode = atoi(value[1].c_str());
	}
	catch (std::logic_error & e) {
		_redirection = "";
		_redirectionCode = -1;
	}
	
	try {
		std::vector<std::string> value = getValue("internal", data);
		_internal = 1;
	}
	catch (std::logic_error & e) {
		_internal = 0;
	}
	
	try {
		std::vector<std::string> value = getValue("autoindex", data);
		if (value.size() < 2) {
			throw std::invalid_argument("Incomplete autoindex.");
		}
		if (value[1] == "on")
			_autoIndex = 1;
		else // gerer si ni on, ni off, ou si il n y a pas de param
			_autoIndex = 0;
	}
	catch (std::logic_error & e) {
		_autoIndex = 0;
	}

	try {
		std::vector<std::string> value = getValue("fastcgi_pass", data);
		if (value.size() < 2) {
			throw std::invalid_argument("Incomplete fastcgi_pass.");
		}
		_fastcgiPass = value[1];
	}
	catch (std::logic_error & e) {
		_fastcgiPass = "";
	}
	
	try {
		std::vector<std::string> value = getValue("fastcgi_index", data);
		if (value.size() < 2) {
			throw std::invalid_argument("Incomplete fastcgi_index.");
		}
		_fastcgiIndex = value[1];
	}
	catch (std::logic_error & e) {
		_fastcgiIndex = "";
	}
	
	try {
		std::vector<std::string> value = getValue("client_body_temp_path", data);
		if (value.size() < 2) {
			throw std::invalid_argument("Incomplete client_body_temp_path.");
		}
		_clientBodyTempPath = value[1];
	}
	catch (std::logic_error & e) {
		_clientBodyTempPath = ""; // voir si il faut une valeure par defaut
	}

	try {
		std::vector<std::string> value = getValue("include", data);
		for (int i = 1; i < value.size(); i++) {
			_include.push_back(value[i]);
		}
	}
	catch (std::logic_error & e) {
		
	}
}

//getters

std::map<std::string, File>		Route::getFiles() {
	return _files;
}

std::map<int, File>				Route::getErrorFiles() {
	return _errorFiles;
}

std::vector<std::string>		Route::getMethods() {
	return _methods;
}
std::vector<std::string>		Route::getAcceptedExtensions() {
	return _acceptedExtensions;
}

File							Route::getDefaultFile() {
	return _defaultFile;
}

std::string						Route::getLocation() {
	return _location;
}

std::string						Route::getRoot() {
	return _root;
}

std::string						Route::getRedirection() {
	return _redirection;
}

std::string						Route::getFastcgiPass() {
	return _fastcgiPass;
}

std::string						Route::getFastcgiIndex() {
	return _fastcgiIndex;
}

std::map<std::string, std::string>		Route::getFastcgiParam() {
	return _fastcgiParam;
}

std::vector<std::string>		Route::getInclude() {
	return _include;
}

std::string						Route::getClientBodyTempPath() {
	return _clientBodyTempPath;
}

int								Route::getRedirectionCode() {
	return _redirectionCode;
}

bool							Route::getInternal() {
	return _internal;
}

bool							Route::getAutoIndex() {
	return _autoIndex;
}
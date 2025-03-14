/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   File.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperthui <lperthui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:38:56 by lperthui          #+#    #+#             */
/*   Updated: 2025/03/14 15:37:25 by lperthui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "File.hpp"

File::File() {}

File::File(std::string name, std::string root) : _name(name), _root(root) {
	// reste a build absolute path et extension avec name et root
}

File::File(std::map<std::string, std::vector<std::string> > data) {
	// std::cout << "File constructed!" << std::endl;
	// for (std::map<std::string, std::vector<std::string> >::iterator it = data.begin(); it != data.end(); it++) {
	// 	std::cout << "Key : " << it->first << " | Value : ";
	// 	printVector(it->second);
	// 	std::cout << std::endl;
	// }
}

File::~File() {}

void printVector(std::vector<std::string> v) {
	std::vector<std::string>::iterator it = v.begin();
	it++;
	for(it; it < v.end(); it++) {
		std::cout << *it << std::endl;
	}
}

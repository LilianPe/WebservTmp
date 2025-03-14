/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   File.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperthui <lperthui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:39:16 by lperthui          #+#    #+#             */
/*   Updated: 2025/03/14 14:57:14 by lperthui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_HPP
# define FILE_HPP
# include <string>
# include <map>
# include <vector>
# include <string>
# include <fstream>
# include <sstream>
# include <iostream>
# include <exception>
# include <cstdlib>
# include "../Parsing/parsing.hpp"

class File {
	
	private:
		std::string _name;
		std::string _root;
		std::string _absolutePath;
		std::string _extension;
		
	public:
		File();
		File(std::string name, std::string root);
		File(std::map<std::string, std::vector<std::string> > data);
		~File();
};

void printVector(std::vector<std::string> v);

#endif

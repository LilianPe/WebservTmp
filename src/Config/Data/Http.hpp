/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Http.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperthui <lperthui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:55:45 by lperthui          #+#    #+#             */
/*   Updated: 2025/03/14 15:52:53 by lperthui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROUTES_HPP
# define ROUTES_HPP
# include <map>
# include <vector>
# include <string>
# include "Server.hpp"
# include "File.hpp"

class Http {

	private :
		std::vector<Server>	_servers;
		std::string			_serverName; // mettre un tableau de string pour stocker tous les noms du premier server
		Server				_defaultServer;
		std::map<int, File>	_errorFiles;
		std::string			_clientMaxBody;
	
	public :
		Http();
		Http(std::map<std::string, std::vector<std::string> > data, std::vector<Server> servers);
		~Http();

		// methods
		void init(std::map<std::string, std::vector<std::string> > data, std::vector<Server> servers);
		
		//getters
		std::vector<Server> getServers();
		std::string			getServerName();
		Server				getDefaultServer();
		std::map<int, File>	getErrorFiles();
		std::string			getClientMaxBody();
};

#endif
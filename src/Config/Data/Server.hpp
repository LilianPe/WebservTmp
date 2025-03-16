/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperthui <lperthui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:01:14 by lperthui          #+#    #+#             */
/*   Updated: 2025/03/16 22:08:31 by lperthui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP
# include <string>
# include <vector>
# include "Route.hpp"

class Server {
	private :
		std::vector<Route>			_routes;
		std::vector<std::string>	_serverNames;
		unsigned int				_listen;
		std::string					_clientMaxBodysize;
		std::string					_root;
		std::vector<File>			_index;
		// ajouter aussi _errorPages;
	
	public :
		Server();
		Server(std::map<std::string, std::vector<std::string> > data, std::vector<Route> routes);
		~Server();

		// methods
		void		init(std::map<std::string, std::vector<std::string> > data, std::vector<Route> routes);
		
		//getters
		std::vector<Route>			getRoutes();
		std::vector<std::string>	getServerNames();
		unsigned int				getListen();
		std::string					getClientMaxBodysize();
		std::string					getRoot();
		std::vector<File>			getIndex();
};

#endif
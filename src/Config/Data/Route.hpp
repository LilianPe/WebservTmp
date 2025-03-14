/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Route.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperthui <lperthui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:45:34 by lperthui          #+#    #+#             */
/*   Updated: 2025/03/14 17:18:23 by lperthui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROUTE_HPP
# define ROUTE_HPP
# include <map>
# include <vector>
# include <string>
# include "File.hpp"

class Route {

	private :
		std::map<std::string, File>				_files; // a init
		std::map<int, File>						_errorFiles; // a init
		std::vector<std::string>				_methods; // a init avec parseLimits()
		std::vector<std::string>				_acceptedExtensions; // a init une fois que les Files seront parse
		File									_defaultFile; // a init une fois que les files seront parse
		std::string								_location;
		std::string								_root;
		std::string								_redirection;
		int										_redirectionCode;
		bool									_internal;
		bool									_autoIndex;
		std::string								_fastcgiPass;
		std::string								_fastcgiIndex;
		std::map<std::string, std::string>		_fastcgiParam;
		std::vector<std::string>				_include;
		std::string								_clientBodyTempPath;
		//ajouter uploadMaxSize
		
		public :
		Route();
		Route(const Route &route);
		Route(std::map<std::string, std::vector<std::string> > data, std::map<std::string, std::string> fastcgiParam, std::string location);
		~Route();
		
		// methods
		void init(std::map<std::string, std::vector<std::string> > data, std::map<std::string, std::string> fastcgiParam, std::string location);

		// getters
		std::map<std::string, File>				getFiles();
		std::map<int, File>						getErrorFiles();
		std::vector<std::string>				getMethods();
		std::vector<std::string>				getAcceptedExtensions();
		File									getDefaultFile();
		std::string								getLocation();
		std::string								getRoot();
		std::string								getRedirection();
		int										getRedirectionCode();
		bool									getInternal();
		bool									getAutoIndex();
		std::string								getFastcgiPass();
		std::string								getFastcgiIndex();
		std::map<std::string, std::string>		getFastcgiParam();
		std::vector<std::string>				getInclude();
		std::string								getClientBodyTempPath();

};

#endif
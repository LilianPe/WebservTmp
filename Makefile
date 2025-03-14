NAME = webserv

OBJ = \
		src/main.o \
		src/Socket/WebservSocket.o \
		src/Socket/Socket.o \
		src/Request/Request.o \
		src/Response/Response.o \
		src/Config/Parsing/parsing.o \
		src/Config/Data/Data.o \
		src/Config/Data/File.o \
		src/Config/Data/Route.o \
		src/Config/Data/Server.o \
		src/Config/Data/Http.o \
		src/Config/Data/Events.o \

all: $(NAME)

$(NAME): $(OBJ)
	c++ $^ -o $@

%.o: %.cpp
	c++ -std=c++98 -g3 -c $^ -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re

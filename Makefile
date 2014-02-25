SRC	=main.cpp \
	 Window.cpp \
	 Mesh.cpp
EXT     =cpp
NAME	=gl
CXXFLAGS= -Wall -Wextra -W -std=c++0x
LDFLAGS	=-lGL -lX11 -DGLEW_STATIC /usr/lib/libGLEW.a
OBJS	= $(SRC:.$(EXT)=.o)
RM	= rm -f
CXX	= clang++
LINKER	= $(CXX)

all: $(NAME)

$(NAME): $(OBJS)
	$(LINKER) $(OBJS) $(LDFLAGS) -o $(NAME)

clean:
	$(RM) $(OBJS) *.swp *~ *#

fclean: clean
	$(RM) $(NAME)

re: make -B -j4

.PHONY: all clean fclean re


name = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
s:= welcome to 42-philo

sources = main.c init.c parse.c precise_usleep.c safe_write.c table.c
headers = philo.h
objects = $(sources:%.c=objs/%.o)

all: $(name) clean
	@echo $(GREEN) " - Compiling $(NAME)..." $(RESET)
	@echo $(YELLOW) " - Philos Ready" $(RESET)
	@echo "\033[36m        		        welcome to  			               	       \033[0m"
	@echo "\033[36m██╗  ██╗██████╗               ██████╗ ██╗  ██╗██╗██╗      ██████╗ ███████╗\033[0m"
	@echo "\033[36m██║  ██║╚════██╗              ██╔══██╗██║  ██║██║██║     ██╔═══██╗██╔════╝\033[0m"
	@echo "\033[36m███████║ █████╔╝    █████╗    ██████╔╝███████║██║██║     ██║   ██║███████╗\033[0m"
	@echo "\033[36m╚════██║██╔═══╝     ╚════╝    ██╔═══╝ ██╔══██║██║██║     ██║   ██║╚════██║\033[0m"
	@echo "\033[36m     ██║███████╗              ██║     ██║  ██║██║███████╗╚██████╔╝███████║\033[0m"
	@echo "\033[36m     ╚═╝╚══════╝              ╚═╝     ╚═╝  ╚═╝╚═╝╚══════╝ ╚═════╝ ╚══════╝\033[0m"
	@echo "\033[36m        		   by AbdulAzeez Shobajo                          \033[0m"

$(name): $(objects)
	@cc $(objects) -o $@
	@echo $(s)

objs:
	@mkdir -p objs

objs/%.o: %.c $(headers) | objs
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@-rm -f objs/*.o
	@-rm -rf objs

fclean:
	@rm -f $(name)

.PHONY: all clean fclean

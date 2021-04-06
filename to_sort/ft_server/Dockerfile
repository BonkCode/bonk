# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Dockerfile                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/15 16:26:33 by rtrant            #+#    #+#              #
#    Updated: 2020/08/15 20:07:00 by rtrant           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FROM debian:buster

LABEL maintainer="rtrant"

RUN apt-get -y update \
	&& apt-get -y install vim \
	&& apt-get -y install nginx \
	&& apt-get -y install mariadb-server \
	&& apt-get -y install php-fpm php-mysql \
	&& apt-get -y install wget \
	&& mkdir /var/www/ft_server \
	&& mkdir /var/www/ft_server/phpmyadmin

COPY ./srcs/init_container.sh ./
COPY ./srcs/nginx-conf /etc/nginx/sites-available/ft_server
COPY ./srcs/change-autoindex.sh /
COPY ./srcs/off /etc/nginx/sites-available
COPY ./srcs/phpmyadmin.inc.php /var/www/ft_server/phpmyadmin/config.inc.php
COPY ./srcs/wp-config.php ./tmp/wp-config.php

CMD bash init_container.sh
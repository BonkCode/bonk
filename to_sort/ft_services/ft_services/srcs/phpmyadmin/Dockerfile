FROM alpine:latest

RUN apk update
RUN apk add vim openrc bash
RUN apk add nginx 
RUN apk add php7-common php7-session php7-fpm php7-mbstring php7-mcrypt php7-soap php7-openssl php7-gmp php7-pdo_odbc php7-json php7-dom php7-pdo php7-zip php7-mysqli php7-sqlite3 php7-apcu php7-pdo_pgsql php7-bcmath php7-gd php7-odbc php7-pdo_mysql php7-pdo_sqlite php7-gettext php7-xmlreader php7-xmlrpc php7-bz2 php7-iconv php7-pdo_dblib php7-curl php7-ctype

# Install phpMyAdmin
RUN cd /var/www \
&& wget https://files.phpmyadmin.net/phpMyAdmin/5.0.1/phpMyAdmin-5.0.1-all-languages.tar.gz \
&& tar zxvf phpMyAdmin-5.0.1-all-languages.tar.gz \
&& rm phpMyAdmin-5.0.1-all-languages.tar.gz \
&& mv phpMyAdmin-5.0.1-all-languages phpmyadmin
RUN chmod -R 777 /var/www/phpmyadmin
COPY config.inc.php /var/www/phpmyadmin/
COPY setup_phpmyadmin.sh .

COPY nginx.conf /etc/nginx/nginx.conf

#EXPOSE 5000
CMD sh ./setup_phpmyadmin.sh
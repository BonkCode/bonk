FROM alpine:latest

# Lots of packages, thx php7
RUN apk update
RUN apk add --no-cache openrc vim nginx openssl
RUN apk add php7-common php7-session php7-fpm php7-mcrypt php7-soap php7-openssl php7-gmp php7-pdo_odbc php7-json php7-dom php7-pdo php7-zip php7-mysqli php7-sqlite3 php7-apcu php7-pdo_pgsql php7-bcmath php7-gd php7-odbc php7-pdo_mysql php7-pdo_sqlite php7-gettext php7-xmlreader php7-xmlrpc php7-bz2 php7-iconv php7-pdo_dblib php7-curl php7-ctype

# Installing wordpress
RUN wget http://wordpress.org/latest.tar.gz \
    && tar -xzvf latest.tar.gz -C /usr/share/ \
    && rm latest.tar.gz \
    && ln -s /usr/share/wordpress/ /var/www/wordpress
COPY wp-config.php /var/www/wordpress

# Nginx configuration
COPY nginx.conf /etc/nginx/nginx.conf
RUN chown -R nginx:nginx /var/www/wordpress \
    && chmod -R 777 /var/www/wordpress
RUN chown -R nginx:nginx /var/www \
    && chmod -R 777 /var/www

# Start services
COPY setup_wp.sh .
CMD ./setup_wp.sh

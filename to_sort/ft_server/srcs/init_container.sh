service mysql start

# Config Access
chown -R www-data /var/www/*
chmod -R 755 /var/www/*

# SSL
mkdir /etc/nginx/ssl
openssl req -newkey rsa:4096 -x509 -sha256 -days 365 -nodes -out /etc/nginx/ssl/ft_server.pem -keyout /etc/nginx/ssl/ft_server.key -subj "/C=RU/ST=Moscow/L=Moscow/O=21 School/OU=rtrant/CN=ft_server"

# Config NGINX
mv /etc/nginx/sites-available/ft_server /etc/nginx/sites-enabled/ft_server
rm -rf /etc/nginx/sites-enabled/default
rm -rf /etc/nginx/sites-available/default

# Config MYSQL
echo "CREATE DATABASE wordpress;" | mysql -u root --skip-password
echo "GRANT ALL PRIVILEGES ON wordpress.* TO 'root'@'localhost' WITH GRANT OPTION;" | mysql -u root --skip-password
echo "update mysql.user set plugin='mysql_native_password' where user='root';" | mysql -u root --skip-password
echo "FLUSH PRIVILEGES;" | mysql -u root --skip-password

# DL phpmyadmin
wget https://files.phpmyadmin.net/phpMyAdmin/4.9.0.1/phpMyAdmin-4.9.0.1-all-languages.tar.gz
tar -xvf phpMyAdmin-4.9.0.1-all-languages.tar.gz --strip-components 1 -C /var/www/ft_server/phpmyadmin

# DL wordpress
cd /tmp/
wget -c https://wordpress.org/latest.tar.gz
tar -xvzf latest.tar.gz
mv wordpress/ /var/www/ft_server
mv /tmp/wp-config.php /var/www/ft_server/wordpress

service php7.3-fpm start
service nginx start
bash
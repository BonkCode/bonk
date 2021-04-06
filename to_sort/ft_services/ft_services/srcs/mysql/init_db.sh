#! /bin/sh

# Using openrc init system
openrc boot
# Add mariadb to run-level sys-init
rc-update add mariadb
# Install MariaDB/MySQL database and create two accounts (root@localhost and mysql@localhost). Same as mysql_install_db, see MariaDB Knowledge Base about this command.
/etc/init.d/mariadb setup
# Start service as root
rc-service mariadb start

# Create database and set users inside mysql service
echo "CREATE DATABASE wordpress;" | mysql -u root --skip-password
#echo "SHOW DATABASES;" | mysql -u root --skip-password
echo "CREATE USER 'admin'@'%' identified by 'wp_admin';" | mysql -u root --skip-password
#echo "SELECT User FROM mysql.user;" | mysql -u root --skip-password
echo "GRANT ALL PRIVILEGES ON *.* TO 'admin'@'%' WITH GRANT OPTION;" | mysql -u root --skip-password 
#echo "SHOW GRANTS FOR 'admin'@localhost;" | mysql -u root --skip-password
mysql -u root --skip-password < wp_databases.sql

sleep infinity && wait

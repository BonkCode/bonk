#!/bin/sh

openrc boot
rc-update add vsftpd
rc-service vsftpd start
# Check if the server is up and running (response should be open)
nc -zv 127.0.0.1 21
# Create a group and user, add user to group (-S -> Create a system user, -G -> GRP, -h HOMEDIR)
addgroup -S ftps_group && adduser -S ftps_usr -G ftps_group -h /var/www
# Change password
echo "ftps_usr:ftps" | chpasswd
# Grant rights to user
chmod -R 777 /var/www
chown -R ftps_usr:ftps_group /var/www

# Start server
/usr/sbin/vsftpd /etc/vsftpd.conf

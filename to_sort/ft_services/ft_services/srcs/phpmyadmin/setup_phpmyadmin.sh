#!/bin/sh

openrc boot
rc-update add nginx
rc-service nginx restart
rc-update add php-fpm7
rc-service php-fpm7 restart
sleep infinity & wait
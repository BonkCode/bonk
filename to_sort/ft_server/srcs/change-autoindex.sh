mv /etc/nginx/sites-available/off /etc/nginx/sites-available/await
mv /etc/nginx/sites-enabled/ft_server /etc/nginx/sites-available/off
mv /etc/nginx/sites-available/await /etc/nginx/sites-enabled/ft_server
service nginx restart
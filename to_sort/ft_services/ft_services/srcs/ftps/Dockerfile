FROM alpine:latest

RUN apk add --no-cache vsftpd vim openrc openssl

COPY vsftpd.conf /etc/
COPY index.html /var/www/
COPY start.sh .

RUN openssl req -x509 -nodes -days 365 -newkey rsa:2048 -keyout /etc/ssl/private/ftps-selfsigned-rsa.key -out /etc/ssl/certs/ftps-selfsigned-rsa.crt -subj "/C=FR/L=Paris/O=42/CN=ft_services.com"

RUN chmod +x start.sh
CMD ./start.sh

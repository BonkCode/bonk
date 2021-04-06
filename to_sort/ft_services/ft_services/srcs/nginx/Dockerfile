FROM alpine:latest

RUN apk update
RUN apk add openrc --no-cache
RUN apk add nginx vim openssl openssh 

# Creating user and granting rights
RUN mkdir -p /run/nginx
RUN adduser -D -g 'www' www
RUN mkdir /www
RUN chown -R www:www /var/lib/nginx
RUN chown -R www:www /www

COPY web/* /www/

# Create SSL certificate
RUN openssl req -x509 -nodes -days 365 -newkey rsa:2048 -keyout /etc/ssl/private/nginx-selfsigned.key -out /etc/ssl/certs/nginx-selfsigned.crt -subj "/C=FR/L=Paris/O=42/CN=ft_services.com"

# Create SSH key
RUN mkdir -p /run/sshd
RUN adduser -D ssh_user
RUN echo "ssh_user:ssh_password"|chpasswd
RUN ssh-keygen -A

# Configure nginx & SSH server
COPY sshd_config /etc/ssh
COPY nginx.conf /etc/nginx

# Run ? SSH /!\ 
COPY start.sh .
RUN chmod +x start.sh
CMD sh ./start.sh

CMD ["nginx", "-g", "daemon off;"]

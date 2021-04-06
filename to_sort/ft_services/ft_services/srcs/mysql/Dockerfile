FROM alpine:latest

RUN apk add --no-cache vim mysql mysql-client openrc

COPY my.cnf /etc/my.cnf
COPY mariadb-server.cnf /etc/my.cnf.d/mariadb-server.cnf
COPY wp_databases.sql .
COPY init_db.sh .

CMD ./init_db.sh

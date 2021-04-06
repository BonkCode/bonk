FROM alpine:latest

RUN apk update
RUN apk add vim telegraf --repository http://dl-3.alpinelinux.org/alpine/edge/testing/ --allow-untrusted --no-cache

# Telegraf setup
RUN mkdir -p etc/telegraf
COPY telegraf.conf etc/telegraf/telegraf.conf
COPY start.sh .

CMD ./start.sh
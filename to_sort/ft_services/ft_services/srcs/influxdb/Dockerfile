FROM alpine:latest

RUN apk add --no-cache influxdb bash

COPY influxdb.conf etc/influxdb.conf
COPY start-services.sh .

ENTRYPOINT sh start-services.sh
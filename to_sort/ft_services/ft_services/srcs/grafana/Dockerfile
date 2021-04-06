FROM alpine:latest
 
RUN apk add --no-cache vim openrc

# Download standalone linux binaries
RUN apk add libc6-compat
RUN wget https://dl.grafana.com/oss/release/grafana-7.2.0.linux-amd64.tar.gz \
    && tar -zxvf grafana-7.2.0.linux-amd64.tar.gz \
    && rm -rf grafana-7.2.0.linux-amd64.tar.gz 

COPY provisioning/dashboards/ /grafana-7.2.0/conf/provisioning/dashboards/
COPY provisioning/providers.yaml /grafana-7.2.0/conf/provisioning/dashboards/
COPY provisioning/datasources.yaml /grafana-7.2.0/conf/provisioning/datasources/
 
COPY start.sh .

CMD ./start.sh
#! /bin/sh

# Start Minikube with VirtualBox 

minikube delete
minikube start --cpus=2 --memory 2200 --driver=virtualbox
minikube addons enable metrics-server
minikube addons enable dashboard
minikube addons enable metallb

# Stock cluster's ip address
MKB_IP=`minikube ip`;
echo "Minikube ip address = $MKB_IP"

# Docker containers
eval $(minikube docker-env)
docker build -t nginx srcs/nginx
docker build -t mysql srcs/mysql
docker build -t wordpress srcs/wordpress
docker build -t phpmyadmin srcs/phpmyadmin
docker build -t ftps srcs/ftps
docker build -t influxdb srcs/influxdb
docker build -t telegraf srcs/telegraf
docker build -t grafana srcs/grafana

# Deployments and Services
kubectl apply -f srcs/metallb-configmap.yaml
kubectl apply -f srcs/nginx/nginx.yaml
kubectl apply -f srcs/mysql/mysql.yaml
kubectl apply -f srcs/wordpress/wordpress.yaml
kubectl apply -f srcs/phpmyadmin/phpmyadmin.yaml
kubectl apply -f srcs/ftps/ftps.yaml
kubectl apply -f srcs/influxdb/influxdb.yaml
kubectl apply -f srcs/telegraf/telegraf.yaml
kubectl apply -f srcs/grafana/grafana.yaml

# Make Minikube launch the Web Dashboard everytime the Minikube VM starts
minikube dashboard

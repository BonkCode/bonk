#!/bin/sh

kubectl delete -f .
eval $(minikube docker-env)
docker build -t wordpress .
kubectl apply -f .
sleep 5
kubectl get all

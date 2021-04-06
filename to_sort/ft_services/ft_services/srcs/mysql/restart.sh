#!/bin/sh

kubectl delete -f .
eval $(minikube docker-env)
docker build -t mysql .
kubectl apply -f .
sleep 5
kubectl get all

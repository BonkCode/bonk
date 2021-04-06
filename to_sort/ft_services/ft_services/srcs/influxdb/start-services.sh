#!/bin/sh

# Start influxdb, create files /var/lib/infludb/meta ../data & ../wal, modify ownership
influxd run -config /etc/influxdb.conf
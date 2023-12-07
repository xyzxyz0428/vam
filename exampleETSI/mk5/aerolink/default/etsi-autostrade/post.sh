#!/bin/sh
# Update for VW Root (56F8D93822B46B0E)

set -x

# VW Root in ECTL, but CRL from here
wget http://eu.rep.c2x.vwg-connect.com/dc/getcrl/56F8D93822B46B0E
crladm import --etsiCrl 56F8D93822B46B0E

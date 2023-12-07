#!/bin/sh
# Update for AtoS 'EU' L0 PKI Root CA (D875151DE8A41EBD)
# https://0.eu-op.l0.c-its-pki.eu/
# https://0.eu-dc.l0.c-its-pki.eu/

# CA is in the ECTL
./fetch-cpoc.sh

set -x

# Get CRL/CTL for this CA
wget --no-verbose https://0.eu-dc.l0.c-its-pki.eu/getctl/D875151DE8A41EBD -O ctl
wget --no-verbose https://0.eu-dc.l0.c-its-pki.eu/getcrl/D875151DE8A41EBD -O crl

# Manually configure ITS access point
# AtoS EU PKI doesn't set this in CTL
echo "http://0.eu-ea.l0.c-its-pki.eu/" > eaurl


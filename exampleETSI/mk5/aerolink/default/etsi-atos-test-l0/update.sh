#!/bin/sh
# Update AtoS Test L0 PKI Root CA (AtoS-1) as used in Plugtests (347A3B143C94C298)
# https://0.atos-op.l0.c-its-pki.eu/
# https://0.atos-dc.l0.c-its-pki.eu/

set -x

# CA is not in the ECTL so use simple test TLM/ECTL
wget --no-verbose https://0.atos-dc.l0.c-its-pki.eu/getcacerts/0DA3EE9ACF7F9F14 -O tlm
wget --no-verbose https://0.atos-dc.l0.c-its-pki.eu/getctl/0DA3EE9ACF7F9F14 -O ectl

# Get CRL/CTL for this CA
wget --no-verbose https://0.atos-dc.l0.c-its-pki.eu/getctl/347A3B143C94C298 -O ctl
wget --no-verbose https://0.atos-dc.l0.c-its-pki.eu/getcrl/347A3B143C94C298 -O crl

# Manually configure ITS access point
# AtoS Test PKI doesn't set this in CTL
echo "http://0.atos-ea.l0.c-its-pki.eu/" > eaurl

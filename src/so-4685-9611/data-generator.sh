#!/bin/sh
#
# Generate a random number of 4-part domains, from random choices of:
# -- 4-9 letter host (or sub-sub-domain)
# -- 2-letter sub-domain
# -- 'corporate domain' from example00 through example19.
# -- TLD from .com, .net, .info.
# Used to generate domains-02.random (20000 entries)
random -n ${1:-1000} -T '%4:9w.%2w.example%02[0:19]d.%{com,net,info}S'

# Generate a random number of 4-part domains, from random choices of:
# -- 4-9 letter host (or sub-sub-domain)
# -- 2-letter sub-domain
# -- 'corporate domain' from example0 through example9.
# -- TLD from .com, .net, .info.
# Used to generate domains-01.random (20000 entries)
# random -n ${1:-1000} -T '%4:9w.%2w.example%02[0:9]d.%{com,net,info}S'

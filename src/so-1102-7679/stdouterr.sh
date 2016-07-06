#!/bin/bash
#
# http://stackoverflow.com/questions/11027679/

unset t_out t_err
eval "$( (echo std; echo err >&2; echo out; echo 'num  =  ber' >&2; exit 31) 2> >(readarray -t t_err; typeset -p t_err) > >(readarray -t t_out; typeset -p t_out) )"
echo estat=$?
echo t_out="${t_out[@]}"
echo t_err="${t_err[@]}"

unset t_out t_err
eval "$( (echo std; echo err >&2; echo out; echo 'num  =  ber' >&2; exit 37 ) 2> >(t_err=$(cat); typeset -p t_err) > >(t_out=$(cat); typeset -p t_out) )"
echo estat=$?
echo t_out="${t_out}"
echo t_err="${t_err}"

unset t_out t_err t_ret
eval "$( (echo std; echo err >&2; echo out; echo 'num  =  ber' >&2; exit 2 ) 2> >(t_err=$(cat); typeset -p t_err) > >(t_out=$(cat); typeset -p t_out); t_ret=$?; typeset -p t_ret )"
echo estat=$?
echo t_out="${t_out}"
echo t_err="${t_err}"
echo t_ret="${t_ret}"


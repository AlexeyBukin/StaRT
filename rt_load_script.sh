#!/bin/zsh
touch .script_body
MY_SCRIPT_BODY="`cat $1`"
echo $MY_SCRIPT_BODY > .script_body
echo "\nexit\n" >> .script_body
nc localhost 8080 < .script_body
rm .script_body
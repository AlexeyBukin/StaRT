# Server communication manual

To request some action from server:
1) Wait while `server.request.status == MSG_NONE`
1) Set `server.request.status = MSG_ACTIVE`
2) Set `server.request.str = my_request_str`
3) Wait while `server.response.status == MSG_NONE`
3) Get status code from `server.response.status`, check if it is `MSG_OK` (otherwise error occured)
4) (Optional) Get string from `server.response.str` with `strdup()` (server will `free()` it)
6) Set `server.request.status` to `MSG_OK` or `MSG_ERROR`

Then server will set `server.request.status = MSG_NONE`, and wait for another request.

P.S.  You should manage `server.request.str` yourself, server will not change it nor free

## MSG
1) MSG_NONE - uninitialized message
2) MSG_OK - successful operation. Server will `free()` message string (in this case only)
3) MSG_WARN - operation failure, but not critical.
4) MSG_EXIT - client disconnect command.
5) MSG_SHUT - shutdown command.
6) MSG_ERROR - critical fail.

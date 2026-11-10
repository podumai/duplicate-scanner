# duplicate-scanner
Command line utility that helps in searching file duplicates.

## Options

| Argument | Type | Description | Default | Values |
| -------- | ---- | ----------- | ------- | ------ |
| help | None | Prints information about program | None| None |
| scan-dir | array | Directories where program will perform search | ./| path-like-string |
| exclude-dir | array | Directories which program will exclude from search | None| path-like-strings |
| filename-mask | string | Regex which program will use for file matching | .+| valid regex string |
| scan-depth | integer | The maximum recursion depth for searching | 0| 0..UINT_MAX |
| block-size | interger | The size of comparing file blocks | 1024| 0..UINT_MAX |
|file-size | integer | The minimum file size to be inspected | 1| 0..UINTN_MAX |
| hash-func | string | The hashing algorithm which will be used for block comparison | sha3| [md5,sha3,blake2b] |

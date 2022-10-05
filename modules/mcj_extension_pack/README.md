# Extension Pack

## Steps

- load file paths
- transform file content (compress, encrypt)
- write transformed file content to tmp file
- create pack content table (name, offset, size)
- write pack header & content table
- append transformed file content from tmp file (checksum, data)
- delete tmp files
- verify (checksum)

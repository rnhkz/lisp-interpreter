# Build

```
sudo apt-get install libedit-dev
su -c "yum install libedit-dev*"
```

```
cc -std=c99 -Wall prompt.c -o prompt
cc -std=c99 -Wall prompt_unix.c -ledit -o prompt_unix
cc -std=c99 -Wall prompt_windows.c -ledit -o prompt_windows
```
